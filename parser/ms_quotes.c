/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <kmichiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:36:13 by kmichiko          #+#    #+#             */
/*   Updated: 2021/01/23 21:38:27 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *proccess_double_quotes(char *str, int i)
{
	int len;
	int j;
	char *result;

	j = i;
	while (str[j] != '\0' && str[j] != '"')
	{
		len++;
		j++;
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	while (str[i] != '\0' && str[i] != '"')
	{
		result[j] = str[i];
		i++;
		j++;
	}
	
}

char *proccess_single_quotes(char *str, int i)
{
	
}
char *parse_qoutes(char *str)
{
	int i;
	char *result;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			result = proccess_double_quotes(str, i);
			return result;
		}
		else if (str[i] == 39)
		{
			i++;
			result = proccess_single_quotes(str, i);
			return result;
		}
		i++;
	}
	return (str);
}


