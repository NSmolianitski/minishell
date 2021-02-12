/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:32:37 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:33:41 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MS_UTILS_H
# define MINISHELL_MS_UTILS_H

# define NSFD "No such file or directory"
# define CNF "command not found"
# define SES "syntax error near unexpected token ';'"
# define SEP "syntax error near unexpected token '|'"
# define SEN "syntax error near unexpected token 'newline'"
# define NVI "not a valid identifier"
# define SNIP "string not in pwd:"
# define HNS "HOME not set"
# define MLA "\033[31mMULTILINE ATTACK!\nDon't try to break our shell!\033[0m"
# define NAR "numeric argument required"

# include <stddef.h>
# include "libft.h"

int		print_line(char const *line, int fd);
void	print_error(char *error, char *str, int err_type);
int		ms_strcmp(const char *s1, const char *s2);
int		skip_spaces(char const *line, int i);
void	print_list(t_list *lst, int export);
char	*get_var_content(t_list *lst, char *var_name);
int		change_var_content(t_list *lst, char *var_name, char *content);
int		find_var(t_list *lst, char *var_name);
void	*rm_var(t_list **lst, char *var_name);
char	*safe_strjoin(char **str1, const char *str2);
int		ms_strswap(char **str, const char *inject, int start, int len);
char	*ft_strchr_quotes(const char *s, int c);
char	*ms_bs_strchr(const char *s, int c);
int		is_symb_esc(const char *str, int i);
void	double_free(char *s1, char *s2);
char	**ms_split(const char *str, char c);
void	write_ms_err_begin_with_cmd(char *str);
void	write_ms_err_begin_export(char *str);
void	write_ms_err_begin_unset(char *str);
void	write_ms_err_begin_exit(char *str);
void	write_ms_err_begin_cd(char *str);
void	print_shell_tag(void);
void	get_env(const char *env, char **name, char **content);
void	gcl_norm(int flag);

#endif
