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

char** generate_stack_setup(char** lines)
{
    const char *push_rbp = "    push rbp\n    mov rbp, rsp\n\n";
    lines = append_line(lines, push_rbp);
    return lines;
}

char** generate_stack_restore(char** lines)
{
    const char *pop_rbp = "    mov rsp, rbp\n    pop rbp\n";
    lines = append_line(lines, pop_rbp);
    return lines;
}
