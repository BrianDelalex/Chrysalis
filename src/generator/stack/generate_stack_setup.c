/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "generator/generator.h"
# include "generator/stack/stack.h"

bool generate_stack_setup(gen_data_t* gen_data)
{
    const char *push_rbp = "    push rbp\n    mov rbp, rsp\n\n";
    return append_line_to_file(gen_data, push_rbp);
}

bool generate_stack_restore(gen_data_t* gen_data)
{
    const char *pop_rbp = "    mov rsp, rbp\n    pop rbp\n";
    return append_line_to_file(gen_data, pop_rbp);
}
