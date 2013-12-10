/**
 * @file icmpSend.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <ipv4.h>
#include <icmp.h>
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <ipv4.h>
#include <icmp.h>
#include <ethernet.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <network.h>

/**
 * @ingroup icmp
 *
<<<<<<< HEAD
 * Send an ICMP (Internet Control Message Protocol) packet.
 *
 * @param pkt
 *      Packet containing the ICMP data.  pkt->curr must be positioned on the
 *      ICMP data, pkt->len must be the length of the ICMP data, and there must
 *      be at least enough space between pkt->data and pkt->curr for the ICMP,
 *      IPv4, and link-level headers to be attached.
 * @param type
 *      ICMP type field to use.
 * @param code
 *      ICMP code field to use.
 * @param datalen
 *      Length of the ICMP data payload.
 * @param src
 *      Source network address.  If src->type == 0, then the source is
 *      automatically set to the address of the interface on which the packet is
 *      sent.
 * @paramr dst
 *      Destination network address.
 *
 * @return
 *      ::OK if packet was successfully sent; otherwise ::SYSERR or another
 *      error code returned by ipv4Send().
 */
syscall icmpSend(struct packet *pkt, uchar type, uchar code,
                 uint datalen, struct netaddr *src, struct netaddr *dst)
{
    struct icmpPkt *icmp;
=======
 * Sends an ICMP reply.
 * @return OK if packet was sent, otherwise SYSERR
 */
syscall icmpSend(struct packet *pkt, uchar type, uchar code,
                 int datalen, struct netaddr *dst)
{
    struct icmpPkt *icmp = NULL;
    struct netaddr src;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    /* Error check pointers */
    if (NULL == pkt)
    {
        return SYSERR;
    }

    pkt->curr -= ICMP_HEADER_LEN;
    pkt->len += ICMP_HEADER_LEN;
    icmp = (struct icmpPkt *)pkt->curr;

    icmp->type = type;
    icmp->code = code;
    icmp->chksum = 0;
    icmp->chksum = netChksum((uchar *)icmp, datalen + ICMP_HEADER_LEN);

<<<<<<< HEAD
    ICMP_TRACE("Sending ICMP packet type %d, code %d", type, code);
    return ipv4Send(pkt, src, dst, IPv4_PROTO_ICMP);
=======
    src.type = NULL;

    ICMP_TRACE("Sending ICMP packet type %d, code %d", type, code);
    return ipv4Send(pkt, &src, dst, IPv4_PROTO_ICMP);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
