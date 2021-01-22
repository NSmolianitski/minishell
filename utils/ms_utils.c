#include <stddef.h>
#include "unistd.h"
#include "libft.h"

/*
**  strlcpy that copies from i
*/

size_t	ms_strlcpy(char *dst, const char *src, size_t dstsize, size_t start)
{
	size_t	i;
	size_t	j;

	if (src == 0)
		return (0);
	if (src[0] == '\0')
	{
		dst[0] = '\0';
		return (0);
	}
	i = 0;
	j = 0;
	while (src[i] != '\0')
		++i;
	++i;
	while (start < dstsize && start < i)
	{
		dst[j] = src[start];
		++start;
		++j;
	}
	dst[--j] = '\0';
	return (i - 1);
}

/*
**  A function that skips spaces and return index of first non-space character
*/

int		skip_spaces(char const *line, int i)
{
	while (line[i] == ' ')
		++i;

	return (i);
}

/*
**  A function that prints string to fd
*/

int		print_line(char const *line, int fd)
{
	if (line == NULL)
		return (-1);
	write(fd, line, ft_strlen(line));
	return (0);
}

/*
**  A function that compares two strings and returns 0 if they are equal
*/

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