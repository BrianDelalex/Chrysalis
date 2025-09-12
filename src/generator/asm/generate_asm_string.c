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
# include <errno.h>

# include "generator/generator.h"
# include "generator/asm/generate_asm.h"

# include "utils/logging.h"
# include "utils/string_manipulation.h"


char* generate_asm_mov(const char* to, const char* from)
{
    char* mov;

    GENERATE_STRING(mov, ASM_MOV, to, from);

    return mov;
}

char* generate_integer_literal(int value)
{
    char* op;

    GENERATE_STRING(op, "%d", value);

    return op;
}
