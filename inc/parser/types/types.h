/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef TYPES_H
#define TYPES_H

extern const char* BUILTIN_TYPE_IDENTIFIERS[];
extern const unsigned int BUILTIN_TYPE_IDENTIFIERS_SIZE;

typedef enum {
    TYPE_ID_INT,
}builtin_type_id_t;

typedef struct type_s {
    int size;
    int type_id;
}type_t;

extern const type_t BUILTIN_TYPES[];
extern const unsigned int BUILTIN_TYPES_SIZE;

#endif//!TYPES_H
