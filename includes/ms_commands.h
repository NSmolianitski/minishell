#ifndef MINISHELL_MS_COMMANDS_H
#define MINISHELL_MS_COMMANDS_H

int		print_pwd(void);
int		ms_echo(char **args);
int		ms_cd(char *str);
void	ms_env(t_list *env_list);

#endif
