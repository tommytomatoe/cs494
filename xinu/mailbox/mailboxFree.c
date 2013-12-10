/**
 * @file mailboxFree.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <mailbox.h>
#include <memory.h>
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <mailbox.h>
#include <memory.h>
#include <semaphore.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

/**
 * @ingroup mailbox
 *
<<<<<<< HEAD
 * Free the specified mailbox.
 *
 * @param box
 *      The index of the mailbox to free.
 *
 * @return
 *      ::OK if the mailbox was successfully freed, or ::SYSERR if @p box did
 *      not specify a valid allocated mailbox.
=======
 * Free a mailbox.
 * @param box the number of the mailbox to delete
 * @return OK if the mailbox was deleted successfully, otherwise SYSERR
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
 */
syscall mailboxFree(mailbox box)
{
    struct mbox *mbxptr;
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
=======
    if (MAILBOX_ALLOC != mbxptr->state)
    {
        return SYSERR;
    }
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    /* wait until other threads are done editing the mailbox table */
    wait(mboxtabsem);

<<<<<<< HEAD
    if (MAILBOX_ALLOC == mbxptr->state)
    {
        /* mark mailbox as no longer allocated  */
        mbxptr->state = MAILBOX_FREE;

        /* free semaphores related to this mailbox */
        semfree(mbxptr->sender);
        semfree(mbxptr->receiver);

        /* free memory that was used for the message queue */
        memfree(mbxptr->msgs, sizeof(int) * (mbxptr->max));

        retval = OK;
    }
    else
    {
        /* mailbox was not allocated  */
        retval = SYSERR;
    }

    /* signal that this thread is done editing the mailbox table */
    signal(mboxtabsem);

    return retval;
=======
    /* free semaphores related to this mailbox */
    if ((SYSERR == (int)semfree(mbxptr->sender))
        || (SYSERR == (int)semfree(mbxptr->receiver)))
    {
        /* signal and return SYSERR */
        signal(mboxtabsem);
        return SYSERR;
    }

    /* free memory that was used for the message queue */
    if (SYSERR == memfree(mbxptr->msgs, sizeof(int) * (mbxptr->max)))
    {
        /* signal and return SYSERR */
        signal(mboxtabsem);
        return SYSERR;
    }

    /* free this mailbox for use */
    mbxptr->state = MAILBOX_FREE;

    /* signal that this thread is done editing the mailbox table */
    signal(mboxtabsem);

    return OK;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
