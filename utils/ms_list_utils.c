#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that prints environment variable list
*/

void	print_list(t_list *lst)
{
	while (lst)
	{
		print_line(lst->name, 1);
		write(1, "=", 1);
		print_line(lst->content, 1);
		write(1, "\n", 1);
		lst = lst->next;
	}
}

/*
**  A function that gets environment variable content
*/

char	*get_var_content(t_list *lst, char *var_name)
{
	while (lst)
	{
		if (!ms_strcmp(lst->name, var_name))
			return (lst->content);
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
