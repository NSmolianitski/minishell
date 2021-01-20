#ifndef MINISHELL_MS_UTILS_H
# define MINISHELL_MS_UTILS_H

# define NSFD "No such file or directory"
# define CNF "command not found"

int		print_line(char const *line, int fd);
void	print_error(char *error, char *str, int err_type);
int		ms_strcmp(const char *s1, const char *s2);

# endif
