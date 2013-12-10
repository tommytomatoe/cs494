/**
 * @file     xsh_gpiostat.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>

/**
 * @ingroup shell
 *
 * Shell command (gpiostat) provides information about the current status
 * of the GPIO pins.
 * @param nargs number of arguments in args array
 * @param args  array of arguments
 * @return non-zero value on error
 */
shellcmd xsh_gpiostat(int nargs, char *args[])
{
    struct gpio_csreg *pgcsr;   /* pointer to gpio registers     */
    uchar p;
    ulong offset;

    /* Output help, if '--help' argument was supplied */
<<<<<<< HEAD
    if (nargs == 2 && strcmp(args[1], "--help") == 0)
=======
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tDisplays statitics for general purpose ");
        printf("input/output pins.\n");
        printf("Options:\n");
        printf("\t--help\t display this help and exit\n");
        return 1;
    }

    /* Check for correct number of arguments */
    if (nargs > 1)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information.\n",
                args[0]);
        return 1;
    }
#ifdef GPIO_BASE
    /* Initialize pointers */
    pgcsr = (struct gpio_csreg *)GPIO_BASE;
#else
    pgcsr = NULL;
#endif                          /* GPIO_BASE */
    if (NULL == pgcsr)
    {
        return -1;
    }

    /* Output GPIO pin status */
    printf("PIN MODE   INPUT   OUTPUT  CONTROL\n");
    printf("--- ------ ------- ------- -------\n");
    for (p = 0; p < GPIO_PIN_COUNT; p++)
    {
        offset = 1 << p;
        printf("%2d ", p);
        if (pgcsr->enable & offset)
        {
            printf(" Output ");
        }
        else
        {
            printf(" Input  ");
        }
<<<<<<< HEAD
        printf("   %1lu    ", (pgcsr->input & offset) >> p);
        printf("   %1lu    ", (pgcsr->output & offset) >> p);
        printf("   %1lu    ", (pgcsr->control & offset) >> p);
=======
        printf("   %1d    ", (pgcsr->input & offset) >> p);
        printf("   %1d    ", (pgcsr->output & offset) >> p);
        printf("   %1d    ", (pgcsr->control & offset) >> p);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
        printf("\n");
    }

    return 0;
}
