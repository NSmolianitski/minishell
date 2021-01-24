/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <kmichiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:36:13 by kmichiko          #+#    #+#             */
/*   Updated: 2021/01/24 14:15:50 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char *trim_quotes(char *str, char ch)
{
	int i;
	int j;
	char *result;

	i = 0;
	while (str[i] != '\0' && (str[i] != ch || (i > 0 && str[i - 1] == '\\' && str[i] == '"')))
	{
		i++;
	}
	result = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char *proccess_double_quotes(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	while (str[i] != '\0' && str[i] != '"')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char *proccess_single_quotes(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	while(str[i] != '\0' && str[i] != '\'')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	while(j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}


char *check_scape_symbols(char *str)
{
	int i;
	char *result;
	char *escape;
	int len;
	int count;

	i = 0;
	count = 0;
	len = ft_strlen(str);
	escape = (char *)ft_calloc(len,  sizeof(char));
	while(str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
		{
			i++;
			if (ft_strchr("\"\\$`", str[i]))
			{
				escape[i-1] = '1';
				if (str[i] == '$')
					escape[i] = '$';
			}
		}
		else 
			i++;
	}
	i = 0;
	while(i < len)
	{
		if (escape[i] == '1')
			count++;
		i++;
	}
	result = (char *)malloc((len - count) * sizeof(char));
	i = 0;
	while(i < (len - count))
	{
		if (escape[i] != '1')
			result[i] = str[i];
		i++;
	}

	result[i] = '\0';
	return (result);
}

char *parse_qoutes(char *str)
{
	int i;
	char *result;
	int is_double_quotes;

	i = 0;
	is_double_quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			result = trim_quotes(&str[i], '"');
			//TO DO free
			result = check_scape_symbols(result);
			is_double_quotes = 1;
			return (result);
		}
		else if (str[i] == 39)
		{
			i++;
			result = trim_quotes(&str[i], 39);
			is_double_quotes = 0;
			return (result);
		}
		i++;
	}
	return (str);
}


int main()
{
	char *str;
	int i;
	int len;
	int len2;

	i = 0;
	//argc+=0;
	//char test[] = "'123'''\"hello\"'''''";
	
	char test[] = "\"hello\"";
	//char *test = argv[1];
	len = strlen(test);
	while(i < len && test[i] != '\0')
	{
		
		str = parse_qoutes(&test[i]);
		len2 = strlen(str);
		printf("%s |len=%d\n", str, len2);
		i += len2;
		if (test[i] != '\0')
			i++;
	}
	return (0);
}