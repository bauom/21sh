/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 23:14:22 by melalj            #+#    #+#             */
/*   Updated: 2019/07/11 17:26:20 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_p(char **line)
{
	t_cmd	*cmd;
	char	*stock;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	stock = ft_strschr(*line, "|");
	cmd->nrp = ft_sc(*line, "|");
	stock = ft_strdup(stock ? (stock + (cmd->nrp > 0 ? 1 : 2)) : stock);
	free(*line);
	*line = ft_strndup(*line, ft_strlen(*line) -
		(!stock ? 0 : ft_strlen(stock) + (cmd->nrp > 0 ? 1 : 2)));
	cmd->cmd = ft_strtrim(*line);
	free(*line);
	*line = stock;
	return (cmd);
}

int    ft_sc(char *line, char *to_search)
{
	char *s;

	if (!line)
		return (0);
	while (*line)
	{
		s = to_search;
		while(*s)
		{
			if(*line == *s)
				return (*s);
			s++;
		}
		line++;
	}
	return (0);
}

char    *ft_strschr(char *line, char *to_search)
{
	char *s;

	if(!line)
		return (NULL);
	while (*line)
	{
		s = to_search;
		while(*s)
		{
			if(*line == *s)
				return (line);
			s++;
		}
		line++;
	}
	return (NULL);
}
