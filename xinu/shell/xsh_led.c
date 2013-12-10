/**
 * @file     xsh_led.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
#ifdef GPIO_BASE

=======
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
/**
 * @ingroup shell
 *
 * Shell command (led DESCRIPTOR STATE) turns a specified led on or off.
 * @param nargs number of arguments in args array
 * @param args  array of arguments
 * @return non-zero value on error
 */
shellcmd xsh_led(int nargs, char *args[])
{
    ulong led;                  /* led to control */

    /* Output help, if '--help' argument was supplied */
<<<<<<< HEAD
    if (nargs == 2 && strcmp(args[1], "--help") == 0)
=======
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        printf("Usage: %s <DESCRIPTOR> <STATE>\n\n", args[0]);
        printf("Description:\n");
        printf("\tTurns a specified led on or off.\n");
        printf("Options:\n");
        printf("\t<DESCRIPTOR>\tdmz, wlan, power, ciscow, ciscoo\n");
        printf("\t<STATE>\t\ton, off\n");
        printf("\t--help\t\tdisplay this help and exit\n");
        return 0;
    }

    /* Check for correct number of arguments */
    if (nargs < 3)
    {
        fprintf(stderr, "%s: missing operand\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return 1;
    }
    if (nargs > 3)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return 1;
    }

    led = 0;
    /* find led to change */
<<<<<<< HEAD
    if (strcmp(args[1], "dmz") == 0)
    {
        led = GPIO_LED_DMZ;
    }
    else if (strcmp(args[1], "wlan") == 0)
    {
        led = GPIO_LED_WLAN;
    }
    else if (strcmp(args[1], "power") == 0)
    {
        led = GPIO1;
    }
    else if (strcmp(args[1], "ciscow") == 0)
    {
        led = GPIO_LED_CISCOWHT;
    }
    else if (strcmp(args[1], "ciscoo") == 0)
=======
    if (strncmp(args[1], "dmz", 3) == 0)
    {
        led = GPIO_LED_DMZ;
    }
    else if (strncmp(args[1], "wlan", 4) == 0)
    {
        led = GPIO_LED_WLAN;
    }
    else if (strncmp(args[1], "power", 5) == 0)
    {
        led = GPIO1;
    }
    else if (strncmp(args[1], "ciscow", 6) == 0)
    {
        led = GPIO_LED_CISCOWHT;
    }
    else if (strncmp(args[1], "ciscoo", 6) == 0)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        led = GPIO_LED_CISCOONG;
    }
    else
    {
        fprintf(stderr, "%s: invalid DESCRIPTOR\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
    }

<<<<<<< HEAD
    /* change led state */
    if (strcmp(args[2], "on") == 0)
    {
        gpioLEDOn(led);
    }
    else if (strcmp(args[2], "off") == 0)
=======
#ifdef GPIO_BASE
    /* change led state */
    if (strncmp(args[2], "on", 2) == 0)
    {
        gpioLEDOn(led);
    }
    else if (strncmp(args[2], "off", 3) == 0)
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    {
        gpioLEDOff(led);
    }
    else
    {
        fprintf(stderr, "%s: invalid STATE\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
    }
<<<<<<< HEAD

    return 0;
}

#endif /* GPIO_BASE */
=======
#endif                          /* GPIO_BASE */

    return 0;
}
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
