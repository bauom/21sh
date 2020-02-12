/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:49:57 by melalj            #+#    #+#             */
/*   Updated: 2019/06/30 06:02:07 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bs(char **line)
{
	int i;
	char *tmp;
	int len;
	
	if (!line || !*line)
		return ;
	i = -1;
	len = 0;
	while((*line)[++i])
		if ((*line)[i] != '\n' || (*line)[i - 1] != '\\')
			len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
		len = 0;
		i = -1;
		while((*line)[++i])
		{
			if((*line)[i] != '\n' || (*line)[i - 1] != '\\')
				tmp[len++] = (*line)[i];
		}
	tmp[len] = '\0';
	free(*line);
	*line = tmp;
}
