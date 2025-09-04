/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PARSER_H
#define PARSER_H

# include "parser/ast_types.h"

ast_program_t* create_ast_struct(token_list_t* tokens);

#endif//!PARSER_H
