/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

char* remove_extra_spaces(char* str)
{
    int str_len = strlen(str);
    char *new_str = NULL;
    int count = 0;
    bool newline = true;

    for (int i = 1; i < str_len; i++) {
        if (str[i] == ' ' && str[i - 1] == ' ')
            count++;
    }
    new_str = malloc(sizeof(char) * (str_len - count + 1));
    if (!new_str) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < str_len; i++) {
        if (newline && str[i] == ' ')
            continue;
        if (str[i] == ' ' && str[i - 1] == ' ')
            continue;
        new_str[j] = str[i];
        newline = str[i] == '\n';
        j++;
    }
    new_str[j] = 0;
    return new_str;
}

char* remove_newline(char* str)
{
    int str_len = strlen(str);
    char *new_str = NULL;
    int count = 0;

    for (int i = 0; i < str_len; i++) {
        if (str[i] == '\n')
            count++;
    }

    new_str = malloc(sizeof(char) * (str_len - count + 1));
    if (!new_str)
        return NULL;

    int j = 0;
    for (int i = 0; i < str_len; i++) {
        if (str[i] == '\n')
            continue;
        new_str[j] = str[i];
        j++;
    }
    new_str[j] = 0;
    return new_str;
}
