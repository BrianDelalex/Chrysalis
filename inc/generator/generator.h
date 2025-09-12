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

# define ASM_MOV_INTO_RAX "    mov rax, %d\n"

# define ASM_MOV "    mov %s, %s\n"

# define ASM_ADD "    add %s, %s\n"

# define ASSIGN_STATEMENT_INTEGER_LITERAL "    mov %s, %d\n"

#  define ASSIGN_STATEMENT "    mov %s, %s\n"

int generator(ast_program_t* program, const char* target);

char** generate_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack);

int count_lines(char** lines);
void free_lines(char **lines);
char** append_line(char** lines, const char* line);

# define CHECK_LINES_RETURN_NULL()  \
    if (!lines)                     \
        return NULL;

# define CHECK_LINES_RETURN(ret_val)    \
    if (!lines)                         \
        return ret_val;

#endif//!GENERATOR_H
