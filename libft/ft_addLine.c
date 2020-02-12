/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addLine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 10:56:28 by melalj            #+#    #+#             */
/*   Updated: 2019/12/27 08:30:46 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_line(char **line, char *to_add)
{
	char *tmp;

	if (!to_add)
		return ;
	if (!line || !*line)
		*line = ft_strdup("");
	tmp = ft_strjoin(*line, to_add);
	free(*line);
	*line = tmp;
}
