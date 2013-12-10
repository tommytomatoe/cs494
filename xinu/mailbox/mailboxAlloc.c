/**
 * @file mailboxAlloc.c
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
#include <memory.h>

/**
 * @ingroup mailbox
 *
<<<<<<< HEAD
 * Allocate a mailbox that allows up to the specified number of outstanding
 * messages.
 *
 * @param count
 *      Maximum number of messages allowed for the mailbox.
 *
 * @return
 *      The index of the newly allocated mailbox, or ::SYSERR if all mailboxes
 *      are already in use or other resources could not be allocated.
 */
syscall mailboxAlloc(uint count)
{
    static uint nextmbx = 0;
    uint i;
    struct mbox *mbxptr;
    int retval = SYSERR;
=======
 * Allocate a mailbox that allows count outstanding messages.
 * @param count maximum number of messages allowed for the mailbox
 * @return the number of the mailbox, SYSERR if none are available
 */
syscall mailboxAlloc(uint count)
{
    static int nextmbx = 0;
    struct mbox *mbxptr;
    ushort i = 0;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    /* wait until other threads are done editing the mailbox table */
    wait(mboxtabsem);

    /* run through all mailboxes until we find a free one */
    for (i = 0; i < NMAILBOX; i++)
    {
        nextmbx = (nextmbx + 1) % NMAILBOX;
<<<<<<< HEAD
        mbxptr = &mboxtab[nextmbx];

        /* when we find a free mailbox set that one up and return it */
        if (MAILBOX_FREE == mbxptr->state)
        {
=======
        /* when we find a free mailbox set that one up and return it */
        if (MAILBOX_FREE == mboxtab[nextmbx].state)
        {
            mbxptr = &mboxtab[nextmbx];

>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
            /* get memory space for the message queue */
            mbxptr->msgs = memget(sizeof(int) * count);

            /* check if memory was allocated correctly */
            if (SYSERR == (int)mbxptr->msgs)
            {
<<<<<<< HEAD
                break;
            }

            /* initialize mailbox details and semaphores */
            mbxptr->count = 0;
            mbxptr->start = 0;
            mbxptr->max = count;
            mbxptr->sender = semcreate(count);
            mbxptr->receiver = semcreate(0);
            if ((SYSERR == (int)mbxptr->sender) ||
                (SYSERR == (int)mbxptr->receiver))
=======
                /* signal and return SYSERR */
                signal(mboxtabsem);
                return SYSERR;
            }

            /* initialize mailbox details and semaphores */
            mbxptr->max = count;

            mbxptr->sender = semcreate(count);
            mbxptr->receiver = semcreate(0);
            if ((SYSERR ==
                 (int)mbxptr->sender)
                || (SYSERR == (int)mbxptr->receiver))
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
            {
                memfree(mbxptr->msgs, sizeof(int) * (mbxptr->max));
                semfree(mbxptr->sender);
                semfree(mbxptr->receiver);
<<<<<<< HEAD
                break;
            }
=======
                return SYSERR;
            }
            mbxptr->count = 0;
            mbxptr->start = 0;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

            /* mark this mailbox as being used */
            mbxptr->state = MAILBOX_ALLOC;

<<<<<<< HEAD
            /* return value is index of the allocated mailbox */
            retval = nextmbx;
            break;
        }
    }

    /* signal this thread is done editing the mbox tab */
    signal(mboxtabsem);

    /* return either SYSERR or the index of the allocated mailbox */
    return retval;
=======
            /* signal this thread is done editing the mbox tab */
            signal(mboxtabsem);

            /* return the this entry in the mboxtab */
            return nextmbx;
        }
    }

    /* signal and return SYSERR because we didn't find a free spot */
    signal(mboxtabsem);
    return SYSERR;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
}
