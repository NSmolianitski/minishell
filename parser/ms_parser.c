#include "ms_parser.h"
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that gets word from command line
*/

static int	get_word(const char *cmd_line, char **cmd, int i)
{
	int start;

	start = i;
	while (1)
	{
		++i;
		if (ft_strchr(" ;|\0", cmd_line[i - 1]))
			break ;
	}
	*cmd = malloc(sizeof(char) * (i - start));
	ms_strlcpy(*cmd, cmd_line, i, start);
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
	int		arg_index;

	arg_index = 0;
	*args = malloc(sizeof(char *) * (count_args(cmd_line, i) + 1));
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		i = skip_spaces(cmd_line, i);
		i = get_word(cmd_line, &(*args)[arg_index], i);
		++arg_index;
	}
	(*args)[arg_index] = 0;
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

static void	count_cmds_err_check(const char *cmd_line, int i)
{
	if (cmd_line[i] == ';')
		print_error(SES, "", 2);
	else if (cmd_line[i] == '|')
		print_error(SEP, "", 2);
	else
		print_line("look into count_cmds_err_check for answer", 1);
}

static int	count_cmds(const char *cmd_line)
{
	int		i;
	int		cmds_num;
	char	*cmd;

	i = 0;
	cmd = NULL;
	cmds_num = 0;
	while (cmd_line[i])
	{
		cmd = 0;
		i = skip_spaces(cmd_line, i);
		if (!ft_strchr(" |;", cmd_line[i]))
			i = get_word(cmd_line, &cmd, i);
		i = skip_spaces(cmd_line, i);
		if (cmd_line[i] == ';' || cmd_line[i] == '|')
		{
			if (!cmd)
			{
				count_cmds_err_check(cmd_line, i);
				return (0);
			}
			i = skip_spaces(cmd_line, i);
			if (cmd_line[i] != '\0')
			{
				++cmds_num;
				++i;
			}
		}
		if (cmd != NULL)
		{
			free(cmd);
			cmd = NULL;
		}
	}
	return (cmds_num);
}

t_cmd	**parser(const char *cmd_line)
{
	t_cmd	**cmd_arr;
	int 	i;
	int 	j;
	int 	k;

	i = 0;
	j = count_cmds(cmd_line);
	if (!j)
		return (0);
	cmd_arr = malloc(sizeof(t_cmd *) * (j + 1));
	k = 0;
	while (k < j)
	{
		cmd_arr[k] = malloc(sizeof(t_cmd));
		++k;
	}
	cmd_arr[j] = NULL;
	j = 0;
	while (cmd_line[i] != '\0')
	{
		parse_cmd(cmd_line, &i, cmd_arr[j]);
		++j;
	}
	return (cmd_arr);
}