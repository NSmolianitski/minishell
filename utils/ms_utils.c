#include <stddef.h>
#include "unistd.h"
#include "libft.h"

/*
**  A function that checks symbol escape
*/

int		is_symb_esc(const char *str, int i)
{
	if (i > 1)
	{
		if (str[i - 1] == '\\' && str[i - 2] == '\\')
			return (0);
		else if (str[i - 1] == '\\')
			return (1);
	}
	else if (i > 0)
		if (str[i - 1] == '\\')
			return (1);
	return (0);
}

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

char	*safe_strjoin(char **str1, const char *str2)
{
	char	*tmp;
	tmp = *str1;
	*str1 = ft_strjoin(*str1, str2);
	free(tmp);
	return (*str1);
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

/*
**  A function like strchr, but ignores content in quotes, escaped $, but handles escaped quotes
*/

char	*ft_strchr_quotes(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !is_symb_esc(s, i))
		{
			++i;
			while (s[i] != '\'' && s[i] != '\0')
				++i;
		}
		else if (s[i] == '"' && !is_symb_esc(s, i))
		{
			++i;
			while (s[i] != '"' && s[i] != '\0')
				++i;
		}
		if (s[i] == c)
			return ((char*)s + i);
		++i;
	}
	if (c == '\0')
		return ((char*)s + i);
	return (0);
}

/*
**  A function that swaps string part by coordinates
*/

int		ms_strswap(char **str, const char *inject, int start, int len)
{
	char	*result;
	char	*tmp;

	result = ft_substr(*str, 0, start);
	result = safe_strjoin(&result, inject);
	tmp = ft_substr(*str, start + 1 + len, ft_strlen(&(*str)[start + len]));
	result = safe_strjoin(&result, tmp);
	free(tmp);
	free(*str);
	*str = result;
	return (1);
}

/*
**  strchr with several symbols
*/

char	*ms_strmultichr(const char *s, const char *symbols)
{
	int		i;
	int 	j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (symbols[j])
		{
			if (s[i] == symbols[j])
				return ((char *) s + i);
			++j;
		}
		++i;
	}
	return (0);
}

/*
**  strchr that skips escaped symbol
*/

char	*ms_bs_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			if (((i > 1 && !(s[i - 2] == '\\') && (s[i - 1] == '\\')) || !(i > 0 && (s[i - 1] == '\\'))))
				return ((char *)s + i);
		++i;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}