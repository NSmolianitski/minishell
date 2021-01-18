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
	print_line(str);
	free(str);
	str = NULL;
	return (0);
}
