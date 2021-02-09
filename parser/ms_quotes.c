#include <stdlib.h>
#include "libft.h"
#include "ms_utils.h"
#include "ms_parser.h"

char	*parse_env(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (str[i] != '\0' && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		i++;
		while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
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

char	*parse_backslash(char *str, int *offset)
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

char	*proccess_double_quotes(char *str, t_list *env_list)
{
	int		i;
	int		j;
	int		offset;
	char	*result;
	char	*env;
	char	*tmp;
	char	*tmp2;
	int		k;

	env = NULL;
	result = NULL;
	tmp = NULL;
	tmp2 = NULL;
	offset = 0;
	j = 0;
	i = 0;
	result = ft_strdup("");
	while (str[i] != '\0' && str[i] != '"')
	{
		if (str[i] == '\\')
		{
			tmp2 = parse_backslash(&str[i + 1], &offset);
			tmp = ft_strjoin(result, tmp2);
			if (tmp2)
			{
				free(tmp2);
				tmp2 = NULL;
			}
			if (result)
			{
				free(result);
				result = NULL;
			}
			result = tmp;
			i += offset;
		}
		else if (str[i] == '$')
		{
			i++;
			if (env)
			{
				free(env);
				env = NULL;
			}
			tmp2 = parse_env(&str[i]);
			env = get_var_content(env_list, tmp2);
			if (!env)
			{
				while (str[i] != '"')
					++i;
				++i;
				continue ;
			}
			free(tmp2);
			tmp2 = NULL;
			tmp2 = tmp;
			tmp = ft_strjoin(result, env);
			free(tmp2);
			tmp2 = NULL;
			if (result)
			{
				free(result);
				result = NULL;
			}
			result = tmp;
			tmp = NULL;
			tmp2 = parse_env(&str[i]);
			if (str[i] != '"')
				i += ft_strlen(tmp2);
			free(tmp2);
			tmp2 = NULL;
		}
		else
		{
			k = 0;
			j = 0;
			while (str[i + j] != '\0' && str[i + j] != '\\' && str[i + j] != '$' && str[i + j] != '"')
				j++;
			tmp = (char *)malloc((j + 1) * sizeof(char));
			while (k < j)
			{
				tmp[k] = str[i + k];
				k++;
			}
			tmp[k] = '\0';
			tmp2 = result;
			result = ft_strjoin(result, tmp);
			free(tmp2);
			tmp2 = NULL;
			i += j;
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	if (env)
	{
		free(env);
		env = NULL;
	}
	return (result);
}

char	*proccess_single_quotes(char *str)
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

char	*parse_qoutes(char *str, t_list *env_list)
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
