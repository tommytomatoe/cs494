/**
 * @file lock.c
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
 * Lock a monitor.
 *
 * If no thread owns the monitor, its owner is set to the current thread and its
 * count is set to 1.
 *
 * If the current thread already owns the monitor, its count is incremented and
 * no further action is taken.
 *
 * If another thread owns the monitor, the current thread waits for the monitor
 * to become fully unlocked by that thread, then sets its owner to the current
 * thread and its count to 1.
 *
 * @param mon
 *      The monitor to lock.
 *
 * @return
 *      ::OK on success; ::SYSERR on failure (@p mon did not specify a valid,
 *      allocated monitor).
 */
syscall lock(monitor mon)
{
    struct monent *monptr;
=======
 * Current thread attempts to grab the lock on a monitor.
 * If another thread does not hold the lock the current thread owns the lock
 * and increases the monitor's count by one. Otherwise, the thread waits.
 * @param mon  target monitor
 * @return OK on success, SYSERR on failure
 */
syscall lock(monitor mon)
{
    register struct monent *monptr;
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    irqmask im;

    im = disable();
    if (isbadmon(mon))
    {
        restore(im);
        return SYSERR;
    }

    monptr = &montab[mon];

    /* if no thread owns the lock, the current thread claims it */
    if (NOOWNER == monptr->owner)
    {
<<<<<<< HEAD
        monptr->owner = thrcurrent;     /* current thread now owns the lock  */
=======
        monptr->owner = thrcurrent;     /* current thread now owns the lock    */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
        (monptr->count)++;      /* add 1 "lock" to the monitor's count */
        wait(monptr->sem);      /* this thread owns the semaphore      */
    }
    else
    {
        /* if current thread owns the lock increase count; dont wait on sem */
        if (thrcurrent == monptr->owner)
        {
            (monptr->count)++;
        }
        /* if another thread owns the lock, wait on sem until monitor is free */
        else
        {
            wait(monptr->sem);
            monptr->owner = thrcurrent;
            (monptr->count)++;

        }
    }

    restore(im);
    return OK;
}
