/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include "files/paths.h"

# include "utils/logging.h"

char *get_absolute_path(const char* filepath)
{
    char *absolute;

    if (filepath[0] == '/') {
        int path_length = strlen(filepath);
        absolute = malloc(sizeof(char) * (path_length + 1));
        if (!absolute) {
            PERR(OUT_OF_MEM);
            return NULL;
        }
        memcpy(absolute, filepath, path_length + 1);
    } else {
        char *pwd = getcwd(NULL, 0);
        if (!pwd) {
            return NULL;
        }
        int pwd_len = strlen(pwd);
        int filepath_len = strlen(filepath);
        absolute = malloc(sizeof(char) * (pwd_len + filepath_len + 2));
        if (!absolute) {
            PERR(OUT_OF_MEM);
            free(pwd);
            return NULL;
        }
        memcpy(absolute, pwd, pwd_len);
        absolute[pwd_len] = '/';
        memcpy(&(absolute[pwd_len + 1]), filepath, filepath_len + 1);
        free(pwd);
    }
    return absolute;
}
