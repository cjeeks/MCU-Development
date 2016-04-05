#ifndef _RS232_H
#define _RS232_H


extern void Init_USB(void);
extern void Init_RS232_1(void);
extern void Init_RS232_2(void);
extern void USB_TX(char *);

extern void RS232_1_TX(char *);
extern void RS232_2_TX(char *);
void RS232_3_TX(unsigned char *tx_buf);
void Init_RS232_0(void);
void Init_RS232_3(void);
extern char parse_RFID_info();
extern unsigned char* get_RFID_ID();
extern unsigned char* get_RFID_DATA();
extern char Is_RS232_1_data();
extern unsigned char get_RS232_1_byte();
void Display(void);

#define BUF_SIZE 100
//extern unsigned char uart1_buf[];
//extern unsigned char read_index ;
//extern unsigned char write_index ;

#endif