#include <unistd.h>
#include "ms_utils.h"

static void is_n_option(int n_option)
{
	if (!n_option)
		write(1, "\n", 1);
}

int		ms_echo(char **args)
{
	int 	i;
	int 	n_option;

	i = 0;
	n_option = 0;
	if (!args)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ms_strcmp(args[0], "-n"))
	{
		n_option = 1;
		++i;
	}
	while (args[i])
	{
		print_line(args[i], 1);
		++i;
		if (!args[i])
			break ;
		if (ms_strcmp(args[i - 1], ""))
			write(1, " ", 1);
	}
	is_n_option(n_option);
	return (0);
}