/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <string.h>
# include <stdlib.h>
# include <errno.h>

# include "generator/stack/stack.h"

# include "parser/stack.h"

# include "utils/logging.h"

static const char* asm_size_directive_from_c_size(uint64_t size)
{
    switch (size) {
    case 1:
        return "BYTE PTR";
    case 2:
        return "WORD PTR";
    case 4:
        return "DWORD PTR";
    case 8:
        return "QWORD PTR";
    default:
        PERR("Invalid size %ld.\n", size);
        return NULL;
    }
}

char *asm_string_access_stack(ast_stack_t* stack, const char* identifier)
{
    char* asm_string;
    ast_stack_entry_t* entry = stack->entries;

    while (entry) {
        if (strcmp(entry->identifier, identifier) == 0) {
            const char* asm_size = asm_size_directive_from_c_size(entry->size);
            int string_size = snprintf(NULL, 0, ACCESS_STACK_FMT, asm_size, entry->offset);
            asm_string = malloc(sizeof(char) * (string_size + 1));
            if (!asm_string) {
                PERR(OUT_OF_MEM);
                return NULL;
            }
            if (snprintf(asm_string, string_size + 1, ACCESS_STACK_FMT, asm_size, entry->offset) < 0) {
                PERR("%s", strerror(errno));
                return NULL;
            }
            return asm_string;
        }
        entry = entry->next;
    }

    printf("Unknow identifier %s\n", identifier);

    return NULL;
}
