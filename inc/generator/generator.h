/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

# include <string.h>
# include <stdbool.h>
# include "parser/ast_types.h"

int generator(ast_program_t* program, const char* target);

typedef struct gen_data_s gen_data_t;
bool append_line_to_file(gen_data_t* gen_data, const char* line);

# define CHECK_FILE_RETURN_NULL(file)   \
    if (!file)                          \
        return NULL;

# define CHECK_FILE_RETURN(file, ret_val)   \
    if (!file)                              \
        return ret_val;

typedef struct gen_data_s {
    char** file;
}gen_data_t;

#endif//!GENERATOR_H
