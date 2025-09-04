/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef EXPECTED_H
#define EXPECTED_H

# include "tokenizer/token_list.h"
# include "parser/ast_types.h"

# include <stddef.h>

/* expected main_return_0 */

ast_return_statement_t return_statement_main_return_0_expected = {
    .value = 0
};

ast_statement_t statement_main_return_0_expected = {
    .type = RETURN,
    .statement = (void*) &return_statement_main_return_0_expected};

ast_function_t func_main_return_0_expected = {
    .statements = &statement_main_return_0_expected,
    .name = "main"
};

ast_program_t prg_main_return_0_expected = {
    .functions = &func_main_return_0_expected,
};
/* End expected main_return_0 */

/* expected main_return_42 */

ast_return_statement_t return_statement_main_return_42_expected = {
    .value = 42
};

ast_statement_t statement_main_return_42_expected = {
    .type = RETURN,
    .statement = (void*) &return_statement_main_return_42_expected,
};

ast_function_t func_main_return_42_expected = {
    .statements = &statement_main_return_42_expected,
    .name = "main"
};

ast_program_t prg_main_return_42_expected = {
    .functions = &func_main_return_42_expected,
};
/* End expected main_return_42 */

/* expected no_main */

ast_statement_t statement_no_main_expected = {
    .type = RETURN,
    .statement = (void*) &return_statement_main_return_0_expected,

};

ast_function_t func_no_main_expected = {
    .statements = &statement_no_main_expected,
    .name = "func"
};

ast_program_t prg_no_main_expected = {
    .functions = &func_no_main_expected,
};
/* End expected no_main */

const token_t main_return_0_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};


const token_t main_return_42_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "42",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t no_main_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "func",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t main_extra_spaces_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t main_missing_closing_parenthesis_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t main_missing_opening_parenthesis_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t main_missing_closing_curly_bracket_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        }
};

const token_t main_missing_opening_curly_bracket_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = SEMICOLON,
            .value = NULL,
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

const token_t main_missing_semicolon_expected[] = {
        {
            .type = KEYWORD,
            .value = "int",
        },
        {
            .type = IDENTIFIER,
            .value = "main",
        },
        {
            .type = PARENTHESES_OPEN,
            .value = NULL,
        },
        {
            .type = PARENTHESES_CLOSE,
            .value = NULL,
        },
        {
            .type = CURLY_OPEN,
            .value = NULL,
        },
        {
            .type = KEYWORD,
            .value = "return",
        },
        {
            .type = INTERGER_LITERAL,
            .value = "0",
        },
        {
            .type = CURLY_CLOSE,
            .value = NULL,
        }
};

#endif//!EXPECTED_H
