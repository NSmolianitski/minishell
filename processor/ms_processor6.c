/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:52:00 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 13:52:01 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

void	sq_norm(char *tmp, char *tmp2, char **str, int i)
{
	tmp2 = ft_substr(tmp, i, ft_strlen(tmp + i));
	safe_strjoin(&(*str), tmp2);
	double_free(tmp, tmp2);
}

void	sq_norm2(char **tmp2, char **str)
{
	safe_strjoin(&(*str), *tmp2);
	free(*tmp2);
	*tmp2 = NULL;
}

int		sq_norm4(char **tmp, char **tmp2, char **str)
{
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	sq_norm2(tmp2, str);
	return (0);
}

void	sq_norm5(char **tmp, char **str, char **tmp2)
{
	*tmp = ft_strdup(*str);
	*tmp2 = NULL;
	free(*str);
	*str = ft_strdup("");
}

int		sq_norm6(int i, char **str, t_list *env_list, char *tmp)
{
	t_coords	coords;
	char		*tmp2;

	sq_norm5(&tmp, str, &tmp2);
	while (tmp[i])
	{
		coords = get_quotes_coords(tmp, i);
		if (coords.type == 3)
		{
			free(tmp);
			return (1);
		}
		else if (coords.type == 4)
		{
			sq_norm(tmp, tmp2, str, i);
			return (0);
		}
		free(tmp2);
		tmp2 = prepare_quotes_str(tmp, env_list, coords, i);
		if (sq_norm4(&tmp, &tmp2, str))
			return (1);
		i = coords.end + 1;
	}
	double_free(tmp, tmp2);
	return (2);
}
