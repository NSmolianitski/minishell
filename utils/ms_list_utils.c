/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:46:42 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:46:44 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that prints environment variable list
*/

void	print_list(t_list *lst, int export)
{
	while (lst)
	{
		if (export)
			print_line("declare -x ", 1);
		if (lst->content == NULL && !export)
		{
			lst = lst->next;
			continue ;
		}
		print_line(lst->name, 1);
		if (lst->content != NULL)
			write(1, "=", 1);
		if (lst->content != NULL && export)
			print_line("\"", 1);
		print_line(lst->content, 1);
		if (lst->content != NULL && export)
			print_line("\"", 1);
		write(1, "\n", 1);
		lst = lst->next;
	}
}

/*
**  A function that gets environment variable content
*/

char	*get_var_content(t_list *lst, char *var_name)
{
	char	*content;

	if (!var_name)
	{
		content = ft_strdup("$");
		return (content);
	}
	while (lst)
	{
		if (!ms_strcmp(lst->name, var_name))
		{
			content = ft_strdup(lst->content);
			return (content);
		}
		lst = lst->next;
	}
	return (0);
}

/*
**  A function that tries to find environment variable in list
*/

int		find_var(t_list *lst, char *var_name)
{
	while (lst)
	{
		if (!ms_strcmp(lst->name, var_name))
			return (1);
		lst = lst->next;
	}
	return (0);
}

/*
**  A function that changes content of the environment variable in list
*/

int		change_var_content(t_list *lst, char *var_name, char *content)
{
	while (lst)
	{
		if (!ms_strcmp(lst->name, var_name))
		{
			free(lst->content);
			lst->content = content;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

/*
**  A function that removes variable from environment list
*/

void	*rm_var(t_list **lst, char *var_name)
{
	t_list	*prev;
	t_list	*temp;

	temp = *lst;
	prev = 0;
	while (temp)
	{
		if (!ms_strcmp(temp->name, var_name))
		{
			free(temp->name);
			free(temp->content);
			if (!prev)
				*lst = temp->next;
			else
				prev->next = temp->next;
			free(temp);
			return (0);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
