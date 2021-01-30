#include <unistd.h>
#include <fcntl.h>
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_commands.h"
#include "ms_processor.h"

/*
**  A function that creates an array of strings from list
*/

static void	list_to_arr(t_list *env_list, char ***envp)
{
	int		i;
	char	*tmp;

	i = ft_lstsize(env_list);
	*envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env_list)
	{
		(*envp)[i] = ft_strjoin(env_list->name, "=");
		tmp = (*envp)[i];
		(*envp)[i] = ft_strjoin((*envp)[i], env_list->content);
		free(tmp);
		env_list = env_list->next;
		++i;
	}
	(*envp)[i] = 0;
}

/*
**  A function that makes a new arr with command name in args[0]
*/

static void prepare_args(t_cmd *cmd, char ***args)
{
	int	i;

	if (!cmd->args)
	{
		*args = malloc(sizeof(char *) * 2);
		(*args)[0] = ft_strdup(cmd->cmd);
		(*args)[1] = 0;
		return ;
	}
	i = 0;
	while (cmd->args[i])
		++i;
	*args = malloc(sizeof(char *) * (i + 2));
	(*args)[0] = ft_strdup(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		(*args)[i + 1] = ft_strdup(cmd->args[i]);
		++i;
	}
	(*args)[i + 1] = 0;
}

/*
**  A function that clears an array of strings
*/

static void free_strs_arr(char ***args)
{
	int i;

	i = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		++i;
	}
	free(*args);
}

/*
**  A function that tries to execute external command
*/

static int	try_external_cmd(t_cmd *cmd, t_list **env_list)
{
	int		status;
	char	**envp;
	char	**args;

	list_to_arr(*env_list, &envp);
	prepare_args(cmd, &args);
	pid_t	pid;
	pid = fork();
	if (pid == -1)
	{
		print_line("Failed to create child process :(", 1);
		return (0);
	}
	if (!pid)
		exit (execve(cmd->cmd, args, envp));
	else
		wait(&status);
	free_strs_arr(&envp);
	free_strs_arr(&args);
	if (status > 256)
		return (0);
	else if (status > 0)
		g_exit_status = 1;
	return (1);
}

/*
**  A function that gets coordinates of quotes in string
*/

static t_coords	get_quotes_coords(const char *str, int i)
{
	t_coords	coords;

	coords.start = i;
	coords.type = 0;
	while (str[coords.start])
	{
		if (str[coords.start] == '\'' && !is_symb_esc(str, coords.start))
			coords.type = 1;
		else if (str[coords.start] == '"' && !is_symb_esc(str, coords.start))
			coords.type = 2;
		if (coords.type)
			break ;
		++coords.start;
	}
	if (str[coords.start] != '\0')
	{
		coords.end = coords.start + 1;
		while (str[coords.end])
		{
			if ((coords.type == 1 && str[coords.end] == '\'') || (coords.type == 2 && str[coords.end] == '"'))
				break ;
			++coords.end;
		}
	}
	return (coords);
}

/*
**  A function that checks if string is multiline
*/

static int	check_multiline(char *str)
{
	int	i;

	i = ft_strlen(str);
	if ((str[i - 1] != '\'' && str[i - 1] != '"') || (!ms_strcmp(str, "'") || !ms_strcmp(str, "\"")))
		return (1);
	return (0);
}

/*
**  A function that parses quotes string in simple string by coordinates
*/

static char	*prepare_quotes_str(char *str, t_list *env_list, t_coords coords, int i)
{
	char	*parsed_quotes;
	char	*tmp;

	parsed_quotes = ft_substr(str, coords.start, (coords.end + 1 - coords.start));
	if (check_multiline(parsed_quotes))
		return (NULL);
	tmp = parsed_quotes;
	parsed_quotes = parse_qoutes(parsed_quotes, env_list);
	free(tmp);
	if (ft_strchr("\"'", str[i]))
		tmp = ft_strdup("");
	else
		tmp = ft_substr(str, i, coords.start - i);
	safe_strjoin(&tmp, parsed_quotes);
	free(parsed_quotes);
	return (tmp);
}

/*
**  A function that gets coordinates of quotes string and parses that string
*/

