#include "ms_parser.h"
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that gets command from command line
*/

static int	get_cmd(const char *cmd_line, char **cmd, int i)
{
	int j;

	j = i;
	while (cmd_line[i])
	{
		++i;
		if (ft_strchr(" ;|", cmd_line[i - 1]))
			break ;
	}
	if (cmd_line[i] == '\0')
		++i;
	*cmd = malloc(sizeof(char) * (i - j));
	ms_strlcpy(*cmd, cmd_line, i, j);
	return (i - 1);
}

/*
**  A function that counts command from command line
*/

static int	count_args(const char *cmd_line, int i)
{
	int 	args_num;

	args_num = 1;
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		if (cmd_line[i] == ' ')
		{
			i = skip_spaces(cmd_line, i);
			++args_num;
		}
		++i;
	}
	return (args_num);
}

static int	get_args(const char *cmd_line, char ***args, int i)
{
	int	arg_index;

	arg_index = 0;
	*args = malloc(sizeof(char *) * count_args(cmd_line, i));
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		i = skip_spaces(cmd_line, i);
		i = get_cmd(cmd_line, &(*args)[arg_index], i);
		print_line((*args)[arg_index], 1);
		++arg_index;
	}
	return (i);
}

static t_cmd	parse_cmd(char *cmd_line)
{
	int		i;
	t_cmd	cmd;

	i = 0;
	i = get_cmd(cmd_line, &cmd.cmd, i);
	i = skip_spaces(cmd_line, i);
	if (!(cmd_line[i] == '\0' || cmd_line[i] == ';' || cmd_line[i] == '|'))
		i = get_args(cmd_line, &cmd.args, i);
	return (cmd);
}

char	*parser(char *cmd_line)
{
	t_cmd	cmd;

	cmd = parse_cmd(cmd_line);
	print_line(cmd.cmd, 1);
}