/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <mouadelalj@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:01:21 by melalj            #+#    #+#             */
/*   Updated: 2019/08/03 00:04:57 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dup_fd(int fd)
{
	static int i = 100;

	dup2(fd, i);
	i++;
	return (i - 1);
}

int		check_fd(char *fd)
{
	char	*tmp;
	int		fd_c;

	tmp = ft_strdup("/dev/fd/");
	add_line(&tmp, fd);
	if ((fd_c = open("/dev/fd/3", O_RDWR)) == -1)
	{
		ft_putendl_fd("21sh : : bad file descriptor", 2);
		return (1);
	}
	close(fd_c);
	return (0);
}
