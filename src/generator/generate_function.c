/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>

# include "generator/function.h"
# include "generator/generator.h"
# include "generator/statement.h"
# include "generator/stack/stack.h"
# include "generator/asm/generate_asm.h"

# include "utils/logging.h"

extern bool g_main_found;

bool generate_start_function(gen_data_t* gen_data)
{
    const char start_func[] =
        "global _start\n\n"     \
        "_start:\n"             \
        "    call main\n"       \
        "    mov rdi, rax\n"    \
        "    mov rax, 60\n"     \
        "    syscall\n";

    if (!append_line_to_file(gen_data, start_func))
        return false;

    return true;
}

bool generate_function(gen_data_t* gen_data, ast_function_t* func)
{
    gen_func_data_t func_data;
    char *global_lbl;
    char *lbl;

    if (strcmp("main", func->name) == 0) {
        g_main_found = true;
    }

    global_lbl = generate_global_label(func->name);
    if (!global_lbl) {
        return false;
    }

    if (!append_line_to_file(gen_data, global_lbl)) {
        free(global_lbl);
        return false;
    }
    free(global_lbl);

    lbl = generate_label_beginning(func->name);
    if (!lbl) {
        return false;
    }

    if (!append_line_to_file(gen_data, lbl)) {
        free(lbl);
        return false;
    }
    free(lbl);
    if (!generate_stack_setup(gen_data))
        return false;

    func_data.gen_data = gen_data;
    func_data.stack = func->stack;

    return generate_statements(&func_data, func->statements);
}
