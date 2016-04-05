/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_X_StartVNC
Purpose     : Starts the VNC server via TCP/IP
              This code works with embOS and the RTIP TCP/IP stack.
              However, it can be easily modified to work with
              different kernel and IP Stack
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "RTIP.H"     /* RTIP API */
#include "SOCKET.H"   /* BSD socket interface */
#include "RTOS.H"     /* embOS header */
#include "GUI.h"
#include "GUI_X.h"
#include "GUI_VNC.h"
#include "HWC.h"      /* Hardware function prototypes */

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static GUI_VNC_CONTEXT _Context;
static OS_STACKPTR int _StackVNCServer[1000];             /* embOS Stack area of the server */
static OS_TASK         _VNCServer_TCB;                    /* embOS Task-control-block of the server */

/*********************************************************************
*
*       static const
*
**********************************************************************
*/
static const unsigned char   _IPLocal[4] = {192,168,1,254};     /* IP address of the system */
static const unsigned char   _IPMask[4] =  {255,255,0,0};       /* IP mask for the system   */

/*********************************************************************
*
*             Static functions
*
**********************************************************************
*/


/*********************************************************************
*
*       _Send
*
* Function description
*   This function is called indirectly by the server; it's address is passed to the actual
*   server code as function pointer. It is needed because the server is independent
*   of the TCP/IP stack implementation, so details for the TCP/IP stack can be placed here.
* Notes:
*   (1) This implementation is for EBS's RTIP stack.
*   (2) It switches between blocking and non-blocking mode; This is due to a weekness
*       of the RTIP stack: It tries to fill up the TCP-window before sending the
*       package; but since the socket normally blocks, no more data is send to the socket
*       until a time-out expires of about 200 ms. This would slow down communication
*       dramatically and can be avoided with the "trick" below; as long as there is enough
*       space in the TCP-window, we use non-blocking mode.
*/
static int _Send(const U8* buf, int len, void* pConnectionInfo) {
  unsigned long r;                             /* Needs to be unsigned long, because ioctlsocket takes a pointer to it */
  SOCKET socket;
  unsigned long zero = 0;

  socket = (SOCKET)pConnectionInfo;
  ioctlsocket (socket, FIONWRITE, &r);
  if (r > len) {
    unsigned long one  = 1;
    ioctlsocket (socket, FIONBIO, &one); /* nonblocking */
  }
  r = send(socket, (const char*)buf, len, 0);
  ioctlsocket (socket, FIONBIO, &zero); /* blocking */
  return r;
}

/*********************************************************************
*
*       _Recv
*
* Function description
*   This function is called indirectly by the server; it's address is passed to the actual
*   server code as function pointer. It is needed because the server is independent
*   of the TCP/IP stack implementation, so details for the TCP/IP stack can be placed here.
* Notes:
*   (1) This implementation is for EBS's RTIP stack, but it should work without modification
*       on most TCP/IP stacks.
*/
static int _Recv(U8* buf, int len, void* pConnectionInfo) {
  return recv((SOCKET)pConnectionInfo, (char*)buf, len, 0);
}

/*********************************************************************
*
*       _ServerTask
*
* Function description
*   This routine is the actual server task.
*   It executes some one-time init code, then runs in an ednless loop.
*   It therefor does not terminate.
*   In the endless loop it
*     - Waits for a conection from a client
*     - Runs the server code
*     - Closes the connection
*/
static void _ServerTask(void) {
  int s, sock;
  short Port;
  struct sockaddr_in addr_in;
  const int one = 1;

  /* Prepare socket (one time setup) */
  Port = 5900 + _Context.ServerIndex;                     /* Default port for VNC is is 590x, where x is the 0-based layer index */
  addr_in.sin_family      = AF_INET;
  addr_in.sin_port        = htons(Port);
  addr_in.sin_addr.s_addr = INADDR_ANY;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    return;                                               /* Error ... We are done with this task */
  }
  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char *) &one, sizeof(one)) < 0) {
    closesocket(s);
    return;                                               /* Error ... We are done with this task */
  }
  if (bind(s, (struct sockaddr *)&addr_in, sizeof(addr_in))) {
    closesocket(s);
    return;                                               /* Error ... We are done with this task */
  }
  if (listen(s, 1)) {
    closesocket(s);
    return;                                               /* Error ... We are done with this task */
  }
  
  /* Endless loop. We run thru it once for every client connecting to us */
  while (1) {
    struct sockaddr addr;
    int addrlen;

    /* Wait for an incoming connection */
    addrlen = sizeof(addr);
    if ((sock = accept(s, &addr, &addrlen)) < 0) {
      return;                                             /* Error ... We are done with this task */
    }

    /* Disable Nagle's algorithm - improves performance (optional) */
    {
      const int zero = 0;
      setsockopt(sock, SOL_SOCKET, SO_NAGLE, (const char *) &zero, sizeof(zero));
    }
    /* Run the actual server */
    GUI_VNC_Process(&_Context, _Send, _Recv, (void*)sock);

    /* Close the connection */
    closesocket(sock);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*             GUI_VNC_X_StartServer
*
* Function description
*   To start the server, the following steps are executed
*   - Make sure the TCP-IP stack is up and running
*   - Init the server context and attach it to the layer
*   - Start the thread (task) which runs the VNC server
* Notes:
*   (1) The first part of the code initializes the TCP/IP stack. In a typical
*       application, this is not required, since the stack should have already been
*       initialized some other place.
*       This could be done in a different module. (TCPIP_AssertInit() ?)
*/
int GUI_VNC_X_StartServer(int LayerIndex, int ServerIndex) {
  /* Make sure the TCP/IP stack is initialized.  (1) */
  if (xn_rtip_init() != 0) {
    OS_SendString("GUI_VNC_X_StartServer: Init failed\n");
    return 1;                    /* Error */
  }
  {
    int interface;
    xn_bind_cs(0);                                        /* append interface to device table */
    interface = xn_interface_open_config(CS89X0_DEVICE, 0, (IOADDRESS)0x20000300,5,0);   /* open interface */
    if (interface < 0) {
      OS_SendString("GUI_VNC_X_StartServer: Can not open interface\n");
      return 1;                                           /* Error */
    }
    xn_set_ip(interface, (PFBYTE)&_IPLocal[0], (PFBYTE)&_IPMask[0]);      /* set IP address of interface */
    HW_EnableEthernetIRQ();                               /* Enable ethernet IRQ. Make sure it is done after xn_interface_open_config() */  
  }

  /* Init VNC context and attach to layer (so context is updated if the display-layer-contents change */
  GUI_VNC_AttachToLayer(&_Context, LayerIndex);
  _Context.ServerIndex = ServerIndex;

  /* Create task for VNC Server */
  OS_CREATETASK(&_VNCServer_TCB, "VNC Server", _ServerTask, 50, _StackVNCServer);
  return 0;                                               /* O.k., server has been started */
}
/*************************** End of file ****************************/


