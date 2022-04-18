#include <stdio.h>
#include <stdlib.h>

#include "./flags.h"
#include "./config.h"
#include "./templates.h"


int main(int argc, char *argv[]) {
    struct flg_flags flags = parse_args(argc, argv);
    if (flags->op == HELP) {
    }
    printf("Hello world!\n");

    return EXIT_SUCCESS;
}
