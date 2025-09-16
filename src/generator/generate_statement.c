/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "generator/statement.h"
# include "generator/generator.h"
# include "generator/function.h"

# include "utils/string_array.h"
# include "utils/logging.h"

bool generate_statements(gen_func_data_t* data, ast_statement_t* statement_list)
{
    ast_statement_t* ptr = statement_list;
    while (ptr) {
        switch (ptr->type) {
            case RETURN:
                if (!generate_return_statement(data, ptr))
                    return false;
                break;
            case ASSIGN_DECL:
                if (!generate_assignment_statement(data, ptr))
                    return false;
                break;
            case ASSIGN:
                if (!generate_assignment_statement(data, ptr))
                    return false;
                break;
            case DECL:
                break;
            default:
                string_array_free(data->gen_data->file);
                PERR("Unknow statement type. %d\n", ptr->type);
                return false;
        }
        ptr = ptr->next;
    }

    return true;
}
