/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:33:20 by melalj            #+#    #+#             */
/*   Updated: 2019/08/08 12:10:25 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_error(char **line_ab)
{
	int i;
	int c;

	i = -1;
	// printf("line \x1b[31m|\x1b[0m%s\x1b[31m|\x1b[0m\n", line_ab[0]);
	// printf("ab \x1b[31m|\x1b[0m%s\x1b[31m|\x1b[0m\n", line_ab[1]);
	while (line_ab[1][++i])
	{
		if (line_ab[1][i] == 'f' && line_ab[0][i] == '&' && (line_ab[1][i - 1] == '&' || (line_ab[1][i + 1] && line_ab[1][i + 2] == '&')))
		{
			ft_putendl("ambiguous redirect");
			return (1);
		}
		if (!ft_strchr("c sfe", line_ab[1][i]))
		{
			c = skip_whitespaces(&(line_ab[1][i]));
			if (!ft_strchr("csf", line_ab[1][i + c]) || !line_ab[1][i + c])
			{
				if (line_ab[1][i] == 'r' && line_ab[1][i + 1] == '&')
					continue ;
				ft_putstr("parse error near ");
				if (!line_ab[1][i + c])
					ft_putstr("\\n");
				else
					ft_putchar(line_ab[0][i + c]);
				ft_putchar('\n');
				return (1);
			}
		}
	}
	free(line_ab[0]);
	free(line_ab[1]);
	free(line_ab);
	return (0);
}

int		skip_whitespaces(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[++i] && (s[i] == ' ' || s[i] == '\t'))
		;
	return (i);
}
