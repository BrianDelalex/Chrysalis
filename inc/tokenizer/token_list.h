/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

typedef enum {
    KEYWORD,            // int, return, etc...
    SEMICOLON,          // ;
    CURLY_OPEN,         // {
    CURLY_CLOSE,        // }
    PARENTHESES_OPEN,   // (
    PARENTHESES_CLOSE,  // )
    IDENTIFIER,         // [a-zA-Z] (main for example)
    INTEGER_LITERAL,   // [0-9]+
    EQUAL,             // =
    PLUS,              // +
    COMMA,             // ,
    UNKNOW,            // The type of the token is unknow to the compiler. This value MUST always be the last of the list.
}token_type_t;

typedef struct token_s {
    token_type_t type;
    char* value;
} token_t;

typedef struct token_list_s {
    struct token_s token;
    struct token_list_s* next;
} token_list_t;

token_list_t* token_list_create_node(token_list_t* head, token_type_t type, char* value);
token_list_t* token_list_add_node(token_list_t* head, token_list_t* node);
void token_list_free(token_list_t* head);
void token_list_dump(token_list_t* head);
void token_dump(token_list_t head);
const char *token_type_as_str(token_type_t type);

#endif//!TOKEN_LIST_H
