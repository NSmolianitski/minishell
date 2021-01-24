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