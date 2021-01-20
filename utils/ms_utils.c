#include "unistd.h"
#include "libft.h"

int		print_line(char const *line, int fd)
{
	if (line == NULL)
		return (-1);
	write(fd, line, ft_strlen(line));
	return (0);
}

int		ms_strcmp(const char *s1, const char *s2)
{
	unsigned int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			if ((((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]) > 0)
				return (1);
			else
				return (-1);
		}
		++i;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}