#include "ms_utils.h"

#define NSFD "No such file or directory"

void	print_error(char *error)
{
	(!ms_strcmp(error, NSFD)) ? print_line(NSFD, 2) : 0;
}
