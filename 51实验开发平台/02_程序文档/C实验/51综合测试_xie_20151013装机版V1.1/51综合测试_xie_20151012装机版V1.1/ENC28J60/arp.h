// File : arp.h implement for Address Resolution Protocol

#define ARP_PACKET_LEN			28

#define ARP_OPCODE_REQUEST_V	0x0001
#define ARP_OPCODE_REQUEST_H_V	0x00
#define ARP_OPCODE_REQUEST_L_V	0x01
#define ARP_OPCODE_REPLY_V		0x0002
#define ARP_OPCODE_REPLY_H_V	0x00
#define ARP_OPCODE_REPLY_L_V	0x02

#define ARP_HARDWARE_TYPE_H_V	0x00
#define ARP_HARDWARE_TYPE_L_V	0x01
#define ARP_PROTOCOL_H_V		0x08
#define ARP_PROTOCOL_L_V		0x00
#define ARP_HARDWARE_SIZE_V		0x06
#define ARP_PROTOCOL_SIZE_V		0x04

#define ARP_HARDWARE_TYPE_H_P	0x0E
#define ARP_HARDWARE_TYPE_L_P	0x0F
#define ARP_PROTOCOL_H_P		0x10
#define ARP_PROTOCOL_L_P		0x11
#define ARP_HARDWARE_SIZE_P		0x12
#define ARP_PROTOCOL_SIZE_P		0x13
#define ARP_OPCODE_H_P			0x14
#define ARP_OPCODE_L_P			0x15
#define ARP_SRC_MAC_P			0x16
#define ARP_SRC_IP_P			0x1C
#define ARP_DST_MAC_P			0x20
#define ARP_DST_IP_P			0x26

//********************************************************************************************
//
Prototype function
void arp_generate_packet ( BYTE *rxtx_buffer, BYTE *dest_mac, BYTE *dest_ip );
void arp_send_request ( BYTE *rxtx_buffer, BYTE *dest_ip );
void arp_send_reply ( BYTE *rxtx_buffer, BYTE *dest_mac );
BYTE arp_packet_is_arp ( BYTE *rxtx_buffer, WORD opcode );
BYTE arp_who_is ( BYTE *rxtx_buffer, BYTE *dest_mac, BYTE *dest_ip );
