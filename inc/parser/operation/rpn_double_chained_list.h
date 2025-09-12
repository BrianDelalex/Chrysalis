/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef RPN_DOUBLE_CHAINED_LIST_H
#define RPN_DOUBLE_CHAINED_LIST_H

typedef enum {
    OPERATOR,
    OPERAND_INT,
    OPERAND_IDENTIFIER,
}RPN_TOKEN;

typedef struct rpn_double_chained_list_s {
    RPN_TOKEN token;
    char* value;
    struct rpn_double_chained_list_s* previous;
    struct rpn_double_chained_list_s* next;
}rpn_double_chained_list_t;

rpn_double_chained_list_t* rpn_double_list_push_back(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node);
rpn_double_chained_list_t* rpn_double_list_push_front(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node);
void rpn_double_list_free(rpn_double_chained_list_t* head);
void rpn_double_list_dump(rpn_double_chained_list_t* head);
rpn_double_chained_list_t* rpn_create_node(RPN_TOKEN token, const char* value);

#endif//!RPN_DOUBLE_CHAINED_LIST_H
