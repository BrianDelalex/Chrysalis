/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "tokenizer/token_list.h"

# include <stdlib.h>
# include <stdio.h>

const char* token_type_str[] = {
    "KEYWORD",
    "SEMICOLON",
    "CURLY_OPEN",
    "CURLY_CLOSE",
    "PARENTHESES_OPEN",
    "PARENTHESES_CLOSE",
    "IDENTIFIER",
    "INTEGER_LITERAL",
    "EQUAL",
    "PLUS",
    "UNKNOW",
};

_Static_assert((sizeof(token_type_str) / sizeof(const char*)) == UNKNOW + 1, "Error token_type_str missing value.");

token_list_t* token_list_create_node(token_list_t* head, token_type_t type, char* value)
{
    token_list_t *node = malloc(sizeof(token_list_t));

    if (!node)
        return NULL;

    node->token.type = type;
    node->token.value = value;
    node->next = NULL;

    return token_list_add_node(head, node);
}

token_list_t* token_list_add_node(token_list_t* head, token_list_t* node)
{
    token_list_t* ptr = head;

    if (!head)
        return node;

    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}

void token_list_free(token_list_t* head)
{
    token_list_t* ptr = head;

    while (head) {
        head = head->next;
        if (ptr->token.value != NULL)
            free(ptr->token.value);
        free(ptr);
        ptr = head;
    }
}

void token_list_dump(token_list_t* head)
{
    printf("Dumping token_list:\n");
    token_list_t* ptr = head;

    while (ptr) {
        printf("    type: %s, value: %s\n", token_type_str[ptr->token.type], ptr->token.value ? ptr->token.value : "NULL");
        ptr = ptr->next;
    }
}

void token_dump(token_list_t head)
{
    printf("type: %s, value: %s\n", token_type_str[head.token.type], head.token.value ? head.token.value : "N/A");
}

const char *token_type_as_str(token_type_t type)
{
    return token_type_str[type];
}
