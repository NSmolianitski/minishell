/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:05:22 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 13:05:24 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

/*
**  A function that reallocates array (makes new empty strings by index)
*/

static char	**realloc_arr(char **arr, int index, int add_size)
{
	char	**new_arr;
	int		arr_len;
	int		i;

	arr_len = 0;
	if (arr)
		while (arr[arr_len])
			++arr_len;
	new_arr = malloc(sizeof(char *) * (arr_len + add_size + 1));
	new_arr[arr_len + add_size] = NULL;
	if (!arr)
		return (new_arr);
	i = 0;
	while (arr[i])
	{
		if (i >= index)
			new_arr[i + add_size] = ft_strdup(arr[i]);
		else
			new_arr[i] = ft_strdup(arr[i]);
		free(arr[i]);
		++i;
	}
	free(arr);
	return (new_arr);
}

static void	cme_norm(int *j, char **arr)
{
	*j = 0;
	while (arr[*j])
		++(*j);
}

static void	cme_norm2(t_cmd *cmd, int j, int i, char **arr)
{
	while (arr[i])
	{
		cmd->args[j] = arr[i];
		++i;
		++j;
	}
}

/*
**  A function that checks for multiword env
*/

void		check_multiword_env(t_cmd *cmd)
{
	char	**arr;
	int		i;
	int		j;

	arr = ms_split(cmd->cmd, ' ');
	if (!arr[0])
	{
		free(arr);
		return ;
	}
	cme_norm(&j, arr);
	if (j == 1)
	{
		free_strs_arr(&arr);
		return ;
	}
	free(cmd->cmd);
	cmd->cmd = arr[0];
	cmd->args = realloc_arr(cmd->args, 0, j - 1);
	i = 1;
	j = 0;
	cme_norm2(cmd, j, i, arr);
	free(arr);
}
