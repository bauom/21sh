/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 21:59:50 by melalj            #+#    #+#             */
/*   Updated: 2019/12/29 16:47:13 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "src/termcap/line_editing.h"
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <locale.h>
# include <curses.h>
# include <errno.h>
# include <term.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_BRED     "\x1b[91m"
# define ANSI_COLOR_BGREEN   "\x1b[92m"
# define ANSI_COLOR_BYELLOW  "\x1b[93m"
# define ANSI_COLOR_BBLUE    "\x1b[94m"
# define ANSI_COLOR_BMAGENTA "\x1b[95m"
# define ANSI_COLOR_BCYAN    "\x1b[96m"
# define ANSI_COLOR_BBLACK    "\x1b[90m"
# define ANSI_COLOR_RESET   "\x1b[0m"


typedef struct		s_alias
{
	char			*name;
	struct s_alias	*next;
}					t_alias;

static	t_alias		**list_alias;
typedef struct		s_env
{
	char			*name;
	int				mode;
	struct s_env	*next;
}					t_env;

int g_c;

typedef struct		s_cmd
{
	char			*cmd;
	int				nrp;
	int				fd;
	char			type;
}					t_cmd;

typedef struct		s_rcmd
{
	pid_t			pid;
	int				r;
}					t_rcmd;

typedef struct		s_fds
{
	int				p_fds[2];
	int				o_fds[3];
	int				pid;
	int				*tmp_fds;
	int				p_fds_tmp[2];
	int				w;
}					t_fds;

int					melalsh_loop(t_env **list_env);
void				sighandler(int signum);
void				melalsh_exit(void);
int					melalsh_exec(t_env **list_env, char *cmd);
void				not_found(char *cmd, int mode);
char				access_check(char *path);
int					access_error(char *cmd, char *path, char mode);
/*
**	ENV functions
*/
int					b_echo(char **i_line);
t_env				*get_env(char **env);
t_env				*new_var(char *var);
void				add_var(t_env **lst_var, char *var);
void				print_env(t_env *list_env);
int					buildin_check(t_env **list_env, char **i_line);
char				**env_tab(t_env *list_env);
char				*f_which(t_env *list_env, char **i_line, int mode);
int					ft_envlen(t_env **alst);
char				*ft_valget(t_env *alst, char *var_name);
int					f_env(t_env *list_env);
t_env				*ft_varget(t_env *alst, char *var_name);
char				*ft_joinwith(char *dir, char *file, char *joint);
int					f_setenv(t_env **env, char **i_line, int mode, char *line);
int					f_unsetenv(t_env **list_env, char **i_line, int mode);
void				del_var(t_env **list_env, t_env *to_del);
int					f_cd(t_env **list_env, char **i_line);
int					free_env(t_env **env);
char				**line_interpret(t_env *env, char *line);
char				**ft_strssplit(char const *s, char *c);
int					free_sl(void *to_free);
int					free_tab(char **to_free);
char				**line_interpret_helper(t_env *env, char **i, char *temp);
void				squote(char **line);
void				dquote(char **line);
void				bs(char **line);
void				quote(char **line);
void				quote_backslash(char **line);
char				ft_qc(char *line, char qc);
char				**ead_line(char **line);
/*
** test 
*/
int		cmd_s(t_env **list_env, char ** b_cmd, int w, int *pid);
int		cmd_pp(t_env **list_env, char ** b_cmd);
t_cmd	*cmd_p(char **line);
int		ft_sc(char *line, char *to_search);
int		cmd_c(t_env	**list_env, char **cmd);
char	*ft_strschr(char *line, char *to_search);
void	ft_printt(char **tt);
void	prompt_h(t_env *list_env, int state);
int		refresh_up(t_env **list_env);
int     cmd_o(t_env **list_env, char *cmd, char **out_put);
int		exec_pipe(t_env **list_env, char **line_ab, t_fds *fds);
int		exec_red(t_env **list_env, char **line_ab, t_fds *pid);
int     exec_reset(t_env **list_env, char **line_ab, t_fds *fds, int r);
int		exec_handler(t_env **list_env, char **line_ab, t_fds *fds);
char	**parser_ab(char *line);
char	***split_ab(char **line, char c);
t_cmd	*p_cmd(char **line, int *i);
int		token_p(char **line_ab, t_cmd **cmd, int *i);
char	*r_token(t_list **lst_token, char **redi);
int		r_r(t_cmd *token, char **line);
void	add_line(char **line, char *to_add);
int		ft_isnumber(char *s);
int		*fd_init();
void	fd_reset(t_fds *fds);
void	d_trim(char ****trim);
char	**init_red(char **line_ab, char **cmd);
char    *open_red(t_cmd *token, char **line, char *file, int *i);
int		r_a(t_cmd *token, char **line, int *i);
void	in_r(t_cmd *token, char **line, int *i);
int		access_c(char *file, int per, int *error);
void	h_doc(char *eof);
char	**expand_ab(t_env **list_env, char *cmd);
int		parse_error(char **line_ab);
int		skip_whitespaces(char *s);
void	kill_pipes(char *pids);
void    exec_red_init(char **line_ab, t_fds *fds, char **cmd, char ***buff);
int		fd_tored(char *buff);
int		dup_fd(int fd);
int		check_fd(char *fd);
/* working on type */ 
char	*type_builtin(t_env *list_env, char **i_line, int mode);
void	type_flags(char **i_line, int j, char **splited_path, char *val_path);
int		if_keyword(char **i_line, int j);
#endif
