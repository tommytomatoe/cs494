/**
 * @file monfree.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <thread.h>
#include <semaphore.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <monitor.h>

/**
 * @ingroup monitors
 *
<<<<<<< HEAD
 * Free a monitor previously allocated with moncreate().
 *
 * A monitor must only be freed when no thread has it locked -- that is, either
 * the monitor is unowned, or is owned by a thread that has been killed.
 *
 * @param mon
 *      The monitor to free.
 *
 * @return
 *      ::OK on success; ::SYSERR on failure (@p mon did not specify a valid,
 *      allocated monitor).
 */
syscall monfree(monitor mon)
{
    struct monent *monptr;
    irqmask im;

    im = disable();

    /* make sure the specified monitor is valid and allocated  */
=======
 * Deallocate a monitor.
 * Deallocate its semaphore, releasing any threads
 * in the waiting queue. Reset monitor's count. 
 * Deallocate entry in global monitor table.
 * @param mon  target monitor
 * @return OK on success, SYSERR on failure
 */
syscall monfree(monitor mon)
{
    register struct monent *monptr;
    irqmask im;

    im = disable();
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    if (isbadmon(mon))
    {
        restore(im);
        return SYSERR;
    }

    monptr = &montab[mon];
<<<<<<< HEAD

    /* free the monitor's semaphore and mark the monitor table entry as free  */
    semfree(monptr->sem);
=======
    semfree(monptr->sem);       /* deallocate the monitor's semaphore */
    monptr->owner = NOOWNER;    /* reset owner field */
    monptr->count = 0;          /* reset count for this monitor */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    monptr->state = MFREE;

    restore(im);
    return OK;
}
