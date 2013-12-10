/**
 * @file moncount.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <semaphore.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#include <monitor.h>

/**
 * @ingroup monitors
 *
<<<<<<< HEAD
 * Retrieve the count of a monitor --- that is, the number of times it has been
 * locked by the owning thread, or 0 if no thread currently owns the monitor.
 *
 * This function performs no locking.  The caller must temporarily disable
 * interrupts if the specified monitor could potentially be freed, locked, or
 * unlocked concurrently.
 *
 * @param mon
 *      The monitor to retrieve the count of.
 *
 * @return
 *      If @p mon specified a valid, allocated monitor, its count is returned.
 *      Otherwise, ::SYSERR is returned.
=======
 * Return a monitor's count
 * @param mon    target monitor
 * @return count from montab entry on success, SYSERR on failure
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
 */
syscall moncount(monitor mon)
{
    if (isbadmon(mon))
    {
        return SYSERR;
    }

    return (montab[mon].count);
}
