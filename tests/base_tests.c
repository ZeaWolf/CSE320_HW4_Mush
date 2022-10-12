#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <criterion/criterion.h>

/*
 * This just checks if mush exits normally on an empty input.
 * It is not very interesting, unfortunately.
 * It is just a place holder where something more interesting might go.
 */
Test(basecode_suite, mush_eof_test, .timeout=20)
{
    char *cmd = "ulimit -t 10; bin/mush < /dev/null";

    int code = WEXITSTATUS(system(cmd));
    cr_assert_eq(code, EXIT_SUCCESS,
                 "Program exited with %d instead of EXIT_SUCCESS",
		 code);
}
