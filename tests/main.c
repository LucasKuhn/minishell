#include "minishell.h"

int    main()
{
    char *line;
	const char prompt[] = " > ";

    line = readline(prompt);
    add_history(line);
    add_history(line);
    add_history(line);
	rl_clear_history();
	free(line);
    return (0);
}
