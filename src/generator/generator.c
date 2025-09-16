/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <stdbool.h>

# include "generator/generator.h"
# include "generator/function.h"

# include "files/files.h"

# include "utils/logging.h"
# include "utils/string_array.h"

bool g_main_found = false;

bool append_line_to_file(gen_data_t* gen_data, const char* line)
{
    gen_data->file = string_array_append(gen_data->file, line);
    if (!gen_data->file)
        return false;
    return true;
}

int generator(ast_program_t* program, const char* target)
{
    gen_data_t gen_data;

    gen_data.file = malloc(sizeof(char*));
    if (!gen_data.file) {
        PERR(OUT_OF_MEM);
        return -1;
    }

    gen_data.file[0] = NULL;
    g_main_found = false;

    if (!generate_function(&gen_data, program->functions))
        return -1;

    if (g_main_found) {
        if (!generate_start_function(&gen_data))
            return -1;
    }

    write_file(target, gen_data.file);
    string_array_free(gen_data.file);
    return 0;
}
