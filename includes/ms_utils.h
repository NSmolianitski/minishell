#ifndef MINISHELL_MS_UTILS_H
# define MINISHELL_MS_UTILS_H

# define NSFD "No such file or directory"
# define CNF "command not found"
# define SES "syntax error near unexpected token ';'"
# define SEP "syntax error near unexpected token '|'"

# include <stddef.h>
# include "libft.h"

int		print_line(char const *line, int fd);
void	print_error(char *error, char *str, int err_type);
int		ms_strcmp(const char *s1, const char *s2);
int		skip_spaces(char const *line, int i);
size_t	ms_strlcpy(char *dst, const char *src, size_t dstsize, size_t start);
void	print_list(t_list *lst, int export);
char	*get_var_content(t_list *lst, char *var_name);
int		find_var(t_list *lst, char *var_name);
void	*rm_var(t_list **lst, char *var_name);

# endif
