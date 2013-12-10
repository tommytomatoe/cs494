/**
 * @file dot2ipv4.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <ipv4.h>
#include <network.h>
#include <stdio.h>
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <ctype.h>
#include <ipv4.h>
#include <network.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

/**
 * @ingroup ipv4
 *
<<<<<<< HEAD
 * Convert an IPv4 address in dotted-decimal notation into a netaddr.
 *
 * @param str
 *      The dotted-decimal IPv4 address string to convert.
 * @param ip
 *      The netaddr structure for conversion result.
 *
 * @return
 *      ::OK if conversion was successful, otherwise ::SYSERR.
 */
syscall dot2ipv4(const char *str, struct netaddr *ip)
{
    uint o0, o1, o2, o3;
    char tmp;
=======
 * Convert an IP Address in dotted-decimal notation into a netaddr.
 * @param str dotted-decimal IP Address string
 * @param ip netaddr structure for conversion result
 * @return OK if conversion was successful, otherwise SYSERR
 */
syscall dot2ipv4(const char *str, struct netaddr *ip)
{
    char c;
    uint count = 0, temp = 0;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    /* Error check pointers */
    if ((NULL == str) || (NULL == ip))
    {
        return SYSERR;
    }

<<<<<<< HEAD
    if (4 != sscanf(str, "%3u.%3u.%3u.%3u%c", &o0, &o1, &o2, &o3, &tmp) ||
        o0 > 0xff || o1 > 0xff || o2 > 0xff || o3 > 0xff)
    {
        return SYSERR;
    }

    ip->addr[0] = o0;
    ip->addr[1] = o1;
    ip->addr[2] = o2;
    ip->addr[3] = o3;
=======
    while ((count < IPv4_ADDR_LEN) && *str)
    {
        c = *str;
        if (isdigit(c))
        {
            temp = temp * 10 + (c - '0');
        }
        else if ('.' == c)
        {
            ip->addr[count] = temp;
            temp = 0;
            count++;
        }
        else
        {
            return SYSERR;
        }
        str++;
    }
    ip->addr[count] = temp;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    ip->type = NETADDR_IPv4;
    ip->len = IPv4_ADDR_LEN;
    return OK;
}
