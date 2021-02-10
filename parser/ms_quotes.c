#include <stdlib.h>
#include "libft.h"
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

void	free_arr(char *tmp)
{
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}

char	*parse_env(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (str[i] != '\0' && (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		i++;
		while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
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

static char *get_exit_status_env(char *str)
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
	i = 0;
	result = ft_strdup("");
	while (str[i] != '\0' && str[i] != '"')
	{
		if (str[i] == '\\')
		{
			tmp2 = parse_backslash(&str[i + 1], &offset);
			tmp = ft_strjoin(result, tmp2);
			free_arr(tmp2);
			free_arr(result);
			result = tmp;
			i += offset;
		}
		else if (str[i] == '$')
		{
			i++;
			free_arr(env);
			tmp2 = parse_env(&str[i]);
			if (str[i] == '?')
				env = get_exit_status_env(tmp2);
			else
				env = get_var_content(env_list, tmp2);
			if (!env)
			{
				while (str[i] != '"')
					++i;
				++i;
				continue ;
			}
			free_arr(tmp2);
			tmp2 = tmp;
			tmp = ft_strjoin(result, env);
			free_arr(tmp2);
			free_arr(result);
			result = tmp;
			tmp = NULL;
			tmp2 = parse_env(&str[i]);
			if (str[i] != '"' && tmp2)
				i += ft_strlen(tmp2);
			free_arr(tmp2);
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
			free_arr(tmp2);
			i += j;
			free_arr(tmp);
		}
	}
	free_arr(env);
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
