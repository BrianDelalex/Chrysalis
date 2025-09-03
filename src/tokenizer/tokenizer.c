/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "tokenizer/tokenizer.h"

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

# include "utils/string_manipulation.h"
# include "utils/char.h"

# include "tokenizer/token_list.h"
# include "tokenizer/keywords.h"

static bool is_valid_integer_literal(char* file)
{
    for (int i = 0; file[i] && file[i] != ' ' && !IS_DELIMITER(file[i]); i++)
        if (!IS_NUM(file[i]))
            return false;
    return true;
}

static bool is_valid_identifier_or_keyword(char* file)
{
    for (int i = 0; file[i] && file[i] != ' ' && !IS_DELIMITER(file[i]); i++) {
        if (!IS_IDENTIFIER_OR_KEYWORD(file[i]))
            return false;
    }
    return true;
}

static bool is_keyword(const char* word)
{
    for (int i = 0; g_keywords[i]; i++)
        if (strcmp(word, g_keywords[i]) == 0)
            return true;
    return false;
}

static token_type_t get_word_type(const char* word)
{
    if (is_keyword(word))
        return KEYWORD;
    return IDENTIFIER;
}

static token_list_t* get_identifier_or_keyword_node(char* file, int* file_index)
{
    token_list_t* node;
    char* word;
    int word_size = 0;
    char* file_ptr = &(file[*file_index]);

    if (!is_valid_identifier_or_keyword(file_ptr))
        return NULL;

    for (; file_ptr[word_size] && file_ptr[word_size] != ' ' && !IS_DELIMITER(file_ptr[word_size]); word_size++);

    *file_index = *file_index + word_size - 1;

    word = malloc(sizeof(char) * (word_size + 1));
    if (!word)
        return NULL;
    memcpy(word, file_ptr, word_size);
    word[word_size] = 0;

    node = malloc(sizeof(token_list_t));
    if (!node) {
        free(word);
        return NULL;
    }
    node->next = NULL;
    node->token.type = get_word_type(word);
    node->token.value = word;
    return node;
}

static bool is_valid_identifier_or_keyword_start(char c)
{
    return IS_ALPHA(c) || c == '_';
}

static token_list_t* get_integer_literal_node(char* file, int* file_index)
{
    token_list_t* node;
    int word_size = 0;
    char* word;
    char* file_ptr = &(file[*file_index]);

    if (!is_valid_integer_literal(file_ptr))
        return NULL;

    for (; file_ptr[word_size] && file_ptr[word_size] != ' ' && !IS_DELIMITER(file_ptr[word_size]); word_size++);

    *file_index = *file_index + word_size - 1;

    word = malloc(sizeof(char) * (word_size + 1));
    if (!word)
        return NULL;
    memcpy(word, file_ptr, word_size);
    word[word_size] = 0;

    node = malloc(sizeof(token_list_t));
    if (!node) {
        free(word);
        return NULL;
    }
    node->next = NULL;
    node->token.type = INTERGER_LITERAL;
    node->token.value = word;

    return node;
}

static token_type_t get_delimiter_type(char c)
{
    switch (c) {
    case '{':
        return CURLY_OPEN;
    case '}':
        return CURLY_CLOSE;
    case '(':
        return PARENTHESES_OPEN;
    case ')':
        return PARENTHESES_CLOSE;
    case ';':
        return SEMICOLON;
    default:
        return UNKNOW;
    }
}

static token_list_t* get_delimiter_node(char c)
{
    token_list_t* node;

    if (!IS_DELIMITER(c))
        return NULL;

    node = malloc(sizeof(token_list_t));
    if (!node)
        return NULL;
    node->next = NULL;
    node->token.type = get_delimiter_type(c);
    node->token.value = NULL;

    return node;
}

static token_list_t* file_to_token_list(char *file)
{
    token_list_t* head = NULL;

    for (int i = 0; file[i]; i++) {
        if (file[i] == ' ')
            continue;
        if (is_valid_identifier_or_keyword_start(file[i])) {
            token_list_t* node = get_identifier_or_keyword_node(file, &i);
            if (!node) {
                token_list_free(head);
                return NULL;
            }
            head = token_list_add_node(head, node);
            continue;
        }
        if (IS_NUM(file[i])) {
            token_list_t* node = get_integer_literal_node(file, &i);
            if (!node) {
                token_list_free(head);
                return NULL;
            }
            head = token_list_add_node(head, node);
            continue;
        }
        token_list_t* node = get_delimiter_node(file[i]);
        if (!node) {
            token_list_free(head);
            return NULL;
        }
        head = token_list_add_node(head, node);
    }

    return head;
}

static char* sanitize_file(char* file)
{
    char* ptr;
    char* clean_file;

    ptr = remove_extra_spaces(file);
    if (!ptr)
        return NULL;

    clean_file = remove_newline(ptr);

    free(ptr);
    return clean_file;
}

token_list_t* tokenizer(char* file)
{
    if (!file)
        return NULL;
    char* clean_file = sanitize_file(file);

    if (!clean_file)
        return NULL;

    return file_to_token_list(clean_file);
}
