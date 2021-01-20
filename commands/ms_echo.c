#include <unistd.h>
#include "ms_utils.h"

int		ms_echo(char *str, int n_option)
{
	print_line(str);
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}