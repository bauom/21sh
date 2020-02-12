/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:08:32 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 06:54:06 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		goto_next_word(t_line *line)
{
	while (line->cmd[line->cursor] != ' ' && line->cursor != line->length)
		cursor_to_right(line);
	while (line->cmd[line->cursor] == ' ' && line->cursor != line->length)
		cursor_to_right(line);
}

void		goto_prev_word(t_line *line)
{
	if (line->cursor && line->cmd[line->cursor - 1] == ' ')
		cursor_to_left(line);
	while (line->cmd[line->cursor] == ' ' && line->cursor)
		cursor_to_left(line);
	while (line->cmd[line->cursor] != ' ' && line->cursor)
		cursor_to_left(line);
	if (line->cursor)
		cursor_to_right(line);
}

void		goto_next_line(t_line *line)
{
	line->cursor = line->cursor + line->winsz.col > line->length ?
		line->length : line->cursor + line->winsz.col;
	set_curpos(line);
}

void		goto_prev_line(t_line *line)
{
	line->cursor = line->cursor < line->winsz.col ? 0 : line->cursor -
		line->winsz.col;
	set_curpos(line);
}

void		ctrl_commands(int key_pressed, t_line *line, t_slct *slct_p)
{
	if (key_pressed == 19)
		goto_next_word(line);
	if (key_pressed == 1)
		goto_prev_word(line);
	if (key_pressed == 5)
		goto_next_line(line);
	if (key_pressed == 23)
		goto_prev_line(line);
	if (key_pressed == KEY_CTRLL)
	{
		if (line->start.row != 1)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
					, 1, &my_putchar);
			line->start.row = 1;
			set_curpos(line);
		}
	}
	if (key_pressed == KEY_CTRLK)
		select_mode(line, slct_p);
	if (key_pressed == KEY_CTRLH)
		paste_slct_item(line, slct_p);
}
