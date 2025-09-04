/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "tokenizer/token_list.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>

ast_statement_t* parse_statement(token_list_t** tokens)
{
    ast_statement_t *statement;
    ast_return_statement_t *return_stat;

    if ((*tokens)->token.type != KEYWORD && strcmp((*tokens)->token.value, "return") != 0) {
        PERR("Expected 'return' keyword\n");
        return NULL;
    }
    *tokens = (*tokens)->next;
    statement = malloc(sizeof(ast_statement_t));
    if (!statement) {
        PERR("Out of memory!\n");
        return NULL;
    }
    statement->type = RETURN;

    return_stat = malloc(sizeof(ast_return_statement_t));
    if (!return_stat) {
        PERR("Out of memory!\n");
        free(statement);
        return NULL;
    }
    if ((*tokens)->token.type != INTERGER_LITERAL) {
        PERR("Expected 'integer literal' after 'return '\n");
        free(statement);
        free(return_stat);
        return NULL;
    }
    return_stat->value = atoi((*tokens)->token.value);
    statement->statement = (void *)return_stat;
    *tokens = (*tokens)->next;
    if ((*tokens)->token.type != SEMICOLON) {
        PERR("Expected ';' after 'return %d'\n", return_stat->value);
        free(return_stat);
        free(statement);
        return NULL;
    }
    *tokens = (*tokens)->next;
    return statement;
}

ast_function_t* parse_function(token_list_t* tokens)
{
    ast_function_t *func;
    token_list_t* ptr = tokens;

    if (ptr->token.type != KEYWORD) {
        PERR("Invalid token expected KEYWORD got %s with value %s\n",
            token_type_as_str(ptr->token.type),
            ptr->token.value ? ptr->token.value : "NULL");
        return NULL;
    }

    ptr = ptr->next;
    if (!ptr || ptr->token.type != IDENTIFIER) {
        if (ptr) {
            PERR("Invalid token expected IDENTIFIER got %s with value %s\n",
                   token_type_as_str(ptr->token.type),
                   ptr->token.value ? ptr->token.value : "NULL");
        }
        return NULL;
    }
    func = malloc(sizeof(ast_function_t));
    if (!func) {
        PERR("Out of memory!\n");
        return NULL;
    }
    func->name = ptr->token.value;
    ptr = ptr->next;
    if (!ptr || ptr->token.type != PARENTHESES_OPEN) {
        PERR("Expected '(' after %s identifier. Found %s\n", func->name, token_type_as_str(ptr->token.type));
        free(func);
        return NULL;
    }
    ptr = ptr->next;
    if (!ptr || ptr->token.type != PARENTHESES_CLOSE) {
        PERR("Expected ')' after '%s('.\n", func->name);
        free(func);
        return NULL;
    }
    ptr = ptr->next;
    if (!ptr || ptr->token.type != CURLY_OPEN) {
        PERR("Expected '{' after '%s()'.\n", func->name);
        free(func);
        return NULL;
    }
    ptr = ptr->next;
    func->statements = parse_statement(&ptr);
    if (!func->statements) {
        free(func);
        return NULL;
    }

    if (!ptr || ptr->token.type != CURLY_CLOSE) {
        PERR("Expected '}' after 'return'.\n");
        free(func);
        return NULL;
    }
    return func;
}

void dump_ast(ast_program_t* program)
{
    printf("<program> ::= <function>\n");
    printf("<function> ::= \"int\" <%s> \"(\" \")\" \"{\" <statement> \"}\"\n", program->functions->name);
    printf("<statement> ::= \"return\" <exp> \";\"\n");
    printf("<exp> ::= %d\n", ((ast_return_statement_t *)program->functions->statements->statement)->value);
}

ast_program_t* create_ast_struct(token_list_t* tokens)
{
    ast_program_t *program = malloc(sizeof(ast_program_t));
    if (!program)
        return NULL;

    ast_function_t *func = parse_function(tokens);
    if (!func) {
        free(program);
        return NULL;
    }
    program->functions = func;
    //dump_ast(program);
    return program;
}
