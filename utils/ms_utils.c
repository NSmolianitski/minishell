#include "unistd.h"

int		ms_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		print_line(char const *line)
{
	if (line == NULL)
		return (-1);
	write(1, line, ms_strlen(line));
	return (0);
}
