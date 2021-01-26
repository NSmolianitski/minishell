/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <kmichiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:35:06 by kmichiko          #+#    #+#             */
/*   Updated: 2021/01/26 22:08:15 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_utils.h"

int 	ms_cd(char **args)
{
	int result;
	int i;
	char *str;

	i = 0;
	result = 0;
	while(args && args[i] != NULL)
		i++;
	if (i == 0)
	{
		str = NULL;
		str = getcwd(str, 0);
		result = chdir(str);
		free(str);
		str = NULL;
	}
	else if (i == 1)
		result = chdir(args[0]);
	else
	{
		print_error(SNIP, "cd", 1);
		write(1, "\n", 1);
	}
	if (result == -1)
	{
		print_error(NSFD, "cd", 1);
		write(1, "\n", 1);
	}
	return (result);
}
