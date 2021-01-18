#include "unistd.h"
#include "libft.h"

int		print_line(char const *line)
{
	if (line == NULL)
		return (-1);
	write(1, line, ft_strlen(line));
	return (0);
}
