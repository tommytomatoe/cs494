/*
<<<<<<< HEAD
 * @file xsh_ping.c
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <conf.h>

#if NETHER

#include <clock.h>
#include <icmp.h>
#include <interrupt.h>
#include <ipv4.h>
#include <limits.h>
#include <network.h>
#include <platform.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <thread.h>

static int echoQueueAlloc(void);
static void echoQueueDealloc(int echoent);
static struct packet *echoQueueGet(int echoent);
static void echoPrintPkt(const struct packet *pkt, ulong elapsed);
static ulong echoTripTime(const struct packet *pkt);
static ulong tickDiff(ulong startsec, ulong startticks,
                      ulong endsec, ulong endticks);
=======
 * @file     xsh_ping.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread.h>
#include <string.h>
#include <network.h>
#include <ipv4.h>
#include <icmp.h>
#include <clock.h>
#include <shell.h>
#include <interrupt.h>
#include <platform.h>

#if NETHER
static int echoQueueAlloc(void);
static int echoQueueDealloc(int echoent);
static struct packet *echoQueueGet(int echoent);
static void echoPrintPkt(struct packet *pkt, ulong elapsed);
static ulong echoTripTime(struct packet *pkt);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

/**
 * @ingroup shell
 *
 * Shell command (ping).
<<<<<<< HEAD
 *
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 *
 * @return
 *      ::SHELL_OK if successful; ::SHELL_ERROR if there was a syntax error or
 *      any echo requests could not be sent.  (Failure to receive echo replies
 *      is not considered a cause to return ::SHELL_ERROR.)
 */
shellcmd xsh_ping(int nargs, char *args[])
{
    uint i;
    uint interval = 1000;
    uint intervalticks;
    uint count = 10;
    uint num_recv = 0;
    int echoq;
    ulong min_rtt = ULONG_MAX, max_rtt = 0, total_rtt = 0;
    ulong startsec, startticks;
    ulong endsec, endticks;
    struct netaddr target;
    char target_str[50];
    irqmask im;

    /* Output help if '--help' argument was supplied.  */
    if (2 == nargs && 0 == strcmp(args[1], "--help"))
=======
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_ping(int nargs, char *args[])
{
    int i = 0;
    int interval = 1000, count = 10, recv = 0, echoq = 0;
    ulong rtt = 0, min = 0, max = 0, total = 0;
    ulong startsec = 0, startms = 0;
    struct netaddr target;
    struct packet *pkt = NULL;
    char str[50];

    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        printf("Usage: ping <IP>\n\n");
        printf("Description:\n");
        printf("\tSend ICMP echo requests to network hosts\n");
        printf("Options:\n");
        printf("\t<IP>\t\tIP address\n");
        printf("\t-c count\tstop after sending count packets\n");
<<<<<<< HEAD
        printf("\t-i interval\tsleep interval milliseconds between pings\n");
        printf("\t--help\t\tdisplay this help and exit\n");
        return SHELL_OK;
    }

    for (i = 1; i < nargs; i++)
    {
        if (0 == strcmp(args[i], "-c"))
        {
            char tmp;

            i++;
            if (i == nargs ||
                1 != sscanf(args[i], "%u%c", &count, &tmp) ||
                0 >= count)
            {
                fprintf(stderr, "ping: -c requires positive integer argument\n");
                return SHELL_ERROR;
            }
        }
        else if (0 == strcmp(args[i], "-i"))
        {
            char tmp;

            i++;
            if (i == nargs ||
                1 != sscanf(args[i], "%u%c", &interval, &tmp))
=======
        printf
            ("\t-i interval\tsleep interval milliseconds between pings\n");
        printf("\t--help\t\tdisplay this help and exit\n");
        return OK;
    }

    /* Check for correct number of arguments */
    if (nargs < 2)
    {
        fprintf(stderr, "ping: too few arguments\n");
        fprintf(stderr, "Try 'ping --help' for more information\n");
        return SHELL_ERROR;
    }

    i = 1;
    while (i < nargs)
    {
        if (0 == strncmp(args[i], "-c", 3))
        {
            i++;
            if (i < nargs)
            {
                count = atoi(args[i]);
            }
            else
            {
                fprintf(stderr, "ping: -c requires integer argument\n");
                return SHELL_ERROR;
            }
        }
        else if (0 == strncmp(args[i], "-i", 3))
        {
            i++;
            if (i < nargs)
            {
                interval = atoi(args[i]);
            }
            else
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
            {
                fprintf(stderr, "ping: -i requires integer argument\n");
                return SHELL_ERROR;
            }
        }
<<<<<<< HEAD
        else
        {
            break;
        }
    }

    if (i == nargs)
=======
        else if (SYSERR == dot2ipv4(args[i], &target))
        {
            fprintf(stderr, "ping: %s is not a valid IPv4 address.\n",
                    args[i]);
            return SHELL_ERROR;
        }
        i++;
    }

    netaddrsprintf(str, &target);
    if (0 == strncmp(str, "ERROR", 6))
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        fprintf(stderr, "ping: destination IP address required.\n");
        return SHELL_ERROR;
    }
