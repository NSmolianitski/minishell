#include <unistd.h>
#include <stdlib.h>
#include "ms_utils.h"

int		print_pwd(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
		return (-1);
	print_line(str, 1);
	free(str);
	str = NULL;
	write(1, "\n", 1);
	return (0);
}