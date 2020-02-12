/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 04:41:38 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/24 07:33:30 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		quote_handler(t_line *line, int key_pressed, int quote)
{
	while (1337)
	{
		ft_getwinsz(&line->winsz);
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		line->start.row++;
		line->start.col = 0;
		line->cursor = 0;
		set_curpos(line);
		get_cursor_start_pos(line);
		ft_putstr_fd("dquote> ", 0);
		line->cursor = line->length;
		if ((quote % 2) != 0 && key_pressed == '\n')
			insert_char(line, '\n');
		if (key_pressed == '\n' || (key_pressed == '\n' && ((quote % 2) == 0)))
			break ;
	}
}

int			quote_checker(t_line *line, int quote)
{
	size_t	i;

	i = 0;
	while (i < line->length)
		if (line->cmd[i++] == '\"')
			quote++;
	return (quote);
}
