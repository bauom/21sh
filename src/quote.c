/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 01:25:50 by melalj            #+#    #+#             */
/*   Updated: 2019/07/30 05:32:18 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	quote_prompt(char **line, char sq)
{
	char *temp;
	char *temp_l;

	if (sq != 'n')
	{
		if (sq == 'd')
			ft_putstr("dquote> ");
		else if (sq == 's')
			ft_putstr("quote> ");
		/*if (get_next_line(0, &temp) == 0)
			return ;*/
//		line_editing(&temp);
		temp_l = ft_joinwith(*line, temp, "\n");
		free(*line);
		free(temp);
		*line = temp_l;
		quote(line);
	}
}

void quote_backslash(char **line)
{
	char *temp;
	int i;
	int j;

	i = -1;
	j = 0;
	while((*line)[++i])
	{
		if ((*line)[i] == '\\' && ((*line)[i + 1] == '\'' || (*line)[i + 1] == '\"'))
			continue ;
		j++;
	}
	if (j != 0)
	{
		temp = (char *)malloc(sizeof(char) * (j + 1));
		i = -1;
		j = -1;
		while((*line)[++i])
		{
			if ((*line)[i] == '\\' && ((*line)[i + 1] == '\'' || (*line)[i + 1] == '\"'))
				continue ;
			temp[++j] = (*line)[i];
		}
		temp[++j] = '\0';
		free(*line);
		*line = temp;
	}
}

void		quote(char **line)
{
	int		i;
	char	sq;

	i = -1;
	sq = 'n';
	while ((*line)[++i])
		sq = ft_qc((*line) + i, sq);
	quote_prompt(line, sq);
}

char		ft_qc(char *line, char qc)
{
	if (*line == '\"' && qc == 'n' && *(line - 1) != '\\')
		qc = 'd';
	else if (*line == '\'' && qc == 'n' && *(line - 1) != '\\')
		qc = 's';
	else if (*line == '\"' && qc == 'd' && *(line - 1) != '\\')
		qc = 'n';
	else if (*line == '\'' && qc == 's')
		qc = 'n';
	return (qc);
}
