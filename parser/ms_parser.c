#include "ms_processor.h"
#include "ms_parser.h"
#include "libft.h"
#include "ms_utils.h"

static char *find_env_in_word(const char *cmd, char *env_start)
{
	char	*env_end;
	char	*env;
	int 	i;

	env_end = ft_strchr(env_start, '$');
	if (!env_end)
		i = ft_strlen(env_start);
	else
		i = env_end - env_start;
	env = ft_substr(cmd, (env_start - cmd), i);
	return (env);
}

/*
**  A function that swaps command with env variable if variable exists
*/

static int	swap_env_if_exists(char **cmd, char **result, char *content)
{
	char	*index;
	char	*tmp;

	*result = ft_substr(*cmd, 0, (ft_strchr(*cmd, '$') - *cmd));
	tmp = *result;
	*result = ft_strjoin(*result, content);
	free(tmp);
	free(content);
	index = ft_strchr(ft_strchr(*cmd, '$') + 1, '$');
	if (!index)
		return (0);
	tmp = *result;
	*result = ft_strjoin(*result, index);
	free(tmp);
	free(*cmd);
	*cmd = *result;
	return (1);
}

/*
**  A function that swaps command with env variable
*/

void	swap_env(char **cmd, t_list *env_list)
{
	char	*env_start;
	char	*content;
	char	*tmp;
	char	*result;

	while (ft_strchr(*cmd, '$'))
	{
		env_start = ft_strchr(*cmd, '$');
		tmp = find_env_in_word(*cmd, env_start + 1);
		if (!ms_strcmp(tmp, "?"))
			content = ft_itoa(g_exit_status);
		else
			content = get_var_content(env_list, tmp);
		free(tmp);
		if (!content)
			content = ft_strdup("");
		if (!swap_env_if_exists(cmd, &result, content))
		{
			free(*cmd);
			*cmd = result;
			break;
		}
	}
}

/*
**  A function that gets word from command line
*/

static int	get_word(const char *cmd_line, char **cmd, int i)
{
	int start;
	int quotes_flag;

	start = i;
	quotes_flag = 0;
	if (cmd_line[i] == '\'')
		quotes_flag = 1;
	else if (cmd_line[i] == '"')
		quotes_flag = 2;
	while (1)
	{
		++i;
		if ((!quotes_flag && ft_strchr(" ;|\0", cmd_line[i - 1])) || cmd_line[i - 1] == '\0')
			break ;
		if ((quotes_flag == 1 && cmd_line[i] == '\'') || (quotes_flag == 2 && cmd_line[i] == '"'))
			quotes_flag = 0;
		else
		{
			if (!quotes_flag && (cmd_line[i] == '\''))
				quotes_flag = 1;
			else if (!quotes_flag && (cmd_line[i] == '"'))
				quotes_flag = 2;
		}
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

static int	get_args(const char *cmd_line, char ***args, int i, t_list *env_list)
{
	int		arg_index;

	arg_index = 0;
	*args = malloc(sizeof(char *) * (count_args(cmd_line, i) + 1));
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		i = skip_spaces(cmd_line, i);
		i = get_word(cmd_line, &(*args)[arg_index], i);
		i = skip_spaces(cmd_line, i);
		++arg_index;
	}
	(*args)[arg_index] = 0;
	return (i);
}

/*
**  A function that creates command structure for one command
*/

static void	parse_cmd(const char *cmd_line, int *i, t_cmd *cmd, t_list *env_list)
{
	*i = skip_spaces(cmd_line, *i);
	*i = get_word(cmd_line, &cmd->cmd, *i);
	*i = skip_spaces(cmd_line, *i);
	if (!(cmd_line[*i] == '\0' || cmd_line[*i] == ';' || cmd_line[*i] == '|'))
		*i = get_args(cmd_line, &cmd->args, *i, env_list);
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
	int		break_flag;

	i = 0;
	cmds_num = 0;
	break_flag = 0;
	while (cmd_line[i])
	{
		cmd = NULL;
		i = skip_spaces(cmd_line, i);
		if (!ft_strchr(" |;", cmd_line[i]))
		{
			i = get_word(cmd_line, &cmd, i);
			if (!break_flag)
				++cmds_num;
			break_flag = 1;
		}
		i = skip_spaces(cmd_line, i);
		if (cmd_line[i] == ';' || cmd_line[i] == '|')
		{
			if (!cmd)
			{
				count_cmds_err_check(cmd_line, i);
				return (0);
			}
			++i;
			break_flag = 0;
		}
		if (cmd != NULL)
		{
			free(cmd);
			cmd = NULL;
		}
	}
	return (cmds_num);
}

/*
**  A function that checks command line for emptiness
*/

static int	check_for_empty_line(const char *cmd_line)
{
	int 	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

t_cmd	**parser(const char *cmd_line, t_list *env_list)
{
	t_cmd	**cmd_arr;
	int 	i;
	int 	j;
	int 	k;

	i = 0;
	j = check_for_empty_line(cmd_line);
	if (j)
		return (0);
	j = count_cmds(cmd_line);
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
		parse_cmd(cmd_line, &i, cmd_arr[j], env_list);
		++j;
	}
	return (cmd_arr);
}