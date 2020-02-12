/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 07:13:44 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 06:56:50 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		select_cases(int key_pressed, t_slct *slct_p, t_line *line)
{
	if (key_pressed == KEY_RIGHT && (slct_p->end < slct_p->start)
			&& (slct_p->end < line->length - 1))
		apply_select_0(slct_p, line, 0);
	else if (key_pressed == KEY_RIGHT && (slct_p->end < line->length - 1))
		apply_select_1(slct_p, line, 0);
	if (key_pressed == KEY_LEFT && (slct_p->end > slct_p->start)
			&& (slct_p->end > 0))
		apply_select_0(slct_p, line, 1);
	else if (key_pressed == KEY_LEFT && (slct_p->end > 0))
		apply_select_1(slct_p, line, 1);
}

void		apply_select_1(t_slct *slct_p, t_line *line, int mode)
{
	if (mode == 0)
	{
		cursor_to_right(line);
		tputs(tgetstr("us", NULL), 1, &my_putchar);
		ft_putchar_fd(line->cmd[line->cursor], 0);
		tputs(tgetstr("ue", NULL), 1, &my_putchar);
		set_curpos(line);
		slct_p->end++;
	}
	else if (mode == 1)
	{
		cursor_to_left(line);
		tputs(tgetstr("us", NULL), 1, &my_putchar);
		ft_putchar_fd(line->cmd[line->cursor], 0);
		tputs(tgetstr("ue", NULL), 1, &my_putchar);
		set_curpos(line);
		slct_p->end--;
	}
}

void		apply_select_0(t_slct *slct_p, t_line *line, int mode)
{
	if (mode == 0)
	{
		slct_p->end++;
		ft_putchar_fd(line->cmd[line->cursor], 0);
		cursor_to_right(line);
	}
	else if (mode == 1)
	{
		slct_p->end--;
		ft_putchar_fd(line->cmd[line->cursor], 0);
		cursor_to_left(line);
	}
}
