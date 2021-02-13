/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:32:47 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:32:48 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MS_PARSER_H
# define MINISHELL_MS_PARSER_H
# include "ms_utils.h"
# include "libft.h"

typedef struct	s_cmd
{
	char		*cmd;
	char		**args;
	char		end;
}				t_cmd;

t_cmd			**parser(const char *cmd_line);
void			swap_env(char **cmd, t_list *env_list);
char			*parse_qoutes(char *str, t_list *env_list);
char			*ms_strmultichr(const char *s, const char *symbols);
int				get_word(const char *cmd_line, char **cmd, int i);
int				count_args(const char *cmd_line, int i);
int				get_args(const char *cmd_line, char ***args, int i);
void			parse_cmd(const char *cmd_line, int *i, t_cmd *cmd);
int				count_cmds(const char *cmd_line);
void			count_cmds_err_check(const char *cmd_line, int i);
void			free_arr(char **tmp);
char			*get_exit_status_env(char *str);
char			*parse_env(char *str);
char			*parse_backslash(char *str, int *offset);
void			join_result(char **tmp2, char **result);
int				proccess_simple_text(char *str, char **result);
void			check_redir_quotes(int *quotes, int i, const char *cmd_line);
int				print_redir_err(void);
int				check_redir_parser_norm(int *flag, const char
*cmd_line, int *i);

#endif
