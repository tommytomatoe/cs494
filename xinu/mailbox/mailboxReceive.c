/**
 * @file mailboxReceive.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <interrupt.h>
#include <mailbox.h>

/**
 * @ingroup mailbox
 *
<<<<<<< HEAD
 * Receive a message from the specified mailbox.
 *
 * @param box
 *      The index of the mailbox to receive the message from.
 *
 * @return
 *      On success, returns the message that was dequeued; on failure (@p box
 *      did not specify an allocated mailbox, or the mailbox was freed while
 *      waiting for a message) returns ::SYSERR.  Note that it may be impossible
 *      to disambiguate ::SYSERR from a successful return value.
=======
 * Receive a mailmsg from a mailbox.
 * @param box the number of the mailbox to receive from
 * @return the mailmsg that was dequeued, otherwise SYSERR
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
 */
syscall mailboxReceive(mailbox box)
{
    struct mbox *mbxptr;
<<<<<<< HEAD
    irqmask im;
    int retval;

    if (!(0 <= box && box < NMAILBOX))
=======
    int mailmsg;
    irqmask im;

    if (box >= NMAILBOX)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        return SYSERR;
    }

    mbxptr = &mboxtab[box];
<<<<<<< HEAD
    im = disable();
    retval = SYSERR;
    if (MAILBOX_ALLOC == mbxptr->state)
    {
        /* wait until there is a mailmsg in the mailmsg queue */
        wait(mbxptr->receiver);

        /* only continue if the mailbox hasn't been freed  */
        if (MAILBOX_ALLOC == mbxptr->state)
        {
            /* recieve the first mailmsg in the mailmsg queue */
            retval = mbxptr->msgs[mbxptr->start];

            mbxptr->start = (mbxptr->start + 1) % mbxptr->max;
            mbxptr->count--;

            /* signal that there is another empty space in the mailmsg queue */
            signal(mbxptr->sender);
        }
    }

    restore(im);
    return retval;
=======
    if (MAILBOX_ALLOC != mbxptr->state)
    {
        return SYSERR;
    }

    /* wait until there is a mailmsg in the mailmsg queue */
    wait(mbxptr->receiver);

    im = disable();

    /* recieve the first mailmsg in the mailmsg queue */
    mailmsg = mbxptr->msgs[mbxptr->start];

    mbxptr->start = (mbxptr->start + 1) % mbxptr->max;
    mbxptr->count--;

    restore(im);

    /* signal that there is another empty space in the mailmsg queue */
    signal(mbxptr->sender);

    return mailmsg;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
