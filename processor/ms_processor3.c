/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:50:42 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:54:03 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

static void		gqc_norm(t_coords *coords, const char *str)
{
	coords->end = coords->start + 1;
	while (str[coords->end])
	{
		if ((coords->type == 1 && str[coords->end] == '\'') ||
		(coords->type == 2 &&
		(str[coords->end] == '"' && !is_symb_esc(str, coords->end))))
			break ;
		++coords->end;
	}
}

/*
**  A function that gets coordinates of quotes in string
*/

t_coords		get_quotes_coords(char **str, int i)
{
	t_coords	cr;

	cr.start = i;
	cr.type = 0;
	while ((*str)[cr.start])
	{
		if ((*str)[cr.start] == '\'' && !is_symb_esc(*str, cr.start))
			cr.type = 1;
		else if ((*str)[cr.start] == '"' && !is_symb_esc(*str, cr.start))
			cr.type = 2;
		else if (is_symb_esc(*str, cr.start))
			cr.start = check_bslash2(str, cr.start - 1);
		if (cr.type)
			break ;
		++cr.start;
	}
	if ((*str)[cr.start] != '\0')
	{
		gqc_norm(&cr, *str);
		if ((*str)[cr.end] == '\0')
			cr.type = 3;
	}
	else
		cr.type = 4;
	return (cr);
}

/*
**  A function that checks if string is multiline
*/

int				check_multiline(char *str)
{
	int	i;

	i = ft_strlen(str);
	if ((str[i - 1] != '\'' && str[i - 1] != '"') ||
	(!ms_strcmp(str, "'") || !ms_strcmp(str, "\"")))
		return (1);
	return (0);
}

/*
**  A function that parses quotes string in simple string by coordinates
*/

char			*prepare_quotes_str(char *str, t_list *env_list,
						t_coords coords, int i)
{
	char	*parsed_quotes;
	char	*tmp;

	parsed_quotes = ft_substr(str, coords.start,
	(coords.end + 1 - coords.start));
	if (check_multiline(parsed_quotes))
		return (NULL);
	tmp = parsed_quotes;
	parsed_quotes = parse_qoutes(parsed_quotes, env_list);
	free(tmp);
	tmp = ft_substr(str, i, coords.start - i);
	safe_strjoin(&tmp, parsed_quotes);
	free(parsed_quotes);
	return (tmp);
}
