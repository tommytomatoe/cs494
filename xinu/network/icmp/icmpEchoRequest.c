/**
 * @file icmpEchoRequest.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <icmp.h>
#include <stdlib.h>
#include <clock.h>
#include <interrupt.h>

/**
 * @ingroup icmp
 *
 * Send an ICMP Echo (Ping) Request.
 * @param dst destination address
 * @param id  ping stream identifier
 * @param seq sequence number
 * @return OK if packet was sent, otherwise SYSERR
 */
syscall icmpEchoRequest(struct netaddr *dst, ushort id, ushort seq)
{
<<<<<<< HEAD
    struct packet *pkt;
    struct icmpEcho *echo;
    int result;
    struct netaddr src;
=======
    struct packet *pkt = NULL;
    struct icmpEcho *echo = NULL;
    int result = OK;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    irqmask im;

    ICMP_TRACE("echo request(%d, %d)", id, seq);
    pkt = netGetbuf();
    if (SYSERR == (int)pkt)
    {
        ICMP_TRACE("Failed to acquire packet buffer");
        return SYSERR;
    }

    pkt->len = sizeof(struct icmpEcho);
    pkt->curr -= pkt->len;

    echo = (struct icmpEcho *)pkt->curr;
    echo->id = hs2net(id);
    echo->seq = hs2net(seq);
    /* Our optional data payload includes room for the departure */
    /*  and arrival timestamps, in seconds, milliseconds, and    */
    /*  clock cycles.                                            */
    im = disable();
    echo->timecyc = hl2net(clkcount());
    echo->timetic = hl2net(clkticks);
    echo->timesec = hl2net(clktime);
    restore(im);
    echo->arrivcyc = 0;
    echo->arrivtic = 0;
    echo->arrivsec = 0;

<<<<<<< HEAD
    ICMP_TRACE("Sending Echo Request id = %d, seq = %d, time = %lu.%lu",
               net2hs(echo->id), net2hs(echo->seq),
               net2hl(echo->timesec), net2hl(echo->timetic));

    src.type = 0;

    result = icmpSend(pkt, ICMP_ECHO, 0, sizeof(struct icmpEcho), &src, dst);
=======
    ICMP_TRACE("Sending Echo Request id = %d, seq = %d, time = %d.%d",
               net2hs(echo->id), net2hs(echo->seq),
               net2hl(echo->timesec), net2hl(echo->timetic));

    result = icmpSend(pkt, ICMP_ECHO, 0, sizeof(struct icmpEcho), dst);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    netFreebuf(pkt);
    return result;
}
