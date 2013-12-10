/**
 * @file mailboxInit.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <mailbox.h>

struct mbox mboxtab[NMAILBOX];
semaphore mboxtabsem;

/**
 * @ingroup mailbox
 *
 * Initialize mailbox structures.
<<<<<<< HEAD
 *
 * @return
 *      ::OK if all mailboxes were initialized successfully, otherwise ::SYSERR.
 */
syscall mailboxInit(void)
{
    uint i;
=======
 * @return OK if all mailboxes are initialized successfully
 */
syscall mailboxInit(void)
{
    int i = 0;

    mboxtabsem = semcreate(1);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    /* set all mailbox states to MAILBOX_FREE */
    for (i = 0; i < NMAILBOX; i++)
    {
        mboxtab[i].state = MAILBOX_FREE;
    }

<<<<<<< HEAD
    mboxtabsem = semcreate(1);
    if (SYSERR == mboxtabsem)
    {
        return SYSERR;
    }

=======
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    return OK;
}
