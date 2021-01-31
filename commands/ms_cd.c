#include <unistd.h>
#include "ms_utils.h"

int		ms_cd(char **args, t_list *env_list)
{
	int		result;
	int		i;
	char	*str;

	i = 0;
	result = 0;
	while (args && args[i] != NULL)
		i++;
	if (i == 0)
	{
		str = get_var_content(env_list, "HOME");
		if (str)
			result = chdir(str);
		else
			result = -2;
		free(str);
	}
	else if (i > 0)
		result = chdir(args[0]);
	if (result == -1)
		print_error(NSFD, args[0], 4);
	else if (result == -2)
		print_error(HNS, "", 4);
	return ((result < 0) ? 1 : 0);
}
