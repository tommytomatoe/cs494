/**
 * @file icmpDaemon.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <icmp.h>
#include <ipv4.h>
#include <mailbox.h>
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <icmp.h>
#include <ipv4.h>
#include <mailbox.h>
#include <interrupt.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

/**
 * @ingroup icmp
 *
<<<<<<< HEAD
 * Daemon that responds to ICMP echo requests (pings).
=======
 * ICMP daemon to manage ping replies.
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
 */
thread icmpDaemon(void)
{
#if NNETIF
<<<<<<< HEAD

    while (TRUE)
    {
        struct packet *pkt;

        /* Received the next ICMP Echo Request.  */
        pkt = (struct packet *)mailboxReceive(icmpqueue);
        ICMP_TRACE("Daemon received ICMP packet");
        ICMP_TRACE("%u bytes total; %u bytes ICMP header+data",
                   pkt->len, pkt->len - (pkt->curr - pkt->data));

        /* Send the ICMP Echo Reply, re-using the packet buffer.  */
        if (OK != icmpEchoReply(pkt))
        {
            ICMP_TRACE("Failed to send ICMP Echo Reply.");
        }

        /* Free the packet buffer.  */
        netFreebuf(pkt);
    }
#endif /* NNETIF */
=======
    struct packet *pkt = NULL;
    struct ipv4Pkt *ip = NULL;
    struct netaddr dst;
    int i = 0, match = -1;

    while (TRUE)
    {
        if (NULL != pkt)
        {
            netFreebuf(pkt);
        }

        pkt = (struct packet *)mailboxReceive(icmpqueue);
        ICMP_TRACE("Daemon received ICMP packet");
        if (SYSERR == (int)pkt)
        {
            continue;
        }

        ip = (struct ipv4Pkt *)pkt->nethdr;
        dst.type = NETADDR_IPv4;
        dst.len = IPv4_ADDR_LEN;
        memcpy(dst.addr, ip->dst, dst.len);

        ICMP_TRACE("NNETIF = %d", NNETIF);
        // Scan the net interface table for an address match.
        for (i = 0; i < NNETIF; i++)
        {
            if (NET_ALLOC != netiftab[i].state)
                continue;

            // Check for our interface addresses and broadcast addresses
            if (netaddrequal(&netiftab[i].ip, &dst)
                || (netaddrequal(&netiftab[i].ipbrc, &dst)))
            {
                ICMP_TRACE("Packet matches netif %d", i);
                match = i;
                break;
            }
        }

        if ((match >= 0) && (match < NNETIF))
        {
            ICMP_TRACE("Daemon replying");
            icmpEchoReply(pkt, &netiftab[match]);
        }
        else
        {
            ICMP_TRACE("Daemon discarding");
            netFreebuf(pkt);
        }

    }
#endif                          /* NNETIF */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    return OK;
}
