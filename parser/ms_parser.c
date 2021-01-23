#include "ms_parser.h"
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that gets word from command line
*/

static int	get_word(const char *cmd_line, char **cmd, int i)
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
**  A function that counts arguments from command line
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

/*
**  A function that creates an array with arguments
*/

static int	get_args(const char *cmd_line, char ***args, int i)
{
	int	arg_index;

	arg_index = 0;
	*args = malloc(sizeof(char *) * count_args(cmd_line, i));
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		i = skip_spaces(cmd_line, i);
		i = get_word(cmd_line, &(*args)[arg_index], i);
		++arg_index;
	}
	return (i);
}

/*
**  A function that creates command structure for one command
*/

static void	parse_cmd(const char *cmd_line, int *i, t_cmd *cmd)
{
	*i = skip_spaces(cmd_line, *i);
	*i = get_word(cmd_line, &cmd->cmd, *i);
	*i = skip_spaces(cmd_line, *i);
	if (!(cmd_line[*i] == '\0' || cmd_line[*i] == ';' || cmd_line[*i] == '|'))
		*i = get_args(cmd_line, &cmd->args, *i);
	else
		cmd->args = NULL;
	cmd->end = cmd_line[*i];
	if (cmd_line[*i] != '\0')
		++(*i);
	*i = skip_spaces(cmd_line, *i);
}

/*
**  A function that reallocates memory for commands array without loosing data
*/

static void realloc_cmd_arr(t_cmd ***cmd_arr, int j)
{
	int 	i;
	t_cmd	**tmp;

	i = 0;
	tmp = *cmd_arr;
	*cmd_arr = malloc(sizeof(t_cmd *) * (j + 1));
	while (i < j)
	{
		(*cmd_arr)[i] = tmp[i];
		++i;
	}
	(*cmd_arr)[i + 1] = 0;
	free(tmp);
	tmp = NULL;
}

static int	count_cmds(const char *cmd_line)
{
	int		i;
	int		cmds_num;

	i = 0;
	cmds_num = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == ';' || cmd_line[i] == '|')
			++cmds_num;
		++i;
	}
	return (cmds_num);
}

t_cmd	**parser(const char *cmd_line)
{
	t_cmd	**cmd_arr;
	int 	i;
	int 	j;

	i = 0;
	j = count_cmds(cmd_line);
	cmd_arr = malloc(sizeof(t_cmd *) * (j + 2));
	for (int k = 0; k <= j + 1; ++k)
		cmd_arr[k] = malloc(sizeof(t_cmd));
	cmd_arr[j + 1]->cmd = NULL;
	j = 0;
	while (cmd_line[i] != '\0')
	{
		parse_cmd(cmd_line, &i, cmd_arr[j]);
		++j;
	}
	return (cmd_arr);
}