/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:18:59 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 06:56:07 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		select_mode(t_line *line, t_slct *slct_p)
{
	int		key_pressed;
	int		ctr;
	int		tmp;

	ctr = 0;
	tmp = 0;
	select_initiate(line, slct_p);
	while (1337)
	{
		key_pressed = get_key();
		select_cases(key_pressed, slct_p, line);
		if (key_pressed == KEY_CTRLJ)
		{
			apply_copy(slct_p, line, ctr);
			break ;
		}
		if (key_pressed == KEY_CTRLI)
		{
			apply_cut(slct_p, line, ctr, tmp);
			break ;
		}
	}
}

void		paste_slct_item(t_line *line, t_slct *slct_p)
{
	int		size;
	int		i;

	size = ft_strlen(slct_p->slct_cmd);
	i = 0;
	while (i < size)
	{
		insert_char(line, (int)slct_p->slct_cmd[i]);
		i++;
	}
}

void		apply_copy(t_slct *slct_p, t_line *line, int ctr)
{
	if (slct_p->end > slct_p->start)
		while (slct_p->start <= slct_p->end)
		{
			slct_p->slct_cmd[ctr++] = line->cmd[slct_p->start];
			line->cursor = slct_p->start;
			set_curpos(line);
			ft_putchar_fd(line->cmd[slct_p->start], 0);
			slct_p->start++;
		}
	else if (slct_p->end < slct_p->start)
	{
		while (slct_p->end <= slct_p->start)
		{
			slct_p->slct_cmd[ctr++] = line->cmd[slct_p->end];
			line->cursor = slct_p->end;
			set_curpos(line);
			ft_putchar_fd(line->cmd[slct_p->end], 0);
			slct_p->end++;
		}
	}
	slct_p->slct_cmd[ctr] = '\0';
}

void		apply_cut(t_slct *slct_p, t_line *line, int ctr, int tmp)
{
	if (slct_p->end > slct_p->start)
	{
		line->cursor = slct_p->start;
		tmp = slct_p->end - slct_p->start;
		while (tmp-- >= 0)
		{
			slct_p->slct_cmd[ctr++] = line->cmd[slct_p->start];
			delete_char(line, line->cmd[slct_p->start]);
		}
	}
	else if (slct_p->end < slct_p->start)
	{
		line->cursor = slct_p->end;
		tmp = slct_p->start - slct_p->end;
		while (tmp-- >= 0)
		{
			slct_p->slct_cmd[ctr++] = line->cmd[slct_p->end];
			delete_char(line, line->cmd[slct_p->end]);
		}
	}
	slct_p->slct_cmd[ctr] = '\0';
}

void		select_initiate(t_line *line, t_slct *slct_p)
{
	slct_p->start = line->cursor;
	slct_p->end = line->cursor;
	tputs(tgetstr("us", NULL), 1, &my_putchar);
	ft_putchar_fd((int)line->cmd[line->cursor], 0);
	tputs(tgetstr("ue", NULL), 1, &my_putchar);
	set_curpos(line);
}
