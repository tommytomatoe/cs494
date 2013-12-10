/**
 * @file moncreate.c
<<<<<<< HEAD
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <monitor.h>
=======
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <monitor.h>
#include <semaphore.h>
#include <interrupt.h>
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

static monitor monalloc(void);

/**
 * @ingroup monitors
 *
<<<<<<< HEAD
 * Create and initialize a new monitor.
 *
 * @return
 *      On success, returns the new monitor.  On failure (system is out of
 *      monitors or semaphores), returns ::SYSERR.
 */
monitor moncreate(void)
{
    irqmask im;
    monitor mon;
    struct monent *monptr;

    /* Disable interrupts.  */
    im = disable();

    /* Allocate entry in monitor table.  */
    mon = monalloc();

    if (SYSERR != mon)
    {
        monptr = &montab[mon];

        /* Monitors initially have no owner and zero count.  */
        monptr->owner = NOOWNER;
        monptr->count = 0;

        /* Initialize the monitor's semaphore with a count of 1, allowing one
         * thread to acquire the monitor.  */
        monptr->sem = semcreate(1);
        if (SYSERR == monptr->sem)
        {
            monptr->state = MFREE;
            mon = SYSERR;
        }
    }

    /* Restore interrupts.  */
    restore(im);

    /* Return monitor table index or SYSERR.  */
    return mon;
}

/* Returns the index of an unused monitor table entry, or SYSERR if none are
 * available.  */
static monitor monalloc(void)
{
#if NMON
    int i;
    static int nextmon = 0;

    /* Check all NMON slots, starting at 1 past the last slot searched.  */
    for (i = 0; i < NMON; i++)
=======
 * Create and initialize a monitor, returning its ID.
 * @param count  resources available.
 * @return new monitor ID on success, SYSERR on failure
 */
monitor moncreate(int count)
{
    //register semaphore sem;
    register monitor mon;
    irqmask im;

    im = disable();             /* disable interrupts    */
    mon = monalloc();           /* request new monitor */
    if (mon != SYSERR && count >= 0)    /* safety check          */
    {
        //probably dont have to initialize to 0 since all monitors
        //will always start with their count equal to 0
        montab[mon].count = 0;
        montab[mon].owner = NOOWNER;    /* no one owns a new monitor */
        montab[mon].sem = semcreate(count);     /* initialize semaphore  */
        restore(im);            /* restore interrupts    */
        return mon;             /* return monitor id   */
    }

    restore(im);
    return SYSERR;
}

/**
 * Allocate an unused monitor and return its ID.
 * Scan the global monitor table for a free entry, mark the entry
 * used, and return the new monitor
 * @return available monitor ID on success, SYSERR on failure
 */
static monitor monalloc(void)
{
#if NMON
    int mon = 0;                /* monitor to return */
    static int nextmon = 0;

    /* check all NMON slots */
    for (mon = 0; mon < NMON; mon++)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        nextmon = (nextmon + 1) % NMON;
        if (MFREE == montab[nextmon].state)
        {
            montab[nextmon].state = MUSED;
            return nextmon;
        }
    }
<<<<<<< HEAD
#endif
=======
#endif                          /* NMON */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    return SYSERR;
}
