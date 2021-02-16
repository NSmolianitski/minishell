/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:32:29 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:32:31 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int				g_echo;
void			processor(t_cmd	**cmd_arr, t_list **env_list);
void			handle_redirects(t_cmd *cmd);
void			sig_int(int sig);
void			sig_quit(int sig);
char			*get_path(char *cmd, t_list **env_list);
int				try_external_cmd(t_cmd *cmd, t_list **env_list);
void			free_strs_arr(char ***args);
void			prepare_args(t_cmd *cmd, char ***args);
void			list_to_arr(t_list *env_list, char ***envp);
t_coords		get_quotes_coords(char **str, int i);
int				check_multiline(char *str);
char			*prepare_quotes_str(char *str, t_list *env_list,
						t_coords coords, int i);
void			check_multiword_env(t_cmd *cmd);
int				swap_quotes(char **str, t_list *env_list,
						t_cmd *cmd, int is_cmd);
void			sq_norm(char *tmp, char *tmp2, char **str, int i);
void			sq_norm2(char **tmp2, char **str);
int				sq_norm4(char **tmp, char **tmp2, char **str);
void			sq_norm5(char **tmp, char **str, char **tmp2);
int				sq_norm6(int i, char **str, t_list *env_list, char *tmp);
void			handle_bslash(char **str);
int				check_quotes(t_cmd *cmd, t_list *env_list);
void			save_restore_fds(int *in, int *out, int flag);
int				check_cmd(t_cmd *cmd, t_list **env_list);
void			execute_cmd(t_cmd *cmd, t_list **env_list);
void			rm_redir_in(t_cmd *cmd, int index);
void			rm_redir_append(t_cmd *cmd, int index);
void			rm_redir_out(t_cmd *cmd, int index);
void			check_bslash(char *tmp, int *i, char **str, int *str_diff);
int				check_bslash2(char **str, int i);
int				redir_in(int *temp_fd, char *file, t_cmd *cmd, int index);
int				redir_err_norm(int *temp_fd, char *file, t_cmd *cmd, int index);
void			redir_stream_one(int temp_fd, t_cmd *cmd, int index);
int				echo_empty_check(char **str);
void			check_empty_args(t_cmd *cmd);

#endif
