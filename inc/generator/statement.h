/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATOR_STATEMENT_H
#define GENERATOR_STATEMENT_H

typedef struct ast_statement_s ast_statement_t;
typedef struct ast_stack_s ast_stack_t;

char** generate_assignment_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack);

char** generate_return_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack);

#endif//!GENERATOR_STATEMENT_H
