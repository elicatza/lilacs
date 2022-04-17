#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

struct flg_oparations {
    bool new;
    bool query;
    bool templates;
    bool help;
    bool version;
};

struct flg_options {
    bool help;
};

struct flg_new_options {
    bool append;
};

struct flg_query_options {
};

struct flg_template_options {
    bool output;
    bool output_raw;
};

struct flg_flags {
    struct flg_oparations operation;
    struct flg_options options;
    struct flg_new_options new_options;
    struct flg_query_options query_options;
    struct flg_template_options template_options;
};


#endif
