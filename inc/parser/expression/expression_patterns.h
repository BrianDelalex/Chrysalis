/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef EXPRESSION_PATTERNS_H
#define EXPRESSION_PATTERNS_H

# include "parser/patterns.h"

extern const int EXPR_INTEGER_LITERAL_TOKENS[];
extern const pattern_t EXPR_INTEGER_LITERAL;

extern const int EXPR_IDENTIFIER_TOKENS[];
extern const pattern_t EXPR_IDENTIFIER;

extern const pattern_t EXPRESSION_PATTERNS[];
extern const unsigned int EXPRESSION_PATTERNS_SIZE;

#endif//!EXPRESSION_PATTERNS_H
