/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checkpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:37:20 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:37:22 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"
#include "libft.h"

void	free_array(char **path)
{
	int i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		path[i] = NULL;
	}
	free(path);
	path = NULL;
}

char	*get_path(char *cmd, t_list **env_list)
{
	char		**path;
	char		*exec_path;
	int			i;
	struct stat	buf;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path = ft_split(get_var_content(*env_list, "PATH"), ':');
	i = 0;
	while (path && path[i] != NULL)
	{
		exec_path = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (lstat(exec_path, &buf) == -1)
		{
			free(exec_path);
		}
		else
			return (exec_path);
		i++;
	}
	return (cmd);
}
