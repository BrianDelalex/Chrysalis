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
# include "parser/stack.h"

# include "tokenizer/token_list.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>

void dump_ast(ast_program_t* program);

ast_program_t* create_ast_struct(token_list_t* tokens)
{
    ast_program_t *program = malloc(sizeof(ast_program_t));
    if (!program)
        return NULL;
    memset(program, 0, sizeof(ast_program_t));

    ast_function_t *func = parse_function_ast(tokens);
    if (!func) {
        ast_program_free(program);
        return NULL;
    }
    program->functions = func;

    if (populate_stack_struct(program) != 0) {
        ast_program_free(program);
    }

    dump_ast(program);
    return program;
}
