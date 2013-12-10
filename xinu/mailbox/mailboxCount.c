/**
 * @file mailboxCount.c
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
 * Retrieve the number of outstanding messages in the specified mailbox.
 *
 * @param box
 *      The index of the mailbox for which to retrieve the number of outstanding
 *      messages.
 *
 * @return
 *      The number of messages in the mailbox, or ::SYSERR if @p box did not
 *      specify a valid allocated mailbox.
 */
syscall mailboxCount(mailbox box)
{
    const struct mbox *mbxptr;
    irqmask im;
    int retval;

    if (!(0 <= box && box < NMAILBOX))
=======
 * Count the number of messages in a mailbox.
 * @param box the number of the mailbox to count
 * @return count of messages in mailbox, SYSERR if error occured
 */
syscall mailboxCount(mailbox box)
{
    struct mbox *mbxptr;
    irqmask im;
    uint count;

    if (box >= NMAILBOX)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        return SYSERR;
    }

    mbxptr = &mboxtab[box];
<<<<<<< HEAD
    im = disable();
    if (MAILBOX_ALLOC == mbxptr->state)
    {
        retval = mbxptr->count;
    }
    else
    {
        retval = SYSERR;
    }
    restore(im);
    return retval;
=======
    if (mbxptr->state != MAILBOX_ALLOC)
    {
        return SYSERR;
    }

    im = disable();
    count = mbxptr->count;
    restore(im);

    return count;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
