/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:54:33 by melalj            #+#    #+#             */
/*   Updated: 2019/06/25 21:50:13 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dquote(char **line)
{
	int n_q;
	int i;
	char *temp;
	char *temp_l;

	if (!line)
		return ;
	n_q = 0;
	i = -1;
	while ((*line)[++i])
		if ((*line)[i] == '"' && (*line)[i - 1] != '\\')
			n_q++;
	if (n_q % 2)
	{
		ft_putstr("dquote> ");
		get_next_line(1, &temp);
		temp_l = ft_joinwith(*line, temp, "\n");
		free(*line);
		free(temp);
		*line = temp_l;
		dquote(line);
	}
}
