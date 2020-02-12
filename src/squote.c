/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:36:47 by melalj            #+#    #+#             */
/*   Updated: 2019/07/28 00:49:19 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	squote(char **line)
{
	int		n_q;
	int		i;
	char	*temp;
	char	*temp_l;

	if (!line)
		return ;
	n_q = 0;
	i = -1;
	while ((*line)[++i])
	{
		if (n_q == 0 && (*line)[i] == '\'' && (*line)[i - 1] != '\\')
			n_q++;
		else if ((*line)[i] == '\'')
			n_q++;
	}
	if (n_q % 2)
	{
		ft_putstr("quote> ");
		get_next_line(1, &temp);
		temp_l = ft_joinwith(*line, temp, "\n");
		free(*line);
		free(temp);
		*line = temp_l;
		squote(line);
	}
}
