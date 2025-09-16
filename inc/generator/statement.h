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

# include <stdbool.h>

# include "generator/function.h"

typedef struct ast_statement_s ast_statement_t;
typedef struct ast_stack_s ast_stack_t;

bool generate_assignment_statement(gen_func_data_t* data, ast_statement_t* statement);

bool generate_return_statement(gen_func_data_t* data, ast_statement_t* statement);

bool generate_statements(gen_func_data_t* gen_data, ast_statement_t* statement_list);


#endif//!GENERATOR_STATEMENT_H
