/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef AST_OPERATION_H
#define AST_OPERATION_H

# include "parser/ast_types.h"

typedef enum {
    ADDITION,
    END,
}OPERATION_TYPE;

typedef struct rpn_double_chained_list_s rpn_double_chained_list_t;

typedef struct ast_operation_s{
    rpn_double_chained_list_t* rpn_list;
}ast_operation_t;

rpn_double_chained_list_t* token_list_to_rpn(token_list_t* head);

#endif//!AST_OPERATION_H
