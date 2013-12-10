<<<<<<< HEAD
/**
 * @file monitor.h
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */
=======

/**
 * @file monitor.h
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <thread.h>
#include <semaphore.h>

#ifndef NMON
<<<<<<< HEAD
#  define NMON 0
=======
#define NMON 0
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#endif

/* Monitor state definitions */
#define MFREE 0x01 /**< this monitor is free */
#define MUSED 0x02 /**< this monitor is used */

<<<<<<< HEAD
#define NOOWNER BADTID /**< no thread owns this monitor's lock */

/** type definition of "monitor" */
=======
#define NOOWNER (-1) /**< no thread owns this monitor's lock */

/* type definition of "monitor" */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
typedef unsigned int monitor;

/**
 * Monitor table entry
 */
<<<<<<< HEAD
struct monent
{
    char state;       /**< monitor state (MFREE or MUSED)  */
    tid_typ owner;    /**< thread that owns the lock, or NOOWNER if unowned  */
    uint count;       /**< number of lock actions performed  */
    semaphore sem;    /**< semaphore used by this monitor  */
=======
struct monent                   /* monitor table entry */
{
    char state;         /**< the state MFREE or MUSED */
    tid_typ owner;              /**< the thread that owns the lock, or 0 if unowned */
    int count;                          /**< the number of lock actions performed */
    semaphore sem;              /**< the semaphore used by this monitor */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
};

extern struct monent montab[];

<<<<<<< HEAD
/** Determine if a monitor is invalid or not in use  */
=======
/* isbadmon - check validity of reqested monitor id and state */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
#define isbadmon(m) ((m >= NMON) || (MFREE == montab[m].state))

/* Monitor function prototypes */
syscall lock(monitor);
syscall unlock(monitor);
<<<<<<< HEAD
monitor moncreate(void);
syscall monfree(monitor);
syscall moncount(monitor);

#endif /* _MONITOR_H */
=======
monitor moncreate(int);
syscall monfree(monitor);
syscall moncount(monitor);

//testing
thread monitortest(void);

#endif                          /* _MONITOR_H */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
