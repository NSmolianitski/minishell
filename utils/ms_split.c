/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:46:50 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:46:51 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

static int		count_words(const char *str)
{
	int		i;
	int		words_num;

	i = 0;
	words_num = 0;
	while (str[i])
	{
		if (str[i] == ' ' && !is_symb_esc(str, i))
		{
			i = skip_spaces(str, i);
			++words_num;
		}
		++i;
	}
	if (str[i] == '\0')
		++words_num;
	return (words_num);
}

static int		get_word_coords(const char *str, int *start, char c)
{
	int len;

	len = 0;
	if (*start > 0)
		len = 1;
	while (str[len + *start])
	{
		if (str[len + *start] == c && !is_symb_esc(str, len + *start))
			break ;
		++len;
	}
	return (len);
}

char			**ms_split(const char *str, char c)
{
	char	**arr;
	int		words_num;
	int		i;
	int		start;
	int		len;

	words_num = count_words(str);
	arr = malloc(sizeof(char *) * (words_num + 1));
	arr[words_num] = NULL;
	i = 0;
	start = 0;
	len = 0;
	while (i < words_num)
	{
		start += len;
		len = get_word_coords(str, &start, c);
		arr[i] = ft_substr(str, start, len);
		++len;
		++i;
	}
	return (arr);
}
