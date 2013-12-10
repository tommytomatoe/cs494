/**
 * @file icmpEchoReply.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <icmp.h>
#include <network.h>
#include <ipv4.h>
#include <string.h>

/**
 * Send an ICMP Echo Reply in response to the specified ICMP Echo Request.
 *
 * @param pkt
 *      Pointer to the packet for an ICMP echo request.  This packet buffer is
 *      re-used for sending the reply.  pkt->curr must point to the beginning of
 *      the the ICMP header, whereas pkt->len must be the length of the entire
 *      packet including link-level header.  These members will be updated by
 *      this function, and the ICMP type field and checksum will be modified;
 *      however, ownership of the packet is not taken and it still must be freed
 *      by the caller.
 *
 * @return
 *      ::OK if packet was successfully sent; otherwise ::SYSERR or another
 *      error code returned by icmpSend().
 */
syscall icmpEchoReply(struct packet *pkt)
{
    struct ipv4Pkt *ip;
    struct netaddr src, dst;

    ICMP_TRACE("Sending ICMP_ECHOREPLY");

    /* RFC 792: "To form an echo reply message, the source and destination
     * addresses are simply reversed, the type code changed to 0, and the
     * checksum recomputed."  */

    /* Retrieve destination and source addresses from the IPv4 header.  */
    ip = (struct ipv4Pkt *)pkt->nethdr;
    dst.type = NETADDR_IPv4;
    dst.len = IPv4_ADDR_LEN;
    memcpy(dst.addr, ip->dst, dst.len);

    src.type = NETADDR_IPv4;
    src.len = IPv4_ADDR_LEN;
    memcpy(src.addr, ip->src, src.len);

    /* Set pkt->curr to point to ICMP data and set pkt->len to the length of
     * the ICMP data.  This sets it up for sending with icmpSend().  */
    pkt->curr += ICMP_HEADER_LEN;
    pkt->len -= (pkt->curr - pkt->data);

    /* Send the ICMP Echo Reply.  */
    return icmpSend(pkt, ICMP_ECHOREPLY, 0, pkt->len, &dst, &src);
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <icmp.h>
#include <ipv4.h>
#include <stdlib.h>

/**
 * @ingroup icmp
 *
 * Compose ICMP Echo Reply.
 * @param pkt Packet containing request
 * @param nif Net interface matching destination address
 * @return OK on success, else SYSERR
 */
syscall icmpEchoReply(struct packet *pkt, struct netif *nif)
{
    struct icmpPkt *icmp = NULL;
    struct ipv4Pkt *ip = NULL;
    struct netaddr dst;

    /* Error check pointers */
    if (NULL == pkt)
    {
        return SYSERR;
    }

    ip = (struct ipv4Pkt *)pkt->nethdr;
    icmp = (struct icmpPkt *)pkt->curr;

    icmp->type = hs2net(ICMP_ECHOREPLY);
    dst.type = NETADDR_IPv4;
    dst.len = IPv4_ADDR_LEN;
    memcpy(dst.addr, ip->src, dst.len);

    ICMP_TRACE("Sending Echo Reply");
    ipv4Send(pkt, &nif->ip, &dst, IPv4_PROTO_ICMP);

    return OK;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