<<<<<<< HEAD

    if (i < nargs - 1)
    {
        fprintf(stderr, "ping: only one destination IP address is allowed.\n");
        return SHELL_ERROR;
    }

    if (SYSERR == dot2ipv4(args[i], &target))
    {
        fprintf(stderr, "ping: %s is not a valid IPv4 address.\n", args[i]);
        return SHELL_ERROR;
    }

    netaddrsprintf(target_str, &target);

    printf("PING %s\n", target_str);
=======
    printf("PING %s\n", str);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    echoq = echoQueueAlloc();
    if (SYSERR == echoq)
    {
        printf("...No free echo queues!\n");
        return SHELL_ERROR;
    }

<<<<<<< HEAD
    im = disable();
    startsec = clktime;
    startticks = clkticks;
    restore(im);

    intervalticks = interval * CLKTICKS_PER_SEC / 1000;

    for (i = 0; i < count; i++)
    {
        ulong sendsec, sendticks;

        // Send ping packet
        if (OK != icmpEchoRequest(&target, gettid(), i))
        {
            printf("...Failed to reach %s\n", target_str);
            echoQueueDealloc(echoq);
            return SHELL_ERROR;
        }

        im = disable();
        sendsec = clktime;
        sendticks = clkticks;
        restore(im);

        // Wait for response
        if (TIMEOUT != recvtime(intervalticks))
        {
            struct packet *pkt;

            // pick reply packets off of the queue
            while (NULL != (pkt = echoQueueGet(echoq)))
            {
                ulong rtt;

                rtt = echoTripTime(pkt);
                total_rtt += rtt;
                min_rtt = min(min_rtt, rtt);
                max_rtt = max(max_rtt, rtt);
                echoPrintPkt(pkt, rtt);
                netFreebuf(pkt);
                num_recv++;
            }

            // Sleep for remaining time
            if (i < count - 1)
            {
                ulong elapsedticks;
                ulong recvsec, recvticks;

                im = disable();
                recvsec = clktime;
                recvticks = clkticks;
                restore(im);

                elapsedticks = tickDiff(sendsec, sendticks, recvsec, recvticks);

                if (elapsedticks < intervalticks)
                {
                    sleep((intervalticks - elapsedticks) * 1000 / CLKTICKS_PER_SEC);
                }
            }
        }
    }

    echoQueueDealloc(echoq);

    if (min_rtt == ULONG_MAX)
    {
        min_rtt = 0;
    }

    im = disable();
    endsec = clktime;
    endticks = clkticks;
    restore(im);

    printf("--- %s ping statistics ---\n", target_str);
    printf("%u packets transmitted, %u received,", count, num_recv);
    printf(" %u%% packet loss,", (count - num_recv) * 100 / count);
    printf(" time %lums\n",
           tickDiff(startsec, startticks,
                    endsec, endticks) * 1000 / CLKTICKS_PER_SEC);
    printf("rtt min/avg/max = %lu.%03lu/", min_rtt / 1000, min_rtt % 1000);
    if (0 != num_recv)
    {
        printf("%lu.%03lu/", (total_rtt / num_recv) / 1000,
               (total_rtt / num_recv) % 1000);
=======
    startsec = clktime;
    startms = clkticks;

    for (i = 0; i < count; i++)
    {
        // Send ping packet
        if (SYSERR == icmpEchoRequest(&target, gettid(), i))
        {
            printf("...Failed to reach %s\n", str);
            return SHELL_ERROR;
        }

        sleep(interval);
        if (NOMSG != recvclr())
        {
            // pick reply packets off of the queue
            pkt = echoQueueGet(echoq);
            while ((NULL != (ulong)pkt) && (SYSERR != (ulong)pkt))
            {
                rtt = echoTripTime(pkt);
                total += rtt;
                if ((rtt < min) || (0 == min))
                {
                    min = rtt;
                }
                if (rtt > max)
                {
                    max = rtt;
                }

                echoPrintPkt(pkt, rtt);
                netFreebuf(pkt);
                recv++;
                pkt = echoQueueGet(echoq);
            }
        }
    }
    echoQueueDealloc(echoq);

    netaddrsprintf(str, &target);
    printf("--- %s ping statistics ---\n", str);
    printf("%d packets transmitted, %d received,", count, recv);
    printf(" %d%% packet loss,", (count - recv) * 100 / count);
    printf(" time %dms\n", (clktime - startsec) * 1000 +
           ((clkticks - startms) * 1000) / CLKTICKS_PER_SEC);
    printf("rtt min/avg/max = %d.%03d/", min / 1000, min % 1000);
    if (0 != recv)
    {
        printf("%d.%03d/", (total / recv) / 1000, (total / recv) % 1000);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    }
    else
    {
        printf("-/");
    }
<<<<<<< HEAD
    printf("%lu.%03lu ms\n", max_rtt / 1000, max_rtt % 1000);
=======
    printf("%d.%03d ms\n", max / 1000, max % 1000);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    return SHELL_OK;
}

