/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/types/types.h"

const char* BUILTIN_TYPE_IDENTIFIERS[] = {
    "int",
};

const unsigned int BUILTIN_TYPE_IDENTIFIERS_SIZE = sizeof(BUILTIN_TYPE_IDENTIFIERS) / sizeof(char*);

const type_t TYPE_INT = {
    .size = sizeof(int),
    .type_id = TYPE_ID_INT
};

const type_t BUILTIN_TYPES[] = {
    TYPE_INT
};
const unsigned int BUILTIN_TYPES_SIZE = sizeof(BUILTIN_TYPES) / sizeof(type_t);
