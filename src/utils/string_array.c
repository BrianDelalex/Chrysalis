/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <string.h>

# include "utils/string_array.h"
# include "utils/logging.h"

int string_array_size(char** array)
{
    int count = 0;

    for (; array[count]; count++);
    return count;
}

void string_array_free(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

char** string_array_append(char** array, const char* line)
{
    char *new_line;
    int array_size = string_array_size(array);

    array = realloc(array, sizeof(char*) * (array_size + 2));
    if (!array) {
        PERR("Out of memory!\n");
        return NULL;
    }
    new_line = malloc(sizeof(char) * (strlen(line) + 1));
    if (!new_line) {
        PERR("Out of memory!\n");
        free(array);
        return NULL;
    }
    memcpy(new_line, line, strlen(line) + 1);
    array[array_size] = new_line;
    array[array_size + 1] = NULL;

    return array;
}
