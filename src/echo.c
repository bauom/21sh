/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 00:08:01 by melalj            #+#    #+#             */
/*   Updated: 2019/12/29 14:07:06 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		b_echo(char **i_line)
{
	int	i;
	int j;

	i = 0;
	while (i_line[++i])
	{
		j = -1;
		if (!ft_strequ(i_line[i], "-n"))
			while (i_line[i][++j])
					ft_putchar(i_line[i][j]);
		if (i_line[i + 1] && ft_strequ(i_line[i - 1], "-n"))
			ft_putchar(' ');
	}
	if (!ft_strequ(i_line[1], "-n"))
		ft_putchar('\n');
	return (0);
}
