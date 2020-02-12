/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:48:48 by melalj            #+#    #+#             */
/*   Updated: 2019/12/28 15:14:28 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     cmd_s(t_env **list_env, char **i_line, int w, int *pid)
{
	pid_t   father;
	char    *exec;
	char    **f;
	int     i;

	if (((i = buildin_check(list_env, i_line)) != -1))
		return (i);
	father = fork();
	if (father == 0)
	{
		exec = ft_strjoin("which ", i_line[0]);
		f = ft_strssplit(exec, " \t");
		free_sl(exec);
		exec = NULL;
		if(*i_line[0] != '/' && *i_line[0] != '.'
				&& (exec = f_which(*list_env, f, 1)) == NULL)
			not_found(i_line[0], 1);
		exec = (exec == NULL) ? i_line[0] : exec;
		f = env_tab(*list_env);
		if (execve(exec, i_line, f) != 0)
			not_found(exec, 1);
	}
	else if (w)
		waitpid(father, &i, 0);
	*pid = father;
	free_tab(i_line);
	return (i);
}

int     cmd_c(t_env **list_env, char **cmd)
{
	t_fds	fds;
	char	**cmd_ab;
	char	***split_p;
	int     f;
	int		i;
	char	*pids;

	fds.o_fds[0] = dup_fd(0);
	fds.o_fds[1] = dup_fd(1);
	fds.o_fds[2] = dup_fd(2);
	split_p = split_ab(cmd , '|');
	d_trim(&split_p);
	f = 0;
	i = 0;
	pids = NULL;
	while (split_p[i + 1])
	{
		f = exec_handler(list_env, split_p[i], &fds);
		add_line(&pids, ft_itoa(fds.pid));
		add_line(&pids, ";");
		i++;
	}
	f = exec_reset(list_env, split_p[i], &fds, f);
	i = -1;
	while (split_p[++i])
		free_tab(split_p[i]);
	free(split_p);
	kill_pipes(pids);
	return (f);
}

void	kill_pipes(char *pids)
{
	char	**tmp;
	int		i;

	if (!pids)
		return ;
	tmp = ft_strsplit(pids, ';');
	i = -1;
	while (tmp[++i])
		kill(ft_atoi(tmp[i]), SIGKILL);
	free_tab(tmp);
}

char	**expand_ab(t_env **list_env, char *cmd)
{
	char	**tmp;
	int		i;
	char	*tmp_l;
	char	*tmp_f;
	char	**line_ab;

	line_ab = (char **)malloc(sizeof(char *) * 2);
	tmp = parser_ab(cmd);
	i = -1;
	tmp_l = NULL;
	line_ab[0] = NULL;
	line_ab[1] = NULL;
	while (tmp[1][++i]) {
		if (tmp[1][i] == 'e') {
			if (tmp[0][i] == '~' && ++i) {
				tmp_f = ft_valget(*list_env, "HOME");
				add_line(&(line_ab[0]), tmp_f);
				tmp_l = ft_strfill('c', ft_strlen(tmp_f));
				free(tmp_f);
				add_line(&(line_ab[1]), tmp_l);
				free(tmp_l);
			} else {
				while (tmp[1][++i] && (ft_isalnum(tmp[0][i])
									   || tmp[0][i] == '_'))
					ft_chrappend(&tmp_l, tmp[0][i], 1);
				tmp_f = ft_valget(*list_env, tmp_l);
				free(tmp_l);
				add_line(&(line_ab[0]), tmp_f);
				tmp_l = ft_strfill('c', ft_strlen(tmp_f));
				free(tmp_f);
				add_line(&(line_ab[1]), tmp_l);
				free(tmp_l);
			}
		}
		tmp_f = ft_chrappend(&(line_ab[0]), tmp[0][i], 0);
		free(line_ab[0]);
		line_ab[0] = ft_strdup(tmp_f);
		free(tmp_f);
		tmp_f = NULL;
		tmp_l = ft_chrappend(&(line_ab[1]), tmp[1][i], 0);
		free(line_ab[1]);
		line_ab[1] = ft_strdup(tmp_l);
		free(tmp_l);
		tmp_l = NULL;
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (line_ab);
}

void	d_trim(char	****to_trim)
{
	int		i;
	int		j;
	char	*tmp;
	i = -1;
	while ((*to_trim)[++i])
	{
		j = -1;
		while ((*to_trim)[i][++j])
		{
			tmp = ft_strtrim((*to_trim)[i][j]);
			free((*to_trim)[i][j]);
			(*to_trim)[i][j] = tmp;
		}
	}
}
