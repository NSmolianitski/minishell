#include <unistd.h>
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_commands.h"

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
		*args = malloc(sizeof(char *));
		(*args)[0] = 0;
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

static void free_char_arr(char ***args)
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
	wait(&status);
	if (!pid)
	{
		execve(cmd->cmd, args, envp);
		return (0);
	}
	free_char_arr(&envp);
	free_char_arr(&args);
	return (1);
}

static int	check_cmd(t_cmd *cmd, t_list **env_list)
{
	if (!ms_strcmp(cmd->cmd, "echo"))
		ms_echo(cmd->args);
	else if (!ms_strcmp(cmd->cmd, "cd"))
		return (2);							//!!!MAKE CD HERE!!!
	else if (!ms_strcmp(cmd->cmd, "pwd"))
		return (3);							//!!!MAKE PWD HERE!!!
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

void		processor(t_cmd	**cmd_arr, t_list **env_list)
{
	int 	i;

	i = 0;
	while (cmd_arr[i])
	{
		if (!check_cmd(cmd_arr[i], env_list))
			print_error(CNF, cmd_arr[i]->cmd, 1);
		++i;
	}
}
