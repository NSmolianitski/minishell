#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

void	write_ms_err_begin(char *str)
{
	write(1, "minishell: ", 11);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2);
}

void	print_error(char *error, char *str, int err_type)
{
	if (err_type == 1)
		write_ms_err_begin(str);
	(!ms_strcmp(error, NSFD)) ? print_line(NSFD, 1) : 0;
	(!ms_strcmp(error, CNF)) ? print_line(CNF, 1) : 0;
	write(1, "\n", 1);
}
