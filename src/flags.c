// error: only one operation may be used at a time
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "flags.h"


struct flg_flags flg_init_defaults() {
    struct flg_flags flags = {
        .operation = {
            .query = false,
            .new = false,
            .templates = false,
            .version = false,
            .help = false,
        },
        .options = {
            .help = false,
        },
        .new_options = {
            .append = false,
        },
        .query_options = {
        },
        .template_options = {
            .output = false,
            .output_raw = false,
        },
    };


    return flags;
}

struct flg_flags parse_args(int argc, char *argv[]) {

    // https://github.com/weynhamz/Arch-pacman/blob/master/src/pacman/pacman.c
    struct flg_flags flags = flg_init_defaults();

    static struct option long_options[] = {
        { "hsl",        no_argument,        NULL,  'N' },
        { "hsv",        no_argument,        NULL,  'Q' },
        { "rgb",        no_argument,        NULL,  'T' },
        { "fields",     required_argument,  NULL,  'V' },
        { "fields",     required_argument,  NULL,  'h' },
        { 0,            0,                  0,      0  }
    };


    int option;
    int option_index = 0;
    int i;

    while ((option = getopt_long(argc, argv, "F:lvr", long_options, &option_index)) != EOF) { 
        switch (option) {

            case 'l':
                flags.hsl = true;
                break;

            case 'v': 
                flags.hsv = true;
                break;

            case 'r': 
                flags.rgb = true;
                break;

            case 'F': 
                /* Disable all fields */
                for (i = 0; i < FIELD_COUNT; ++i) {
                    flags.active_fields[i] = false;
                }

                int user_args[FIELD_COUNT];
                char user_field_args[FIELD_COUNT + 1] = {'\0'};

                sscanf(optarg, "%3[1-3]", user_field_args);
                if (errno != 0) {
                    fprintf(stderr, "Error parsing active fields: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }

                if (strlen(optarg) == strlen(user_field_args)) {
                    /* Enable active fields based on user input */
                    for (i = 0; i < strlen(user_field_args); ++i) {
                        user_args[i] = user_field_args[i] - '0';
                        if (user_args[i] <= FIELD_COUNT) {
                            flags.active_fields[user_args[i] - 1] = true;
                        }
                    }

                } else {
                    fprintf(stderr, "Field argument has to be in range [1-%d]\n", FIELD_COUNT);
                    exit(EXIT_FAILURE);
                }

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", option);

        }
    }

    return flags;
}
