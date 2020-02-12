/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:49:44 by melalj            #+#    #+#             */
/*   Updated: 2019/07/30 14:36:20 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		refresh_up(t_env **list_env)
{
	int		r;
	char	**env;
	char	**cmd;
	char	*line;

	if ((r = melalsh_exec(list_env, ft_strdup("make re")) != 0))
	{
		ft_putendl_fd("update cannot be done", 2);
		return (1);
	}
	env = env_tab(*list_env);
	cmd = ft_strsplit("./21sh", ' ');
	if (execve(cmd[0], cmd, env) != 0)
		ft_putendl_fd("can't run the new version", 2);
	return (0);
}
