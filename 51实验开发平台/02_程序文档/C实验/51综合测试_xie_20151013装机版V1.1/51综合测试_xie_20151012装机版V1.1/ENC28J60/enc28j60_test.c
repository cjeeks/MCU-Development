#include "uip.h" 
#include "uip_arp.h"
#include "enc28j60.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif

/* IO DEFINETION
sbit CSN =	P1^0;	// 28J60-- CS(SS)
sbit SIN =	P1^1;	// MOSI
sbit SON =	P1^2;	// MISO
sbit SCKN = P1^3;	// SCK
sbit RSTN = P1^4;	// RST
sbit INTN = P3^3;	// INT 
*/

void enc28j60_test(void)
{
	idata u8_t i, arptimer;
	idata u16_t j;

	/* Initialize the device driver. */ 
	dev_init();
	uip_arp_init();

	/* Initialize the uIP TCP/IP stack. */
	uip_init();
	
	arptimer = 0;
	while(1) 
	{
		uip_len = dev_poll();
		for(j=0;j<500;j++);
		if(uip_len == 0) 
		{
			for(i = 0; i < UIP_CONNS; i++) 
			{
				uip_periodic(i);
				if(uip_len > 0) 
				{
					uip_arp_out();
					dev_send();
				}
			}

#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++) 
			{
				uip_udp_periodic(i);
				if(uip_len > 0) 
				{
					uip_arp_out();
					dev_send();
				}
			}
#endif /* UIP_UDP */

      /* Call the ARP timer function every 10 seconds. */
			if(++arptimer == 20) 
			{	
				uip_arp_timer();
				arptimer = 0;
			}
		}else 
		{
			if(BUF->type == htons(UIP_ETHTYPE_IP)) 
			{
				uip_arp_ipin();
				uip_input();
				if(uip_len > 0) 
				{
					uip_arp_out();
					dev_send();
				}
			}
			else if(BUF->type == htons(UIP_ETHTYPE_ARP)) 
			{
				uip_arp_arpin();
				if(uip_len > 0) 
				{	
					dev_send();
				}
			}
		}
	}
}
