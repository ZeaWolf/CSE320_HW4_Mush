#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "mush.h"

int main(int argc, char *argv[]) {
    jobs_init();
    exec_interactive();
    jobs_fini();
}
