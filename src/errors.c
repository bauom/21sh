/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:45:36 by melalj            #+#    #+#             */
/*   Updated: 2019/12/29 13:52:11 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_found(char *cmd, int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" not found", 2);
	}
	else if (mode == 1)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(1);
	}
}

char	access_check(char *path)
{
	if (access(path, F_OK))
		return ('f');
	else if (access(path, R_OK))
		return ('r');
	else if (access(path, X_OK))
		return ('x');
	else if (access(path, W_OK))
		return ('w');
	return (0);
}

int		access_error(char *cmd, char *path, char mode)
{
	if (mode == 'f')
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		return (0);
	}
	else if (mode == 'x')
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied: ", 2);
		ft_putendl_fd(path, 2);
		return (0);
	}
	return (1);
}
