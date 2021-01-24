#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

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