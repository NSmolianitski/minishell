#ifndef MINISHELL_MS_PROCESSOR_H
# define MINISHELL_MS_PROCESSOR_H

# include "ms_parser.h"
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>

typedef struct	s_coords
{
	int			start;
	int			end;
	int			type;
}				t_coords;

int				g_exit_status;
int				g_signal_flag;
void			processor(t_cmd	**cmd_arr, t_list **env_list);
void			handle_redirects(t_cmd *cmd);
void			sig_int(int sig);
void			sig_quit(int sig);
void			print_shell_tag(void);
char			*get_path(char *cmd, t_list **env_list);
#endif
