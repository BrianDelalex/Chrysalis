/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef LOGGING_H
#define LOGGING_H

# include <stdio.h>

# define PERR(fmt, args...) dprintf(2, "%s(l.%d):" fmt, __FUNCTION__, __LINE__, ## args)

# define OUT_OF_MEM "Out of memory!\n"

#endif//!LOGGING_H
