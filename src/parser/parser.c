/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/parser.h"
# include "parser/ast_types.h"

# include "tokenizer/token_list.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>

static void dump_ast(ast_program_t* program)
{
    printf("<program> ::= <function>\n");
    printf("<function> ::= \"int\" <%s> \"(\" \")\" \"{\" <statement> \"}\"\n", program->functions->name);
    if (program->functions->statements->type == RETURN) {
        printf("<statement> ::= \"return\" <exp> \";\"\n");
        ast_statement_return_t* statement = (ast_statement_return_t*)program->functions->statements->statement;
        if (statement->expr.op.type == OP_IDENTIFIER) {
            printf("<exp> ::= %s\n", ((ast_operand_identifier_t*)statement->expr.op.operand)->identifier);
        } else {
            printf("<exp> ::= %d\n", ((ast_operand_integer_integral_t *)statement->expr.op.operand)->value);
        }
    } else if (program->functions->statements->type == ASSIGN) {
        ast_statement_assign_t* statement = (ast_statement_assign_t*)program->functions->statements->statement;
        printf("<statement> ::= \"assign\" <var> <exp> \";\"\n");
        printf("<var> ::= %s \"=\" <expr>\n", statement->var.identifier);
        printf("<expr> ::= %d\n", ((ast_operand_integer_integral_t*)statement->expr.op.operand)->value);
    }
}

ast_program_t* create_ast_struct(token_list_t* tokens)
{
    ast_program_t *program = malloc(sizeof(ast_program_t));
    if (!program)
        return NULL;
    memset(program, 0, sizeof(ast_program_t));

    ast_function_t *func = get_function_ast(tokens);
    if (!func) {
        ast_program_free(program);
        return NULL;
    }
    program->functions = func;
    dump_ast(program);
    return program;
}
