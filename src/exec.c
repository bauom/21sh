/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:41:17 by melalj            #+#    #+#             */
/*   Updated: 2019/08/09 23:12:29 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_handler(t_env **list_env, char **line_ab, t_fds *fds)
{
	int		r;

	pipe(fds->p_fds);
	r = exec_pipe(list_env, line_ab, fds);
	return (r);
}

int		exec_red(t_env **list_env, char **line_ab, t_fds *fds)
{
	char	**buff;
	int		f;
	char	*cmd;
	int		i;

	exec_red_init(line_ab, fds, &cmd, &buff);
	if (!cmd)
		return (1);
	if (ft_strequ(cmd, ""))
	{
		free(cmd);
		return (0);
	}
	f = cmd_s(list_env, line_interpret(*list_env, cmd), fds->w, &(fds->pid));
	i = -1;
	while (buff[++i])
		if (ft_strchr(buff[i], 'o'))
			close(fd_tored(buff[i]));
	free(cmd);
	free_tab(buff);
	fd_reset(fds);
	return (f);
}

void	exec_red_init(char **line_ab, t_fds *fds, char **cmd, char ***buff)
{
	int *o;

	fds->p_fds_tmp[0] = dup_fd(0);
	fds->p_fds_tmp[1] = dup_fd(1);
	if (ft_strchr(line_ab[1], 'h'))
	{
		dup2(fds->o_fds[0], 0);
		if (fds->w == 0)
		{
			dup2(fds->o_fds[1], 1);
			close(fds->o_fds[1]);
		}
	}
	fds->tmp_fds = fd_init();
	*buff = init_red(line_ab, cmd);
	if (fds->w == 0)
	{
		dup2(fds->p_fds_tmp[1], 1);
		close(fds->p_fds_tmp[1]);
	}
}

int		*fd_init(void)
{
	int *o;

	o = (int *)malloc(sizeof(int) * 3);
	o[0] = dup_fd(0);
	o[1] = dup_fd(1);
	o[2] = dup_fd(2);
	return (o);
}

void	fd_reset(t_fds *fds)
{
	dup2(fds->tmp_fds[0], 0);
	close(fds->tmp_fds[0]);
	dup2(fds->tmp_fds[1], 1);
	close(fds->tmp_fds[1]);
	dup2(fds->tmp_fds[2], 2);
	close(fds->tmp_fds[2]);
	close(fds->p_fds_tmp[1]);
	close(fds->p_fds_tmp[0]);
	free(fds->tmp_fds);
}

int		exec_pipe(t_env **list_env, char **line_ab, t_fds *fds)
{
	int r;

	r = 1;
	dup2(fds->p_fds[1], 1);
	close(fds->p_fds[1]);
	fds->w = 0;
	r = exec_red(list_env, line_ab, fds);
	dup2(fds->p_fds[0], 0);
	close(fds->p_fds[0]);
	return (r);
}

int		exec_reset(t_env **list_env, char **line_ab, t_fds *fds, int r)
{
	char	*tmp;

	dup2(fds->o_fds[1], 1);
	close(fds->o_fds[1]);
	fds->w = 1;
	r = exec_red(list_env, line_ab, fds);
	dup2(fds->o_fds[2], 2);
	close(fds->o_fds[2]);
	dup2(fds->o_fds[0], 0);
	close(fds->o_fds[0]);
	return (r > 9 ? r - 10 : r);
}
