#include <unistd.h>
<<<<<<< HEAD
#include <stdlib.h>
#include "libft.h"
=======
#include "ms_commands.h"
>>>>>>> Some files rename (pwd to ms_pwd, etc.)

/*
**  A function that prints shell tag
*/

static void	print_shell_tag(void)
{
	write(1, "\033[32m", ft_strlen("\033[32m")); //output color
	write(1, "minishell$ ", 11);
	write(1, "\033[0m", ft_strlen("\033[0m"));
}

/*
**  A function that gets the command line from input
*/

static char	*get_cmd_line(void)
{
	char	buff[1000];
	char	*cmd_line;
	char	*tmp;
	int		read_bytes;

	cmd_line = ft_strdup("");
	while ((read_bytes = read(0, buff, 999)))
	{
		if (buff[read_bytes - 1] == '\n')
			buff[read_bytes - 1] = '\0';
		tmp = cmd_line;
		cmd_line = ft_strjoin(cmd_line, buff);
		free(tmp);
		if (buff[read_bytes - 1] == '\0')
			break ;
	}
	return (cmd_line);
}

int			main(void)
{
	char	*cmd_line;

	while (1)
	{
		print_shell_tag();
		cmd_line = get_cmd_line();
//		write(0, cmd_line, ft_strlen(cmd_line));  //print command line
//		write(0, "\n", 1);
		free(cmd_line);
	}
	return (0);
}
