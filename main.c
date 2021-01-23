#include <unistd.h>
#include <stdlib.h>
#include "ms_utils.h"
#include "libft.h"
#include "ms_parser.h"
#include "ms_processor.h"

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

static void parser_free(char **cmd_line, t_cmd **cmd_arr)
{
	int 	i;

	free(*cmd_line);
	i = 0;
	while (cmd_arr[i])
	{
		free(cmd_arr[i]->cmd);
		cmd_arr[i]->cmd = NULL;
		if (cmd_arr[i]->args != NULL)
			free(cmd_arr[i]->args);
		cmd_arr[i]->args = NULL;
		free(cmd_arr[i]);
		cmd_arr[i] = NULL;
		++i;
	}
	free(cmd_arr);
}

int			main(void)
{
	char	*cmd_line;
	t_cmd	**cmd_arr;

	while (1)
	{
		print_shell_tag();				//print shell tag
		cmd_line = get_cmd_line();		//read command line and put it to a variable
		cmd_arr = parser(cmd_line);		//send command line to parser (and get command)
		for (int i = 0; cmd_arr[i]->cmd; ++i)
		{
			print_line(cmd_arr[i]->cmd, 1);
			print_line("\n", 1);
		}
//		if (ms_strcmp(cmd, ""))
//			processor(cmd);
//		parser_free(&cmd_line, cmd_arr);
	}
	return (0);
}
