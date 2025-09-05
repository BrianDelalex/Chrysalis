/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "generator/generator.h"

# include "files/files.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>

# define CHECK_LINES_RETURN_NULL()  \
    if (!lines)                     \
        return NULL;                \

# define CHECK_LINES_RETURN(ret_val)    \
    if (!lines)                         \
        return ret_val;                 \

bool g_main_found = false;

int count_lines(char** lines)
{
    int count = 0;

    for (; lines[count]; count++);
    return count;
}

void free_lines(char **lines)
{
    for (int i = 0; lines[i]; i++) {
        free(lines[i]);
    }
    free(lines);
}

char** append_line(char** lines, const char* line)
{
    char *new_line;
    int lines_count = count_lines(lines);

    lines = realloc(lines, sizeof(char*) * (lines_count + 2));
    if (!lines) {
        PERR("Out of memory!\n");
        return NULL;
    }
    new_line = malloc(sizeof(char) * (strlen(line) + 1));
    if (!new_line) {
        PERR("Out of memory!\n");
        free(lines);
        return NULL;
    }
    memcpy(new_line, line, strlen(line) + 1);
    lines[lines_count] = new_line;
    lines[lines_count + 1] = NULL;

    return lines;
}

char** generate_statement(char** lines, ast_statement_t* statement)
{
    ast_return_statement_t *rtn_statement = (ast_return_statement_t*) statement->statement;
    char* line;

    int line_size = snprintf(NULL, 0, RETURN_INT_STATEMENT, rtn_statement->value);
    line = malloc(sizeof(char) * (line_size + 1));
    if (!line) {
        PERR(OUT_OF_MEM);
        return NULL;
    }

    if (snprintf(line, line_size + 1, RETURN_INT_STATEMENT, rtn_statement->value) < 0) {
        PERR("%s", strerror(errno));
        return NULL;
    }
    lines = append_line(lines, line);
    CHECK_LINES_RETURN_NULL();
    return lines;
}

char** generate_start_function(char** lines)
{
    printf("generate_start_function\n");
    const char global_start[] = "global _start\n\n";
    const char start_lbl[] = "_start:\n";
    const char call_main[] = "    call main\n";
    const char mov_rdi_rax[]= "    mov rdi, rax\n";
    const char mov_rax_exit[] = "    mov rax, 60\n";
    const char syscall[] = "    syscall\n";

    lines = append_line(lines, global_start);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, start_lbl);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, call_main);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, mov_rdi_rax);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, mov_rax_exit);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, syscall);
    CHECK_LINES_RETURN_NULL();

    return lines;
}

char** generate_function(char** lines, ast_function_t* func)
{
    int global_lbl_size = GLOBAL_LABEL_STR_SIZE(func->name);
    int lbl_size = LABEL_STR_SIZE(func->name);
    char *global_lbl;
    char *lbl;

    if (strcmp("main", func->name) == 0) {
        g_main_found = true;
    }

    global_lbl = malloc(sizeof(char) * global_lbl_size);
    if (!global_lbl) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    if (snprintf(global_lbl, global_lbl_size, GLOBAL_LABEL_STR, func->name) < 0) {
        PERR("%s\n", strerror((errno)));
        free(global_lbl);
        return NULL;
    }

    lines = append_line(lines, global_lbl);
    CHECK_LINES_RETURN_NULL();
    free(global_lbl);

    lbl = malloc(sizeof(char) * lbl_size);
    if (!lbl) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    if (snprintf(lbl, lbl_size, LABEL_STR, func->name) < 0) {
        PERR("%s\n", strerror(errno));
        free(lbl);
        return NULL;
    }

    lines = append_line(lines, lbl);
    CHECK_LINES_RETURN_NULL();
    free(lbl);

    return generate_statement(lines, func->statements);
}

int generator(ast_program_t* program, const char* target)
{
    char** lines = malloc(sizeof(char*));
    lines[0] = NULL;
    g_main_found = false;

    lines = generate_function(lines, program->functions);
    CHECK_LINES_RETURN(-1);

    if (g_main_found) {
        lines = generate_start_function(lines);
        CHECK_LINES_RETURN(-1);
    }

    write_file(target, lines);
    free_lines(lines);
    return 0;
}
