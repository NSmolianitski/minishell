/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <kmichiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:55:38 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/13 10:30:53 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ms_utils.h"
#include "ms_parser.h"

int			process_env(char *str, t_list *env_list, char **env)
{
	char	*tmp2;
	int		i;

	i = 0;
	tmp2 = NULL;
	*env = NULL;
	free_arr(env);
	tmp2 = parse_env(&str[i]);
	if (str[i] == '?')
		*env = get_exit_status_env(tmp2);
	else
		*env = get_var_content(env_list, tmp2);
	if (str[i] != '"' && tmp2)
		i += ft_strlen(tmp2);
	free_arr(&tmp2);
	return (i);
}

void		proccess_str(char *str, char **result, char **env, t_list *env_list)
{
	int		i;
	int		offset;
	char	*tmp2;

	i = 0;
	while (str[i] != '\0' && str[i] != '"')
	{
		if (str[i] == '\\')
		{
			tmp2 = parse_backslash(&str[i + 1], &offset);
			join_result(&tmp2, result);
			i += offset;
		}
		else if (str[i] == '$')
		{
			i++;
			i += process_env(&str[i], env_list, env);
			if (!(*env))
				continue ;
			join_result(env, result);
		}
		else
			i += proccess_simple_text(&str[i], result);
	}
}

char		*proccess_double_quotes(char *str, t_list *env_list)
{
	char	*result;
	char	*env;

	env = NULL;
	result = ft_strdup("");
	proccess_str(str, &result, &env, env_list);
	free_arr(&env);
	return (result);
}

char		*proccess_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char		*parse_qoutes(char *str, t_list *env_list)
{
	int		i;
	char	*result;

	i = 0;
	if (str[0] == '\0')
		str = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			result = proccess_double_quotes(&str[i], env_list);
			return (result);
		}
		else if (str[i] == '\'')
		{
			i++;
			result = proccess_single_quotes(&str[i]);
			return (result);
		}
		i++;
	}
	return (str);
}
