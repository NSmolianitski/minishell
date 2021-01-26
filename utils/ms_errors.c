#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

static void	write_ms_err_begin_with_cmd(char *str)
{
	write(1, "minishell: ", 11);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2);
}

static void	write_ms_err_begin_export(char *str)
{
	write(1, "minishell: export: '", 20);
	print_line(str, 1);
	write(1, "': ", 3);
}

static void	write_ms_err_begin(void)
{
	write(1, "minishell: ", 11);
}

void	print_error(char *error, char *str, int err_type)
{
	if (err_type == 1)
		write_ms_err_begin_with_cmd(str);
	else if (err_type == 2)
		write_ms_err_begin();
	else if (err_type == 3)
		write_ms_err_begin_export(str);
	(!ms_strcmp(error, NSFD)) ? print_line(NSFD, 1) : 0;
	(!ms_strcmp(error, CNF)) ? print_line(CNF, 1) : 0;
	(!ms_strcmp(error, SES)) ? print_line(SES, 1) : 0;
	(!ms_strcmp(error, SEP)) ? print_line(SEP, 1) : 0;
	(!ms_strcmp(error, NVI)) ? print_line(NVI, 1) : 0;
	(!ms_strcmp(error, SNIP)) ? print_line(SNIP, 1) : 0;
	write(1, "\n", 1);
}
