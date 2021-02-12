/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:32:05 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:32:06 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
**  A function that prints shell tag
*/

void			print_shell_tag(void)
{
	write(1, "\033[32m", ft_strlen("\033[32m"));
	write(1, "minishell$ ", 11);
	write(1, "\033[0m", ft_strlen("\033[0m"));
}

static void		count_something_and_malloc(const char *env, char **name)
{
	int		j;

	j = 0;
	while (env[j] != '=')
		++j;
	*name = malloc(sizeof(char) * (j + 1));
}

void			get_env(const char *env, char **name, char **content)
{
	int		i;
	int		j;

	count_something_and_malloc(env, name);
	i = 0;
	while (env[i] != '=')
	{
		(*name)[i] = env[i];
		++i;
	}
	(*name)[i] = '\0';
	++i;
	j = i;
	while (env[j] != '\0')
		++j;
	*content = malloc(sizeof(char) * ((j - i) + 1));
	j = 0;
	while (env[i] != '\0')
	{
		(*content)[j] = env[i];
		++i;
		++j;
	}
	(*content)[j] = '\0';
}

void			gcl_norm(int flag)
{
	if (!flag)
		exit(1);
	write(1, "  \b\b", 4);
}
