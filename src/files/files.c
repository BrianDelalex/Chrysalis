/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "files/files.h"

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

char* read_file(const char* filepath)
{
    char* file;

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        dprintf(2, "%s(l%d): %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return NULL;
    }

    size_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == (size_t) -1) {
        dprintf(2, "%s(l%d): %s\n", __FUNCTION__, __LINE__, strerror(errno));
        close(fd);
        return NULL;
    }

    size_t rc = lseek(fd, 0, SEEK_SET);
    if (rc == (size_t) -1) {
        dprintf(2, "%s(l%d): %s\n", __FUNCTION__, __LINE__, strerror(errno));
        close(fd);
        return NULL;
    }

    file = malloc(sizeof(char) * (file_size + 1));
    if (!file) {
        dprintf(2, "%s(l%d): %s\n", __FUNCTION__, __LINE__, strerror(errno));
        close(fd);
        return NULL;
    }

    int r_bytes = read(fd, file, file_size);
    if (r_bytes == -1) {
        dprintf(2, "%s(l%d): %s\n", __FUNCTION__, __LINE__, strerror(errno));
        close(fd);
        free(file);
        return NULL;
    }
    file[file_size] = 0;

    close(fd);
    return file;
}
