#include <unistd.h>
#include <stdlib.h>
#include "ms_utils.h"
#include "libft.h"
#include "ms_parser.h"
#include "ms_processor.h"

/*
**  A function that prints shell tag
*/

static void	print_shell_tag(void)
{
	write(1, "\033[32m", ft_strlen("\033[32m")); //output color
	write(1, "minishell$ ", 11);
	write(1, "\033[0m", ft_strlen("\033[0m"));
}

/*
**  A function that gets the command line from input
*/

static char	*get_cmd_line(void)
{
	char	buff[1000];
	char	*cmd_line;
	char	*tmp;
	int		read_bytes;

	cmd_line = ft_strdup("");
	while ((read_bytes = read(0, buff, 999)))
	{
		if (buff[read_bytes - 1] == '\n')
			buff[read_bytes - 1] = '\0';
		tmp = cmd_line;
		cmd_line = ft_strjoin(cmd_line, buff);
		free(tmp);
		if (buff[read_bytes - 1] == '\0')
			break ;
	}
	return (cmd_line);
}

/*
**  A function that frees commands array and command line
*/

static void parser_free(char **cmd_line, t_cmd **cmd_arr)
{
	int 	i;
	int 	j;

	free(*cmd_line);
	*cmd_line = NULL;
	i = 0;
	while (cmd_arr[i])
	{
		free(cmd_arr[i]->cmd);
		cmd_arr[i]->cmd = NULL;
		if (cmd_arr[i]->args != NULL)
		{
			j = 0;
			while (cmd_arr[i]->args[j])
			{
				free(cmd_arr[i]->args[j]);
				++j;
			}
			free(cmd_arr[i]->args);
		}
		cmd_arr[i]->args = NULL;
		free(cmd_arr[i]);
		cmd_arr[i] = NULL;
		++i;
	}
	free(cmd_arr[i]);
	cmd_arr[i] = NULL;
	free(cmd_arr);
}

static void		get_env(const char *env, char **name, char **content)
{
	int		i;
	int		j;

	j = 0;
	while (env[j] != '=')
		++j;
	*name = malloc(sizeof(char) * (j + 1));
	i = 0;
	while (env[i] != '=')
	{
		(*name)[i] = env[i];
		++i;
	}
	(*name)[i] = '\0';
	++i;
	j = i;
	while (env[j] != '\0')
		++j;
	*content = malloc(sizeof(char) * ((j - i) + 1));
	j = 0;
	while (env[i] != '\0')
	{
		(*content)[j] = env[i];
		++i;
		++j;
	}
	(*content)[j] = '\0';
}

/*
**  A function that creates a list from envp
*/

static void		make_env_list(char **envp, t_list **env_list)
{
	int		i;
	char	*name;
	char	*content;
	t_list	*new_lst;

	i = 0;
	get_env(envp[i], &name, &content);
	*env_list = ft_lstnew(name, content);
	++i;
	while (envp[i])
	{
		get_env(envp[i], &name, &content);
		new_lst = ft_lstnew(name, content);
		ft_lstadd_back(env_list, new_lst);
		++i;
	}
}

int				main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_cmd	**cmd_arr;
	t_list	*env_list;

	argc += 0;
	argv += 0;

	g_exit_status = 0;							//set exit status to zero
	make_env_list(envp, &env_list);				//create environment variable list from envp
	while (1)
	{
		print_shell_tag();						//print shell tag
		cmd_line = get_cmd_line();				//read command line and put it to a variable
		cmd_arr = parser(cmd_line);	//send command line to parser (and get commands array)
		if (!cmd_arr)							//if no commands -> continue
		{
			free(cmd_line);
			continue;
		}
		processor(cmd_arr, &env_list);			//execute commands
		parser_free(&cmd_line, cmd_arr);		//free commands array and command line
//		exit(g_exit_status);					//!for testing!
	}
	return (0);
}
