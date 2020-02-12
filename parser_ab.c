/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:41:45 by melalj            #+#    #+#             */
/*   Updated: 2019/08/08 09:50:47 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parser_ab(char *line)
{
	char	**line_ab;
	int		i;
	int		j;
	int		d;

	i = ft_strlen(line);
	line_ab = (char **)malloc(sizeof(char *) * 2);
	line_ab[0] = ft_strnew(i);
	line_ab[1] = ft_strnew(i);
	i = 0;
	j = 0;
	d = 0;
	while (line[i])
	{
		if (!d && line[i] == ';')
			line_ab[1][j] = ';';
		else if (line[i] == ' ' || line[i] == '\t')
		{
			line_ab[1][j] = (!d) ? ' ' : 's';
		}
		else if (d != '\'' && line[i] == '\\')
		{
			i++;
			if (line[i + 1] == '\n' && i++)
				continue ;
			line_ab[1][j] = 'c';
		}
		else if (line[i] == '\"' && (!d || d == '\"'))
		{
			d = (d == '\"') ? 0 : '\"';
			i++;
			continue;
		}
		else if (line[i] == '\'' && (!d || d == '\''))
		{
			d = (d == '\'') ? 0 : '\'';
			i++;
			continue;
		}
		else if (!d && line[i] == '<')
		{
			if (line[i - 2] && line[i - 2] == ' ')
				if (line[i - 1] && (ft_isdigit(line[i - 1]) || line[i - 1] == '&'))
					line_ab[1][j - 1] = 'f';
			if (line[i + 1] == '<' && (i += 2) && (line_ab[0][j] = '<'))
			{
				line_ab[1][j++] = 'h';
				continue;
			}
			else
				line_ab[1][j] = 'i';
		}
		else if (!d && line[i] == '>')
		{
			if (line[i - 2] && line[i - 2] == ' ')
				if (line[i - 1] && (ft_isdigit(line[i - 1]) || line[i - 1] == '&'))
					line_ab[1][j - 1] = 'f';
			if (line[i + 1] == '>' && (i += 2) && (line_ab[0][j] = '>'))
			{
				line_ab[1][j++] = 'a';
				continue;
			}
			else
				line_ab[1][j] = 'r';
		}
		else if (!d && line[i] == '&')
			line_ab[1][j] = '&';
		else if (!d && line[i] == '|')
			line_ab[1][j] = 'p';
		else if (d != '\'' && line[i] == '$')
			line_ab[1][j] = (ft_isalnum(line[i + 1]) || line[i + 1] == '_') ? 'e' :'c';
		else if (d != '\'' && line[i] == '~' && ft_strchr("/", line[i + 1]))
				line_ab[1][j] = ft_iswspace(line[i - 1]) || line[i - 1] < 1 ? 'e' : 'c';
		else
			line_ab[1][j] = 'c';
		line_ab[0][j] = line[i];
		i++;
		j++;
	}
	return (line_ab);
}