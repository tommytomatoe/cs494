#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tty.h>
#include <testsuite.h>
#include <interrupt.h>

#define MAX_STR 50

/**
 * Tests the TTY driver.
 * @return OK when testing is complete
 */
thread test_ttydriver(bool verbose)
{
<<<<<<< HEAD
#if defined(LOOP0) && defined(TTYLOOP)
=======
#if LOOP && TTYLOOP
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    char str[MAX_STR];
    uchar iflags, oflags;
    int i, max;
    bool passed = TRUE;

<<<<<<< HEAD
    open(LOOP0);
    open(TTYLOOP, LOOP0);
=======
    open(LOOP);
    open(TTYLOOP, LOOP);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0

    iflags = control(TTYLOOP, TTY_CTRL_CLR_IFLAG,
                     TTY_IRAW | TTY_ECHO | TTY_ICRNL |
                     TTY_IGNCR | TTY_INLCR, NULL);
    oflags = control(TTYLOOP, TTY_CTRL_CLR_OFLAG, TTY_OCRNL, NULL);
    oflags |= control(TTYLOOP, TTY_CTRL_SET_OFLAG, TTY_ONLCR, NULL);

    /* Write */
    testPrint(verbose, "Write");
    write(TTYLOOP, "This is a sentence.", 19);
<<<<<<< HEAD
    read(LOOP0, str, 19);
=======
    read(LOOP, str, 19);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    failif((0 != strncmp(str, "This is a sentence.", 19)), "");

    /* Write: cook LF and CR */
    testPrint(verbose, "Write: cook LF and CR");
    write(TTYLOOP, "line1\r\nline2\rline3\nline4", 24);
<<<<<<< HEAD
    read(LOOP0, str, 26);
=======
    read(LOOP, str, 26);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    failif(0 != strncmp(str, "line1\r\r\nline2\rline3\r\nline4", 26), "");

    /* Write: cook backsapce/delete */
    testPrint(verbose, "Write: cook backspace/delete");
    write(TTYLOOP, "first\bsecond", 12);
<<<<<<< HEAD
    read(LOOP0, str, 12);
=======
    read(LOOP, str, 12);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    failif(0 != strncmp(str, "first\bsecond", 12), "");

    /* Read */
    testPrint(verbose, "Read");
<<<<<<< HEAD
    write(LOOP0, "Line1\nLine2\n", 12);
=======
    write(LOOP, "Line1\nLine2\n", 12);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 40);
    if (0 != strncmp(str, "Line1\n", 6))
    {
        testFail(verbose, "");
        passed = FALSE;
    }
    else
    {
        read(TTYLOOP, str, 40);
        if (0 != strncmp(str, "Line2\n", 6))
        {
            testFail(verbose, "");
            passed = FALSE;
        }
        else
        {
            testPass(verbose, "");
        }
    }

    /* Read: raw */
    testPrint(verbose, "Read: raw");
    control(TTYLOOP, TTY_CTRL_SET_IFLAG, TTY_IRAW, NULL);
<<<<<<< HEAD
    write(LOOP0, "LINEA\nLINEB\n", 12);
=======
    write(LOOP, "LINEA\nLINEB\n", 12);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 12);
    control(TTYLOOP, TTY_CTRL_CLR_IFLAG, TTY_IRAW, NULL);
    failif(0 != strncmp(str, "LINEA\nLINEB\n", 12), "");

    /* Read EOF */
    testPrint(verbose, "Read: EOF");
<<<<<<< HEAD
    write(LOOP0, "Before", 6);
    putc(LOOP0, 0x04);
    write(LOOP0, "After\n", 6);
=======
    write(LOOP, "Before", 6);
    putc(LOOP, 0x04);
    write(LOOP, "After\n", 6);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 10);
    if ((0 != strncmp(str, "Before", 6))
        || (EOF != read(TTYLOOP, str, 10)))
    {
        testFail(verbose, "");
        passed = FALSE;
    }
    else
    {
        read(TTYLOOP, str, 10);
        if (0 != strncmp(str, "After\n", 6))
        {
            testFail(verbose, "");
            passed = FALSE;
        }
        else
        {
            testPass(verbose, "");
        }
    }

    /* Read: cook backsapce/delete */
    testPrint(verbose, "Read: cook backspace/delete");
<<<<<<< HEAD
    write(LOOP0, "ones\btoo\b\bwo\n", 13);
=======
    write(LOOP, "ones\btoo\b\bwo\n", 13);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 7);
    failif(0 != strncmp(str, "onetwo\n", 7), "");

    /* Read: convert NL to CR (INLCR flag set) */
    testPrint(verbose, "Read: convert NL to CR");
    control(TTYLOOP, TTY_CTRL_SET_IFLAG, TTY_INLCR, NULL);
<<<<<<< HEAD
    write(LOOP0, "abc\n", 4);
=======
    write(LOOP, "abc\n", 4);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 10);
    control(TTYLOOP, TTY_CTRL_CLR_IFLAG, TTY_INLCR, NULL);
    failif(0 != strncmp(str, "abc\r", 4), "");

    /* Read: ignore CR (IGNCR flag set) */
    testPrint(verbose, "Read: ignore CR");
    control(TTYLOOP, TTY_CTRL_SET_IFLAG, TTY_IGNCR, NULL);
<<<<<<< HEAD
    write(LOOP0, "one\rtwo\n", 8);
=======
    write(LOOP, "one\rtwo\n", 8);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    read(TTYLOOP, str, 10);
    control(TTYLOOP, TTY_CTRL_CLR_IFLAG, TTY_IGNCR, NULL);
    failif(0 != strncmp(str, "onetwo\n", 7), "");

    /* Read: convert CR to NL (ICRNL flag set) */
    bzero(str, MAX_STR);
    max = 8;
    testPrint(verbose, "Read: convert CR to NL");
    control(TTYLOOP, TTY_CTRL_SET_IFLAG, TTY_ICRNL, NULL);
<<<<<<< HEAD
    write(LOOP0, "123\r456\n", 8);
=======
    write(LOOP, "123\r456\n", 8);
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    for (i = 0; i < max;)
    {
        i += read(TTYLOOP, str + i, max - i);
    }
    control(TTYLOOP, TTY_CTRL_CLR_IFLAG, TTY_ICRNL, NULL);
    failif(0 != strncmp(str, "123\n456\n", 8), "");

    control(TTYLOOP, TTY_CTRL_SET_IFLAG, iflags, NULL);
    control(TTYLOOP, TTY_CTRL_CLR_OFLAG, TTY_ONLCR, NULL);
    control(TTYLOOP, TTY_CTRL_SET_OFLAG, oflags, NULL);

    if (passed)
    {
        testPass(TRUE, "");
    }
    else
    {
        testFail(TRUE, "");
    }

    close(TTYLOOP);
<<<<<<< HEAD
    close(LOOP0);
#else /* defined(LOOP0) && defined(TTYLOOP) */
    testSkip(TRUE, "");
#endif /* !defined(LOOP0) || !defined(TTYLOOP) */
=======
    close(LOOP);
#else /* LOOP && TTYLOOP */
    testSkip(TRUE, "");
#endif /* !(LOOP && TTYLOOP) */
>>>>>>> bcd791d9b8645ffb0c3709c8a162ca8a5242a9a0
    return OK;
}
