/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef CHAR_H
#define CHAR_H

# define IS_ALPHA(c)    ((c > 64 && c < 91) || (c > 96 && c < 123))
# define IS_NUM(c)      (c > 47 && c < 58)
# define IS_IDENTIFIER_OR_KEYWORD(c) (IS_ALPHA(c) || c == '_' || IS_NUM(c))
# define IS_DELIMITER(c) (c == '{' || c == '}' || c == '(' || c == ')' || c == ';' || c == '=' || c == '+')

#endif//!CHAR_H
