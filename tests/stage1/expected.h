#ifndef EXPECTED_H
#define EXPECTED_H

# include "tokenizer/token_list.h"

# include <stddef.h>

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
