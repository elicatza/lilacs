#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>


enum flg_operations {
    HELP = 1,
    NEW,
    QUERY,
    TEMPLATE,
};

struct flg_flags {
    enum flg_operations op;

    bool op_new_append;
    bool op_template_output;
    bool op_template_output_raw;
};

struct flg_flags parse_args(int argc, char *argv[]);



#endif
