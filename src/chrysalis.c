/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <unistd.h>

# include "chrysalis.h"

# include "utils/logging.h"

# include "files/files.h"
# include "files/paths.h"

# include "tokenizer/tokenizer.h"
# include "parser/parser.h"
# include "generator/generator.h"


static void print_help()
{
    printf("Usage: Chrysalis [options] file...\n");
    printf("Options:\n");
    printf("    -o <file>       Place the output into <file>\n");
}

static int read_output_path_arg(int index, char** av, program_options_t* opt)
{
    if (av[index] == NULL)
        return -1;

    opt->output_filepath = get_absolute_path(av[index]);
    if (!opt->output_filepath)
        return -1;
    return 0;
}

static int read_arg(int index, char** av, program_options_t* opt)
{
    const char *args[] = {"-o", NULL};
    int (*args_func_ptr [])(int, char**, program_options_t*) = {&read_output_path_arg, NULL};

    for (int i = 0; args[i]; i++) {
        if (strcmp(av[index], args[i]) == 0)
            return args_func_ptr[i](index + 1, av, opt);
    }
    printf("ERROR: Unknow argument '%s'\n", av[index]);
    print_help();
    return -1;
}

static program_options_t parse_args(int ac, char** av)
{
    int i = 1;
    program_options_t options;
    memset(&options, 0, sizeof(program_options_t));

    if (ac < 2) {
        print_help();
        exit(1);
    }
    if (ac > 3) {
        for (; i < ac - 1; i += 2)
            if (read_arg(i, av, &options) == -1)
                exit(1);
    }
    options.input_filepath = get_absolute_path(av[i]);
    if (!options.input_filepath)
        exit(1);
    return options;
}


int main(int ac, char** av)
{
    program_options_t options = parse_args(ac, av);
    if (options.output_filepath) {
        printf("output path: %s\n", options.output_filepath);
    }
    if (options.input_filepath) {
        printf("input path: %s\n", options.input_filepath);
    }
}
