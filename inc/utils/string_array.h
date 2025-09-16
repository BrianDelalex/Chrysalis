/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

int string_array_size(char** array);
void string_array_free(char **array);
char** string_array_append(char** array, const char* line);

#endif//!STRING_ARRAY_H
