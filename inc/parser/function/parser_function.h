/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PARSER_FUNCTION_H
#define PARSER_FUNCTION_H

# include "tokenizer/token_list.h"

void* parse_function_decl_ast(token_list_t* head);

#endif//!PARSER_FUNCTION_H
