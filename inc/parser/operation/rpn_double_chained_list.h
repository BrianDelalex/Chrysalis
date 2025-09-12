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

# include <stdint.h>

typedef enum {
    OPERATOR,
    OPERAND_INT,
    OPERAND_IDENTIFIER,
}RPN_TOKEN;

typedef union union_identifier_value_u {
    char* identifier;
    uint64_t value;
}union_identifier_value_t;

typedef struct rpn_double_chained_list_s {
    RPN_TOKEN token;
    union_identifier_value_t data;
    struct rpn_double_chained_list_s* previous;
    struct rpn_double_chained_list_s* next;
}rpn_double_chained_list_t;

rpn_double_chained_list_t* rpn_double_list_push_back(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node);
rpn_double_chained_list_t* rpn_double_list_push_front(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node);
rpn_double_chained_list_t* rpn_double_list_pop_front(rpn_double_chained_list_t** head);
void rpn_double_list_free(rpn_double_chained_list_t* head);
void rpn_double_list_dump(rpn_double_chained_list_t* head);
rpn_double_chained_list_t* rpn_create_node(RPN_TOKEN token, union_identifier_value_t _union);

#endif//!RPN_DOUBLE_CHAINED_LIST_H
