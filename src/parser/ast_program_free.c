/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/


# include "parser/ast_types.h"

# include <stdlib.h>

void ast_program_free(ast_program_t* prg)
{
    if (prg->functions)
        prg->functions->free(prg->functions);
    free(prg);
}
