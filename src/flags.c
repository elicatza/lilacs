#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdio.h>

#include "flags.h"


 /* returns initilized struct flg_flags variable with default values set */
struct flg_flags flg_init_defaults() {
    struct flg_flags flags = {
        .op = 0,
        .op_new_append = false,
        .op_template_output = false,
        .op_template_output_raw = false,
    };


    return flags;
}

/* Checks if option matches any of the operations.
 * If so it mutates the matching flags field.
 * Returns 0 on match
 * Returns 1 on no match
 * Returns 2 if has been assigned already
 * Exits if operation has already been assigned
 */
int parse_operations(int opt, struct flg_flags *flags) {

    switch (opt) {
        case 'Q':
            if (flags->op != 0) {
                return 2;
            }
            flags->op = QUERY;
            break;
        case 'N':
            if (flags->op != 0) {
                return 2;
            }
            flags->op = NEW;
            break;
        case 'T':
            if (flags->op != 0) {
                return 2;
            }
            flags->op = TEMPLATE;
            break;
        case 'h':
            if (flags->op != 0) {
                return 2;
            }
            flags->op = HELP;
            break;
        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parse_op_template(int opt, struct flg_flags *flags) {

    switch (opt) {
        case 'o':
            flags->op_template_output = true;
            break;
        case 'r':
            flags->op_template_output_raw = true;
            break;
        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parse_op_new(int opt, struct flg_flags *flags) {

    switch (opt) {
        case 'a':
            flags->op_new_append = true;
            break;
        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parse_op_query(int opt, struct flg_flags *flags) {

    switch (opt) {
        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

struct flg_flags parse_args(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Program requires an operation.\n");
        exit(EXIT_FAILURE);
    }
    /* https://github.com/weynhamz/Arch-pacman/blob/master/src/pacman/pacman.c */
    struct flg_flags flags = flg_init_defaults();

	int opt;
	int option_index = 0;
    const char *optstring = "NQThaor";
    static const struct option opts[] = {
        { "new",        no_argument,       0, 'N' },
        { "query",      no_argument,       0, 'Q' },
        { "templates",  no_argument,       0, 'T' },
        { "help",       no_argument,       0, 'h' },
        { "append",     no_argument,       0, 'a' },
        { "output",     no_argument,       0, 'o' },
        { "output_raw", no_argument,       0, 'r' },
        { 0, 0, 0, 0 }
    };

    /* Parse operations */
    while ((opt = getopt_long(argc, argv, optstring, opts, &option_index)) != -1) {
        if (opt == '?') {
            /* Character not in optstring or error */
            exit(EXIT_FAILURE);
        }
        if ((parse_operations(opt, &flags)) == 2) {
            fprintf(stderr, "You can not use more than 1 operation\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("opts: %d\n", flags.op);

	optind = 1;
    int result;
	while((opt = getopt_long(argc, argv, optstring, opts, &option_index)) != EOF) {
		if(opt == '?') {
            /* Character not in optstring or error */
            exit(EXIT_FAILURE);
		}
        
        if(parse_operations(opt, &flags) == 2) {
			/* opt is an operation */
			continue;
		}

		switch(flags.op) {
			case TEMPLATE:
				result = parse_op_template(opt, &flags);
				break;
			case NEW:
				result = parse_op_new(opt, &flags);
				break;
			case QUERY:
				result = parse_op_query(opt, &flags);
				break;
			default:
                result = 1;
				break;
		}

        if (result != 0) {
            fprintf(stderr, "ERROR: Invalid option applied to operation!\n");
            exit(1);
        }
    }
    return flags;
}

