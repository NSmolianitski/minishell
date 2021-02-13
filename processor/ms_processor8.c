#include "ms_processor.h"

void		check_bslash(char *tmp, int *i, char **str, int *str_diff)
{
	if (tmp[*i + 1] == '\\')
	{
		ms_strswap(str, "\\", (*i - *str_diff), 1);
		++(*i);
	}
	else
		ms_strswap(str, "", (*i - *str_diff), 0);
	++(*str_diff);
	++(*i);
}

int			check_bslash2(char **str, int i)
{
	if ((*str)[i + 1] == '\\')
	{
		ms_strswap(str, "\\", i, 1);
		return (i);
	}
	else
		ms_strswap(str, "", i, 0);
	return (i);
}