static int	swap_quotes(char **str, t_list *env_list)
{
	t_coords	coords;
	int 		i;
	char		*tmp;
	char		*tmp2;

	i = 0;
	if (ms_bs_strchr(*str, '\'') || ms_bs_strchr(*str, '"'))
	{
		tmp = ft_strdup(*str);
		tmp2 = NULL;
		free(*str);
		*str = ft_strdup("");
		while (tmp[i])
		{
			coords = get_quotes_coords(tmp, i);
			free(tmp2);
			tmp2 = prepare_quotes_str(tmp, env_list, coords, i);
			if (!tmp2)
			{
				free(tmp);
				free(tmp2);
				return (1);
			}
			safe_strjoin(&(*str), tmp2);
			i = coords.end + 1;
		}
		free(tmp);
		free(tmp2);
	}
	else
		swap_env(str, env_list);
	return (0);
}

/*
**  A function that removes alone '\' and handles '\\' into '\'
*/

static void		handle_bslash(char **str)
{
	char	*tmp;
	int 	i;
	int 	str_diff;

	tmp = ft_strdup(*str);
	i = 0;
	str_diff = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\\')
		{
			if (tmp[i + 1] == '\\')
			{
				ms_strswap(str, "\\", (i - str_diff), 1);
				++i;
			}
			else
				ms_strswap(str, "", (i - str_diff), 0);
			++str_diff;
		}
		++i;
	}
	free(tmp);
}

/*
**  A function that checks for quotes and replace them
*/

static int	check_quotes(t_cmd *cmd, t_list *env_list)
{
	int 		i;
	swap_env(&cmd->cmd, env_list);
	if (swap_quotes(&cmd->cmd, env_list))
		return (1);
	handle_bslash(&cmd->cmd);
	if (!cmd->args)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		swap_env(&cmd->args[i], env_list);
		if (swap_quotes(&cmd->args[i], env_list))
			return (1);
		handle_bslash(&cmd->args[i]);
		++i;
	}
	return (0);
}

/*
**  A function that checks what command to execute
*/

static int	check_cmd(t_cmd *cmd, t_list **env_list)
{
	handle_redirects(cmd);
	if (!ms_strcmp(cmd->cmd, "echo"))
		ms_echo(cmd->args);
	else if (!ms_strcmp(cmd->cmd, "cd"))
		ms_cd(cmd->args, *env_list);
	else if (!ms_strcmp(cmd->cmd, "pwd"))
		print_pwd();
	else if (!ms_strcmp(cmd->cmd, "export"))
		ms_export(cmd, env_list);
	else if (!ms_strcmp(cmd->cmd, "unset"))
		ms_unset(cmd, env_list);
	else if (!ms_strcmp(cmd->cmd, "env"))
		ms_env(*env_list);
	else if (!ms_strcmp(cmd->cmd, "exit"))
		return (7);							//!!!MAKE EXIT HERE!!!
	else if (!try_external_cmd(cmd, env_list))
		return (0);
	return (1);
}

/*
**  A function that executes command
*/

static void	execute_cmd(t_cmd *cmd, t_list **env_list)
{
	int	stdout_fd;
	int	stdin_fd;

	stdin_fd = dup(0);
	stdout_fd = dup(1);
	if (check_quotes(cmd, *env_list))
	{
		print_error(MLA, "MULTILINE", 5);
		g_exit_status = 1;
	}
	else if (!check_cmd(cmd, env_list) && ms_strcmp(cmd->cmd, ""))
	{
		print_error(CNF, cmd->cmd, 1);
		g_exit_status = 127;
	}
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	close(stdin_fd);
	close(stdout_fd);
}

/*
**  Functions in processor executes sequently (pipe commands executes together)
*/

void		processor(t_cmd	**cmd_arr, t_list **env_list)
{
	int 	i;
	int 	is_pipe;

	i = 0;
	is_pipe = 0;
	while (cmd_arr[i])
	{
		if (cmd_arr[i]->end == '|')
			is_pipe = 1;
		else if ((cmd_arr[i]->end == ';' || cmd_arr[i]->end == '\0') && !is_pipe)
			execute_cmd(cmd_arr[i], env_list);
		++i;
	}
}
