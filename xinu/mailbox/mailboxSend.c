/**
 * @file mailboxSend.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

#include <stddef.h>
#include <interrupt.h>
#include <mailbox.h>

/**
 * @ingroup mailbox
 *
<<<<<<< HEAD
 * Send a message to the specified mailbox.
 *
 * @param box
 *      The index of the mailbox to send the message to.
 *
 * @param mailmsg
 *      The message to send.
 *
 * @return ::OK if the message was successfully enqueued, otherwise ::SYSERR.
 *         ::SYSERR is returned only if @p box did not specify a valid allocated
 *         mailbox or if the mailbox was freed while waiting for room in the
 *         queue.
=======
 * Send a mailmsg to a mailbox.
 * @param box the number of the mailbox to send to
 * @param mailmsg the mailmsg to send
 * @return OK if the mailmsg was enqueued, otherwise SYSERR
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
 */
syscall mailboxSend(mailbox box, int mailmsg)
{
    struct mbox *mbxptr;
    irqmask im;
<<<<<<< HEAD
    int retval;

    if (!(0 <= box && box < NMAILBOX))
=======

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
        /* wait until there is room in the mailmsg queue */
        wait(mbxptr->sender);

        /* only continue if the mailbox hasn't been freed  */
        if (MAILBOX_ALLOC == mbxptr->state)
        {
            /* write mailmsg to this mailbox's mailmsg queue */
            mbxptr->msgs[((mbxptr->start + mbxptr->count) % mbxptr->max)] =
                mailmsg;
            mbxptr->count++;

            /* signal that there is another mailmsg in the mailmsg queue */
            signal(mbxptr->receiver);

            retval = OK;
        }
    }

    restore(im);
    return retval;
=======
    if (mbxptr->state != MAILBOX_ALLOC)
    {
        return SYSERR;
    }

    /* wait until there is room in the mailmsg queue */
    wait(mbxptr->sender);

    im = disable();

    /* write mailmsg to this mailbox's mailmsg queue */
    mbxptr->msgs[((mbxptr->start + mbxptr->count) % mbxptr->max)] =
        mailmsg;
    mbxptr->count++;

    restore(im);

    /* signal that there is another mailmsg in the mailmsg queue */
    signal(mbxptr->receiver);

    return OK;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
