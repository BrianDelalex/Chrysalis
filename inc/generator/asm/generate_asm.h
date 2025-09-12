/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATE_ASM_H
#define GENERATE_ASM_H

# define GENERATE_STRING(str, fmt, args...)  \
    int _size = snprintf(NULL, 0, fmt, ## args);        \
    str = malloc(sizeof(char) * (_size + 1));           \
    if (!str) {                                        \
        PERR(OUT_OF_MEM);                              \
        return NULL;                                   \
        }                                              \
    if (snprintf(str, _size + 1, fmt, ## args) < 0) {   \
        PERR("%s", strerror(errno));                        \
        free(str);                                          \
        return NULL;                                        \
    }                                                       \

char* generate_asm_mov(const char* to, const char* from);
char* generate_integer_literal(int value);

#endif//!GENERATE_ASM_H
