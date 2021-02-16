/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:59:44 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:59:46 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_utils.h"
#include "ms_processor.h"

static char		*find_env_in_word(const char *cmd, char *env_start)
{
	char	*env_end;
	char	*env;
	int		i;

	env_end = ms_strmultichr(env_start, "$'\"=/");
	if (!env_end)
		i = ft_strlen(env_start);
	else
		i = env_end - env_start;
	env = ft_substr(cmd, (env_start - cmd), i);
	return (env);
}

static void		check_content(char **content, char **cmd, char *tmp)
{
	if (!*content)
	{
		if (ft_strchr("+=", (*cmd)[1]))
		{
			free(tmp);
			return ;
		}
		else
			*content = ft_strdup("");
	}
}

/*
**  A function that swaps command with env variable
*/

void			swap_env(char **cmd, t_list *env_list)
{
	char	*env_start;
	char	*content;
	char	*tmp;
	int		len;

	while (*cmd && ft_strchr_quotes(*cmd, '$') && ms_strcmp("$", *cmd))
	{
		env_start = ft_strchr_quotes(*cmd, '$');
		tmp = find_env_in_word(*cmd, env_start + 1);
		if (ft_strchr(tmp, '?'))
			content = ft_itoa(g_exit_status);
		else
			content = get_var_content(env_list, tmp);
		check_content(&content, cmd, tmp);
		len = ft_strlen(tmp);
		if (ft_strnstr(*cmd, "$?", ft_strlen(*cmd)))
			len = 1;
		ms_strswap(cmd, content, (ft_strchr_quotes(*cmd, '$') - *cmd), len);
		if (!ms_strcmp(*cmd, ""))
		{
			free(*cmd);
			*cmd = ft_strdup("ENV NO CONTENT!");
		}
		double_free(tmp, content);
	}
}
