/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   melalsh_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:08:55 by melalj            #+#    #+#             */
/*   Updated: 2019/12/28 10:36:26 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		melalsh_loop(t_env **list_env)
{
	int		state;
	char	*line;
	char	**i_line;
	char	**cmd;
	int		i;

	state = 0;
	while (1)
	{
		prompt_h(*list_env, state);
		if (!(cmd = ead_line(&line)))
			break ;
		if (parse_error(parser_ab(line)) && (state = 1) && free_sl(line))
			continue ;
		free(line);
		i_line = NULL;
		g_c = 0;
		i = -1;
		while (cmd[++i])
		{
			line = ft_strtrim(cmd[i]);
			if (ft_strnstr(line, "exit", 4)
				&& (line[4] == ' ' || line[4] == '\0'))
				melalsh_exit();
			state = melalsh_exec(list_env, line);
			free(line);
		}
		free_tab(cmd);
	}
	free(line);
	return (1);
}

int		melalsh_exec(t_env **list_env, char *cmd)
{
	t_list	*lst;
	int		r;
	char	**ab;
	t_fds	pid;

	lst = NULL;
	if (!(ab = expand_ab(list_env, cmd)))
		return (1);
	if (!ab[0] || !ab[1])
		return (0);
	pid.w = 1;
//	printf("str : |%s|\n", ab[0]);
//	printf("ab : |%s|\n", ab[1]);
	if (!ft_strschr(ab[1], "pra"))
	{
		r = exec_red(list_env, ab, &pid);
	}
	else
		r = cmd_c(list_env, ab);
	free(ab[0]);
	free(ab[1]);
	free(ab);
	return (r);
}
