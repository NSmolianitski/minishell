#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ms_utils.h"
#include "ms_parser.h"

/*
**  A function that removes unnecessary '>>' redirect and file name
*/

static void rm_redir_append(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		++i;
	if (i == 3 && cmd->args[0][0] == '>')
	{
		free(cmd->args[0]);
		free(cmd->args[1]);
		free(cmd->args[2]);
		free(cmd->args);
		cmd->args = NULL;
		return ;
	}
	new_args = malloc(sizeof(char *) * (i - 2));
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (i == index)
		{
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			free(cmd->args[i + 2]);
			i += 3;
			continue ;
		}
		new_args[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		++i;
		++j;
	}
	new_args[j] = 0;
	free(cmd->args);
	cmd->args = new_args;
}

/*
**  A function that removes unnecessary '>' redirect and file name
*/

static void rm_redir_out(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		++i;
	if (i == 2 && cmd->args[0][0] == '>')
	{
		free(cmd->args[0]);
		free(cmd->args[1]);
		free(cmd->args);
		cmd->args = NULL;
		return ;
	}
	new_args = malloc(sizeof(char *) * (i - 1));
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (i == index)
		{
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			i += 2;
			continue ;
		}
		new_args[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		++i;
		++j;
	}
	new_args[j] = 0;
	free(cmd->args);
	cmd->args = new_args;
}

/*
**  A function that removes unnecessary '<' redirect and file name
*/

static void rm_redir_in(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		++i;
	if (i == 2 && cmd->args[0][0] == '<')
	{
		free(cmd->args[0]);
		free(cmd->args[1]);
		free(cmd->args);
		cmd->args = NULL;
		return ;
	}
	new_args = malloc(sizeof(char *) * (i - 1));
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (i == index)
		{
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			i += 2;
			continue ;
		}
		new_args[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		++i;
		++j;
	}
	new_args[j] = 0;
	free(cmd->args);
	cmd->args = new_args;
}

/*
**  A function that replaces file descriptors for redirects
*/

static void make_redir(char *file, int stream, t_cmd *cmd, int index)
{
	int		temp_fd;
	char	buff[1000];

	if (stream == 3)
	{
		temp_fd = open(file, O_RDWR | O_CREAT, 0666);
		while (read(temp_fd, buff, 999));
		dup2(temp_fd, 1);
		rm_redir_append(cmd, index);
	}
	else if (stream == 1)
	{
		temp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(temp_fd, 1);
		rm_redir_out(cmd, index);
	}
	else
	{
		temp_fd = open(file, O_RDWR | O_CREAT, 0666);
		dup2(temp_fd, 0);
		rm_redir_in(cmd, index);
	}
	close(temp_fd);
}

/*
**  A function that handles redirects if they exists
*/

void handle_redirects(t_cmd *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!ms_strcmp(">", cmd->args[i]) && ms_strcmp(">", cmd->args[i + 1]))
		{
			make_redir(cmd->args[i + 1], 1, cmd, i);
			i = 0;
		}
		else if (!ms_strcmp("<", cmd->args[i]))
		{
			make_redir(cmd->args[i + 1], 0, cmd, i);
			i = 0;
		}
		else if (!ms_strcmp(">", cmd->args[i]) && !ms_strcmp(">", cmd->args[i + 1]))
		{
			make_redir(cmd->args[i + 2], 3, cmd, i);
			i = 0;
		}
		++i;
	}
}