<<<<<<< HEAD
/* Allocate an ICMP Echo Reply queue.  Return index of allocated queue, or
 * SYSERR if none are available.  */
static int echoQueueAlloc(void)
{
    irqmask im;
    int i;
    int retval;

    im = disable();
    retval = SYSERR;

=======
/**
 * Search for an echo reply queue that is not in use.
 */
static int echoQueueAlloc(void)
{
    irqmask im;
    int i = 0;

    im = disable();
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    for (i = 0; i < NPINGQUEUE; i++)
    {
        if (BADTID == echotab[i].tid)
        {
            echotab[i].tid = gettid();
<<<<<<< HEAD
            retval = i;
            break;
=======
            restore(im);
            return i;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
        }
    }

    restore(im);
<<<<<<< HEAD
    return retval;
}

/* Release an echo reply queue, freeing any buffered packets.  */
static void echoQueueDealloc(int echoent)
{
    irqmask im;
    struct packet *pkt;
    struct icmpEchoQueue *eq;

=======
    return SYSERR;
}

/**
 * Give up an echo reply queue, and flush any loitering packets.
 */
static int echoQueueDealloc(int echoent)
{
    irqmask im;
    struct packet *pkt = NULL;
    struct icmpEchoQueue *eq = NULL;

    if ((echoent < 0) || (echoent >= NPINGQUEUE))
    {
        return SYSERR;
    }
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    eq = &echotab[echoent];

    im = disable();
    eq->tid = BADTID;
    while (eq->tail != eq->head)
    {
        pkt = eq->pkts[eq->tail];
<<<<<<< HEAD
        ICMP_TRACE("Discarding ping packet from closed queue %d", echoent);
=======
        ICMP_TRACE("Discarding ping packet from closed queue %d",
                   echoent);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
        netFreebuf(pkt);
        eq->tail = (eq->tail + 1) % NPINGHOLD;
    }

    restore(im);
<<<<<<< HEAD
}

/* Fetch a packet from an ICMP Echo Reply queue.  Returns a pointer to the
 * resulting packet buffer, or NULL if no packets are available in the specified
 * queue.  */
static struct packet *echoQueueGet(int echoent)
{
    irqmask im;
    struct packet *pkt;
    struct icmpEchoQueue *eq;

    eq = &echotab[echoent];
    im = disable();
    if (eq->head != eq->tail)
    {
        pkt = eq->pkts[eq->tail];
        eq->tail = (eq->tail + 1) % NPINGHOLD;
    }
    else
    {
        pkt = NULL;
    }
=======
    return OK;
}

/**
 * Fetch a packet from an echo reply queue.
 */
static struct packet *echoQueueGet(int echoent)
{
    irqmask im;
    struct packet *pkt = NULL;
    struct icmpEchoQueue *eq = NULL;

    if ((echoent < 0) || (echoent >= NPINGQUEUE))
    {
        return (struct packet *)SYSERR;
    }
    eq = &echotab[echoent];

    im = disable();

    if (eq->tid != gettid())
    {
        restore(im);
        return (struct packet *)SYSERR;
    }

    if (eq->head == eq->tail)
    {
        restore(im);
        return (struct packet *)NULL;
    }
    pkt = eq->pkts[eq->tail];
    eq->tail = (eq->tail + 1) % NPINGHOLD;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    restore(im);
    return pkt;
}

<<<<<<< HEAD
/* Prints information from an ICMP Echo Reply packet.
 *
 * @elapsed specifies the number of microseconds that have elapsed since the
 * corresponding ICMP Echo Request was sent.  */
static void echoPrintPkt(const struct packet *pkt, ulong elapsed)
{
    const struct ipv4Pkt *ip;
    const struct icmpPkt *icmp;
    const struct icmpEcho *echo;
    struct netaddr src;
    char src_str[50];

    ip = (const struct ipv4Pkt *)pkt->nethdr;
    icmp = (const struct icmpPkt *)pkt->curr;
    echo = (const struct icmpEcho *)icmp->data;
=======
/**
 * Print out a echo reply packet.
 */
static void echoPrintPkt(struct packet *pkt, ulong elapsed)
{
    struct icmpPkt *icmp = NULL;
    struct icmpEcho *echo = NULL;
    struct ipv4Pkt *ip = NULL;
    struct netaddr src;
    char str[50];

    ip = (struct ipv4Pkt *)pkt->nethdr;
    icmp = (struct icmpPkt *)pkt->curr;
    echo = (struct icmpEcho *)icmp->data;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    src.type = NETADDR_IPv4;
    src.len = IPv4_ADDR_LEN;
    memcpy(src.addr, ip->src, src.len);

<<<<<<< HEAD
    netaddrsprintf(src_str, &src);
    printf("%d bytes from %s: ", net2hs(ip->len), src_str);
    printf("icmp_seq=%d ttl=%d ", net2hs(echo->seq), ip->ttl);
    printf("time=%lu.%03lu ms\n", elapsed / 1000, elapsed % 1000);
}

/*
 * Return the elapsed round trip time of an ICMP echo request and reply, in
 * microseconds.
 *
 * This relies on the timecyc, timetic, and timesec fields that were stored in
 * the echo request and echoed back, as well as the arrivcyc, arrivtic, and
 * arrivsec fields which were set by icmpRecv().
 */
static ulong echoTripTime(const struct packet *pkt)
{
    const struct icmpPkt *icmp;
    const struct icmpEcho *echo;
    ulong cycPerTick;
    ulong elapsedticks, elapsedcyc;

    icmp = (const struct icmpPkt *)pkt->curr;
    echo = (const struct icmpEcho *)icmp->data;

    cycPerTick = platform.clkfreq / CLKTICKS_PER_SEC;

    elapsedticks = tickDiff(net2hl(echo->timesec), net2hl(echo->timetic),
                            echo->arrivsec, echo->arrivtic);

    elapsedcyc = elapsedticks * cycPerTick;

    elapsedcyc += (echo->arrivcyc - net2hl(echo->timecyc)) % cycPerTick;

    return elapsedcyc / (platform.clkfreq / 1000000);
}

/* Returns the number of timer ticks that have elapsed between two times.
 *
 * NOTE: This function is needed because tick wraparound occurs before
 * wraparound in the underlying data type and therefore needs special handling.
 */
static ulong tickDiff(ulong startsec, ulong startticks,
                      ulong endsec, ulong endticks)
{
    ulong elapsedticks;

    elapsedticks = (endsec - startsec) * CLKTICKS_PER_SEC;

    if (endticks >= startticks)
    {
        elapsedticks += (endticks - startticks);
    }
    else
    {
        elapsedticks -= (startticks - endticks);
    }

    return elapsedticks;
}

=======
    netaddrsprintf(str, &src);
    printf("%d bytes from %s: ", net2hs(ip->len), str);
    printf("icmp_seq=%d ttl=%d ", net2hs(echo->seq), ip->ttl);
    printf("time=%d.%03d ms\n", elapsed / 1000, elapsed % 1000);
}

/**
 * Return elapsed trip time in microseconds.
 */
static ulong echoTripTime(struct packet *pkt)
{
    struct icmpPkt *icmp = NULL;
    struct icmpEcho *echo = NULL;
    ulong elapsed = 0, cycPerTick = 0;

    icmp = (struct icmpPkt *)pkt->curr;
    echo = (struct icmpEcho *)icmp->data;

    cycPerTick = platform.clkfreq / CLKTICKS_PER_SEC;

    elapsed = (echo->arrivcyc - net2hl(echo->timecyc)) % cycPerTick;
    elapsed += (echo->arrivtic - net2hl(echo->timetic)) * cycPerTick;
    elapsed +=
        (echo->arrivsec - net2hl(echo->timesec)) * platform.clkfreq;
    elapsed = elapsed / (platform.clkfreq / 1000000);
    return elapsed;
}
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#endif /* NETHER */
