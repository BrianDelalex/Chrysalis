/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef FILES_H
#define FILES_H

char* read_file(const char* filepath);
int write_file(const char* filepath, char** lines);

#endif//!FILES_H
