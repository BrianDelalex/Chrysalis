/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stddef.h>
# include <stdlib.h>
# include <string.h>

# include "parser/operation/rpn_double_chained_list.h"

# include "utils/string_manipulation.h"
# include "utils/logging.h"

rpn_double_chained_list_t* rpn_double_list_push_back(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node)
{
    rpn_double_chained_list_t* ptr = head;
    if (!head) {
        node->previous = NULL;
        node->next = NULL;
        return node;
    }

    while (ptr->next) {
        ptr = ptr->next;
    }

    ptr->next = node;
    node->previous = ptr;

    return head;
}

rpn_double_chained_list_t* rpn_double_list_push_front(rpn_double_chained_list_t* head, rpn_double_chained_list_t* node)
{
    node->next = head;
    node->previous = NULL;

    return node;
}

void rpn_double_list_free(rpn_double_chained_list_t* head)
{
    rpn_double_chained_list_t* ptr = head;

    while (ptr) {
        free(ptr->value);
        head = ptr->next;
        free(ptr);
        ptr = head;
    }
}

void rpn_double_list_dump(rpn_double_chained_list_t* head)
{
    while (head) {
        printf("%s ", head->value);
        head = head->next;
    }
    printf("\n");
}

rpn_double_chained_list_t* rpn_create_node(RPN_TOKEN token, const char* value)
{
    rpn_double_chained_list_t* node = malloc(sizeof(rpn_double_chained_list_t));

    if (!node) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(node, 0, sizeof(rpn_double_chained_list_t));
    node->token = token;
    node->value = copy_string(value);
    if (!node->value) {
        free(node);
        return NULL;
    }
    return node;
}
