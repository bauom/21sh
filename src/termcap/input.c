/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 02:05:00 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/25 03:50:46 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	print_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			ft_putchar_fd(' ', 0);
		else
			ft_putchar_fd(*line, 0);
		line++;
	}
}

void	insert_char(t_line *line, int key)
{
	if (line->length + 1 >= MAX_CMD_LEN)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
			MAX_CMD_LEN - line->cursor - 1);
	line->cmd[line->cursor] = key;
	line->length++;
	line->cursor++;
	tputs(tgetstr("im", NULL), 1, &my_putchar);
	if (key != '\n')
		ft_putchar_fd(key, STDIN_FILENO);
	tputs(tgetstr("ei", NULL), 1, &my_putchar);
}

void	delete_char(t_line *line, int key)
{
	if (key == 127 && !line->cursor)
		return ;
	if (key == 127)
		cursor_to_left(line);
	if (line->cursor == line->length)
		return ;
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
			MAX_CMD_LEN - line->cursor - 1);
	line->length--;
	tputs(tgetstr("cd", NULL), 0, &my_putchar);
	print_line(line->cmd + line->cursor);
	set_curpos(line);
}
