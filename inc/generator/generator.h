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
# include "parser/ast_types.h"

# define GLOBAL_LABEL_STR "global %s\n"

# define GLOBAL_LABEL_STR_SIZE(lbl_name) (strlen(GLOBAL_LABEL_STR) + strlen(lbl_name) - 1)

# define LABEL_STR "%s:\n"

# define LABEL_STR_SIZE(lbl_name) (strlen(LABEL_STR) + strlen(lbl_name) - 1)

# define RETURN_INT_STATEMENT "    mov rax, %d\n    ret\n\n"

int generator(ast_program_t* program, const char* target);

#endif//!GENERATOR_H
