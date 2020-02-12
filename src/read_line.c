/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:30:28 by melalj            #+#    #+#             */
/*   Updated: 2019/12/27 10:52:22 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **ead_line(char **line)
{
	char	**s_line;

	 if (!(*line = line_editing()))
	 	return (NULL);
//	get_next_line(0, line);
	// quote(line);
	// quote_backslash(line);
	// bs(line);
	s_line = ft_strssplit(*line, ";");
	return (s_line);
}
