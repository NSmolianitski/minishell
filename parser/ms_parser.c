#include "ms_utils.h"
#include "libft.h"

static char	*get_cmd(char const *cmd_line)
{
	char	*cmd;
	int 	i;

	i = 0;
	while (cmd_line[i])
	{
		++i;
		if (ft_strchr(" ;", cmd_line[i - 1]))
			break ;
	}
	if (cmd_line[i] == '\0')
		++i;
	cmd = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(cmd, cmd_line, i);
	return (cmd);
}

char	*parser(char *cmd_line)
{
	char	*cmd;

	cmd = get_cmd(cmd_line);
	return (cmd);
}