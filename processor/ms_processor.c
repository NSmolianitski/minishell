#include <unistd.h>
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
**  A function that checks what command to execute
*/

static int	check_cmd(t_cmd *cmd, t_list **env_list)
{
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
	int 	i;

	swap_env(&cmd->cmd, *env_list);
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			swap_env(&cmd->args[i], *env_list);
			++i;
		}
	}
	if (!check_cmd(cmd, env_list))
	{
		print_error(CNF, cmd->cmd, 1);
		g_exit_status = 127;
	}
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
