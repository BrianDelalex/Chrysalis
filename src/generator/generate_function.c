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
    const char global_start[] = "global _start\n\n";
    const char start_lbl[] = "_start:\n";
    const char call_main[] = "    call main\n";
    const char mov_rdi_rax[]= "    mov rdi, rax\n";
    const char mov_rax_exit[] = "    mov rax, 60\n";
    const char syscall[] = "    syscall\n";

    if (!append_line_to_file(gen_data, global_start))
        return false;
    if (!append_line_to_file(gen_data, start_lbl))
        return false;
    if (!append_line_to_file(gen_data, call_main))
        return false;
    if (!append_line_to_file(gen_data, mov_rdi_rax))
        return false;
    if (!append_line_to_file(gen_data, mov_rax_exit))
        return false;
    if (!append_line_to_file(gen_data, syscall))
        return false;

    return true;
}

bool generate_function(gen_data_t* gen_data, ast_function_t* func)
{
    gen_func_data_t func_data;
    int global_lbl_size = GLOBAL_LABEL_STR_SIZE(func->name);
    int lbl_size = LABEL_STR_SIZE(func->name);
    char *global_lbl;
    char *lbl;

    if (strcmp("main", func->name) == 0) {
        g_main_found = true;
    }

    global_lbl = malloc(sizeof(char) * global_lbl_size);
    if (!global_lbl) {
        PERR(OUT_OF_MEM);
        return false;
    }
    if (snprintf(global_lbl, global_lbl_size, GLOBAL_LABEL_STR, func->name) < 0) {
        PERR("%s\n", strerror((errno)));
        free(global_lbl);
        return false;
    }

    if (!append_line_to_file(gen_data, global_lbl)) {
        free(global_lbl);
        return false;
    }
    free(global_lbl);

    lbl = malloc(sizeof(char) * lbl_size);
    if (!lbl) {
        PERR(OUT_OF_MEM);
        return false;
    }
    if (snprintf(lbl, lbl_size, LABEL_STR, func->name) < 0) {
        PERR("%s\n", strerror(errno));
        free(lbl);
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
