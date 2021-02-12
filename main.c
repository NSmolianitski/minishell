/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:32:25 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:32:26 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ms_utils.h"
#include "libft.h"
#include "ms_parser.h"
#include "ms_processor.h"

/*
**  A function that gets the command line from input
*/

static char		*get_cmd_line(void)
{
	char	buff[2];
	char	*cmd_line;
	char	*tmp;
	int		read_bytes;
	int		flag;

	cmd_line = ft_strdup("");
	flag = 0;
	while ((read_bytes = read(0, buff, 1)) >= 0)
	{
		if (read_bytes == 0)
		{
			gcl_norm(flag);
			continue ;
		}
		flag = 1;
		if (buff[read_bytes - 1] == '\n')
			buff[read_bytes - 1] = '\0';
		tmp = cmd_line;
		cmd_line = ft_strjoin(cmd_line, buff);
		free(tmp);
		if (read_bytes > 0 && buff[read_bytes - 1] == '\0')
			break ;
	}
	return (cmd_line);
}

static void		pf_norm(t_cmd **cmd_arr, int *i)
{
	cmd_arr[*i]->args = NULL;
	free(cmd_arr[*i]);
	cmd_arr[*i] = NULL;
	++(*i);
}

/*
**  A function that frees commands array and command line
*/

static void		parser_free(char **cmd_line, t_cmd **cmd_arr)
{
	int		i;
	int		j;

	free(*cmd_line);
	*cmd_line = NULL;
	i = 0;
	while (cmd_arr[i])
	{
		free(cmd_arr[i]->cmd);
		cmd_arr[i]->cmd = NULL;
		if (cmd_arr[i]->args != NULL)
		{
			j = 0;
			while (cmd_arr[i]->args[j])
			{
				free(cmd_arr[i]->args[j]);
				++j;
			}
			free(cmd_arr[i]->args);
		}
		pf_norm(cmd_arr, &i);
	}
	free(cmd_arr[i]);
	cmd_arr[i] = NULL;
	free(cmd_arr);
}

/*
**  A function that creates a list from envp
*/

static void		make_env_list(char **envp, t_list **env_list)
{
	int		i;
	char	*name;
	char	*content;
	t_list	*new_lst;

	i = 0;
	get_env(envp[i], &name, &content);
	*env_list = ft_lstnew(name, content);
	++i;
	while (envp[i])
	{
		get_env(envp[i], &name, &content);
		new_lst = ft_lstnew(name, content);
		ft_lstadd_back(env_list, new_lst);
		++i;
	}
}

int				main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_cmd	**cmd_arr;
	t_list	*env_list;

	argc += 0;
	argv += 0;
	g_exit_status = 0;
	g_signal_flag = 0;
	make_env_list(envp, &env_list);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	while (1)
	{
		print_shell_tag();
		g_signal_flag = 0;
		cmd_line = get_cmd_line();
		cmd_arr = parser(cmd_line);
		if (!cmd_arr)
		{
			free(cmd_line);
			continue;
		}
		processor(cmd_arr, &env_list);
		parser_free(&cmd_line, cmd_arr);
	}
}
