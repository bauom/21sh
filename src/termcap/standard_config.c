/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:46:16 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 07:03:41 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

struct termios	saved_tattr;

void	default_term_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_tattr);
}

void	raw_term_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	saved_tattr = tattr;
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_iflag &= ~(IXON);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
	tgetent(NULL, getenv("TERM"));
}

void	loop_initiate(int key_pressed, t_line *line)
{
	ft_getwinsz(&line->winsz);
	if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
		line->start.row--;
	match_move(key_pressed, line);
	match_hist(key_pressed, line);
}

void	standard_commands(int key_pressed, t_line *line)
{
	if (key_pressed > 31 && key_pressed < 127)
		insert_char(line, key_pressed);
	if (key_pressed == KEY_DC || key_pressed == 127)
		delete_char(line, key_pressed);
}
