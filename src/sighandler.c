/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:30:01 by melalj            #+#    #+#             */
/*   Updated: 2019/08/01 23:07:40 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == 2)
	{
		ft_putstr("\n\033[1m" ANSI_COLOR_BLUE);
		ft_putstr("21sh");
		ft_putstr(ANSI_COLOR_RED " => " ANSI_COLOR_RESET "\033[0m");
		g_c = 1;
	}
}

void	melalsh_exit(void)
{
	ft_putstr(ANSI_COLOR_BBLACK "x_x < \n" ANSI_COLOR_RESET);
	exit(0);
}

void	prompt_h(t_env *list_env, int state)
{
	char *line;

	if (g_c == 0)
	{
		ft_putstr("\033[1m" ANSI_COLOR_BLUE);
		ft_putstr("21sh");
		if (state == 0)
			ft_putstr(ANSI_COLOR_GREEN " => " ANSI_COLOR_RESET "\033[0m");
		else
			ft_putstr(ANSI_COLOR_RED " => " ANSI_COLOR_RESET "\033[0m");
	}
	signal(SIGINT, sighandler);
}
