#ifndef MINISHELL_MS_COMMANDS_H
#define MINISHELL_MS_COMMANDS_H

int		print_pwd(void);
int		ms_echo(char **args);
int 	ms_cd(char **args, t_list *env_list);
void	ms_env(t_list *env_list);
void	ms_export(t_cmd *cmd, t_list **env_list);
void	ms_unset(t_cmd *cmd, t_list **env_list);

#endif
