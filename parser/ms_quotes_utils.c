/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:57:01 by kmichiko          #+#    #+#             */
/*   Updated: 2021/02/13 11:57:07 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

char		*get_exit_status_env(char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(str);
	tmp2 = ft_itoa(g_exit_status);
	ms_strswap(&tmp, tmp2, 0, ft_strlen(str));
	safe_strjoin(&tmp, str + 1);
	free(tmp2);
	tmp2 = NULL;
	return (tmp);
}

char		*parse_env(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (str[i] != '\0' &&
		(ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		i++;
		while (str[i] != '\0' &&
		(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?') && str[i] != '$')
			i++;
	}
	if (i == 0 || !(result = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char		*parse_backslash(char *str, int *offset)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (str[i] != '\0' && ft_strchr("\"\\`$", str[i]))
	{
		result = (char *)malloc((2) * sizeof(char));
		result[i] = str[i];
		i++;
		*offset = 2;
	}
	else
	{
		result = (char *)malloc((2) * sizeof(char));
		result[i] = '\\';
		i++;
		*offset = 1;
	}
	result[i] = '\0';
	return (result);
}

void		join_result(char **tmp2, char **result)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(*result, *tmp2);
	free_arr(tmp2);
	free_arr(result);
	*result = tmp;
	tmp = NULL;
}

int			proccess_simple_text(char *str, char **result)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	k = 0;
	while (str[j] != '\0' && str[j] != '\\' && str[j] != '$' && str[j] != '"')
		j++;
	tmp = (char *)malloc((j + 1) * sizeof(char));
	while (k < j)
	{
		tmp[k] = str[k];
		k++;
	}
	tmp[k] = '\0';
	safe_strjoin(result, tmp);
	free_arr(&tmp);
	return (j);
}
