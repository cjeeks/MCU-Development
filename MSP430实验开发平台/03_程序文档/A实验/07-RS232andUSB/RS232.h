#ifndef _RS232_H
#define _RS232_H

extern void Init_USB(void);
extern void Init_RS232_1(void);
extern void Init_RS232_2(void);
extern void USB_TX(char *);
extern void RS232_1_TX(char *);
extern void RS232_2_TX(char *);

#endif