#ifndef __UIP_ARP_H__
#define __UIP_ARP_H__

#include "uip.h"
/**
 * Representation of a 48-bit Ethernet address.
 */

struct uip_eth_addr 
{
	u8_t addr[6];
};

extern struct uip_eth_addr uip_ethaddr;

/**
 * The Ethernet header. 
 */
struct uip_eth_hdr 
{
	struct uip_eth_addr dest;
	struct uip_eth_addr src;
	u16_t type;
};

#define UIP_ETHTYPE_ARP 0x0806
#define UIP_ETHTYPE_IP  0x0800
#define UIP_ETHTYPE_IP6 0x86dd

/* The uip_arp_init() function must be called before any of the other
   ARP functions. */
void uip_arp_init(void);

/* The uip_arp_ipin() function should be called whenever an IP packet
   arrives from the Ethernet. This function refreshes the ARP table or
   inserts a new mapping if none exists. The function assumes that an
   IP packet with an Ethernet header is present in the uip_buf buffer
   and that the length of the packet is in the uip_len variable. */
void uip_arp_ipin(void);

/* The uip_arp_arpin() should be called when an ARP packet is received
   by the Ethernet driver. This function also assumes that the
   Ethernet frame is present in the uip_buf buffer. When the
   uip_arp_arpin() function returns, the contents of the uip_buf
   buffer should be sent out on the Ethernet if the uip_len variable
   is > 0. */
void uip_arp_arpin(void);

/* The uip_arp_out() function should be called when an IP packet
   should be sent out on the Ethernet. This function creates an
   Ethernet header before the IP header in the uip_buf buffer. The
   Ethernet header will have the correct Ethernet MAC destination
   address filled in if an ARP table entry for the destination IP
   address (or the IP address of the default router) is present. If no
   such table entry is found, the IP packet is overwritten with an ARP
   request and we rely on TCP to retransmit the packet that was
   overwritten. In any case, the uip_len variable holds the length of
   the Ethernet frame that should be transmitted. */
void uip_arp_out(void);

/* The uip_arp_timer() function should be called every ten seconds. It
   is responsible for flushing old entries in the ARP table. */
void uip_arp_timer(void);

/**
 * Set the default router's IP address.
 *
 * \param addr A pointer to a 4-byte array containing the IP address
 * of the default router.
 *
 * \hideinitializer
 */
#define uip_setdraddr(addr) do { uip_arp_draddr[0] = addr[0]; \
                                 uip_arp_draddr[1] = addr[1]; } while(0)

/**
 * Set the netmask.
 *
 * \param addr A pointer to a 4-byte array containing the IP address
 * of the netmask.
 *
 * \hideinitializer
 */
#define uip_setnetmask(addr) do { uip_arp_netmask[0] = addr[0]; \
                                  uip_arp_netmask[1] = addr[1]; } while(0)

/**
 * Get the default router's IP address.
 *
 * \param addr A pointer to a 4-byte array that will be filled in with
 * the IP address of the default router.
 *
 * \hideinitializer
 */
#define uip_getdraddr(addr) do { addr[0] = uip_arp_draddr[0]; \
                                 addr[1] = uip_arp_draddr[1]; } while(0)

/**
 * Get the netmask.
 *
 * \param addr A pointer to a 4-byte array that will be filled in with
 * the value of the netmask.
 *
 * \hideinitializer
 */
#define uip_getnetmask(addr) do { addr[0] = uip_arp_netmask[0]; \
                                  addr[1] = uip_arp_netmask[1]; } while(0)


/**
 * Specifiy the Ethernet MAC address.
 *
 * The ARP code needs to know the MAC address of the Ethernet card in
 * order to be able to respond to ARP queries and to generate working
 * Ethernet headers.
 *
 * \note This macro only specifies the Ethernet MAC address to the ARP
 * code. It cannot be used to change the MAC address of the Ethernet
 * card.
 *
 * \param eaddr A pointer to a struct uip_eth_addr containing the
 * Ethernet MAC address of the Ethernet card.
 *
 * \hideinitializer
 */
#define uip_setethaddr(eaddr) do {\
	uip_ethaddr.addr[0] = eaddr.addr[0];\
	uip_ethaddr.addr[1] = eaddr.addr[1];\
	uip_ethaddr.addr[2] = eaddr.addr[2];\
	uip_ethaddr.addr[3] = eaddr.addr[3];\
	uip_ethaddr.addr[4] = eaddr.addr[4];\
	uip_ethaddr.addr[5] = eaddr.addr[5];\
}while(0)

/** @} */

/**
 * \internal Internal variables that are set using the macros
 * uip_setdraddr and uip_setnetmask.
 */
extern u16_t uip_arp_draddr[2], uip_arp_netmask[2];
#endif /* __UIP_ARP_H__ */


