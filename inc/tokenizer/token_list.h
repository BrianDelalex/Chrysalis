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
    INTERGER_LITERAL,   // [0-9]+
    UNKNOW,
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

#endif//!TOKEN_LIST_H
