#include <unistd.h>
#include "ms_commands.h"

static void	print_shell_tag(void)
{
	write(1, "minishell$ ", 11);
}

int			main(void)
{
	char	buff[200];			//Don't forget to create a string from read with malloc (or create custom realloc)
	int		read_symbols;

	while (1)
	{
		print_shell_tag();
		read_symbols = read(0, buff, 200);
		buff[read_symbols] = '\0';
		printf("%s", buff);
	}
	return (0);
}
