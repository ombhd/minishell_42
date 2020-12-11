/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:59:55 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/11 22:59:02 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
// # include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define SIZE				16384
# define CONT				1
# define APPEND				'a'
# define TRUNC				'>'
# define READ				'<'
# define SUCCESS			0
# define PIPE				124
# define S_COLON			59
# define CTRL_D				-3
# define VALID_STX			7
# define RDIN_ERR			2
# define SPLT_ERR			3
# define STX_ERR			1
# define F_NOT_FOUND_ERR	2
# define NOT_VALID_ERR		3
# define CMD_NOT_FOUND_ERR	4
# define OLDPWD_ERR			5
# define HOME_NOT_SET_ERR	6
# define IS_DIRECTORY_ERR	7
# define PERMISSION_ERR		8
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 		1
# endif

typedef struct		s_parser
{
	int				i;
	int				j;
	int				m;
	int				l;
	char			quote_ig;
	char			slash_ig;
	char			*tmp;
}					t_parser;

typedef struct		s_cmd
{
	char			*cmd;
	char			**args;
	char			start;
	char			end;
	char			redir;
	char			is_err;
	char			is_pipe;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_ms
{
	char			*input;
	char			*output;
	char			err;
	char			cmd_err;
	char			*pwd;
	char			*old_pwd;
	char			**tab;
	char			**cmd_tab;
	char			**env;
	char			**p_env;
	pid_t			pid;
	pid_t			*tpid;
	t_cmd			*cmds;
	t_cmd			*head;
	t_cmd			*lst_end;
	int				redir;
	int				pp_count;
	char			is_pipe;
	int				*fds;
	int				status;
	long			ret_status;
	int				j;
	int				ctrl;
	int				backup[3];
}					t_ms;

void				get_input(t_ms *ms);
int					tb_len(char **table);
char				**free_str_table(char **tab);
void				init(t_ms *ms, char step, char **env);
int					parse_total_cmds(t_ms *ms);
void				parse(t_ms *ms);
char				**parse_split(char const *s, char c, t_ms *ms);
void				errex(t_ms *ms, int err);
char				**dup_str_tab(char **arr, char p);
int					skip_while(char *s, char c);
t_cmd				*get_head(t_cmd *cmds, char *err);
void				parse_d(t_ms *ms);
void				new_cmd(t_ms *ms, char del, char **tab);
int					quote_handler(char const *s, int neg);
void				clean_stx_err(t_ms *ms);
void				init_parser(t_parser *p);
void				parse_read_rdr(t_ms *ms, int b, int i, char *s);
void				parse_trunc_rdr(t_ms *ms, int b, int *i, char *s);
void				parse_pipe(t_ms *ms, int b, int i, char *s);
void				parse_scolon(t_ms *ms, int b, int i, char *s);
char				*parse_quote_bslash(char *elem, t_ms *ms);
size_t				len_if(char *s, int nl);
char				*ft_dup_free(char *src, char **to_free);
int					build_line(char **line, char **buff, char **buff_s,\
								char step);
int					get_next_line(int fd, char **line);
void				free_cmds(t_ms *ms);
void				*ft_free(void *mem_ptr);
char				*clean_join(char *s1, char *s2);
void				internal_init(t_ms *ms);
char				*get_p_value(char *val);
int					is_set(char *target, char *set);
char				**rm_empty_str(char **arr);
int					get_env(char **env, char *var);
char				**get_arr(char *value, char ***env, char p);
int					check_exist(char **env, char *arg);
int					cmp_get_pos(char **env, char *var);
char				**rm_arr(char **env, int pos);
void				sort_env(char **env);
char				**add_to_arr(char *value, char ***env, char p);
char				**set_env(char *var, char *value, char ***env, char p);
int					ft_cd(t_ms *ms);
int					ft_env(t_ms *ms);
int					ft_export(t_ms *ms);
int					ft_pwd(t_ms *ms);
int					ft_unset(t_ms *ms);
int					ft_exit(t_ms *ms);
int					ft_echo(t_ms *ms);
int					check_command(t_ms *ms);
void				check_command_help(t_ms *ms);
char				*get_exec_path(t_ms *ms);
void				exec_command(t_ms *ms);
int					is_builtin_sys(char *cmds);
int					valid_arg(char *arg);
int					cmd_error(t_ms *ms, int err, char *cmd, char *arg);
void				save_fds(int *fds);
void				restore_fds(int *fds);
void				ft_redir(t_ms *ms, t_cmd *tmp, t_cmd *cmd);
void				handle_sig(int sig);
int					check_permission(char *path, int mode);
int					cmd_error_help(t_ms *ms);
pid_t				run_child(t_ms *ms, int i);
int					*dup_in_out(t_ms *ms);
int					wait_child(t_ms *ms);
char				*is_path_exe(char **tab, t_ms *ms);
void				manage_cmd(t_ms *ms, int is_built_in);
void				exucte_cmd(t_ms *ms);
t_ms				*exucte_help(t_ms *ms);
void				pipe_fds(t_ms *ms);
int					minishell(char **env, int step);
int					g_ret;

#endif
