/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:17:44 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 07:03:20 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void				get_cursor_start_pos(t_line *line)
{
	char			answer[20];
	int				i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void				match_move(int key_pressed, t_line *line)
{
	int						i;

	i = 0;
	static struct s_keymove	keymove[4] = {
		{KEY_RIGHT, &cursor_to_right},
		{KEY_LEFT, &cursor_to_left},
		{KEY_HOME, &cursor_to_home},
		{KEY_END, &cursor_to_end},
	};

	while (i < 4)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
}

void				match_hist(int key_pressed, t_line *line)
{
	int							i;

	i = 0;
	static struct s_keyhist		keyhist[2] = {
		{KEY_UP, &old_history_entry},
		{KEY_DOWN, &new_history_entry}
	};

	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void				shell_core(t_line *line)
{
	int				key_pressed;
	static	t_slct	*slct_p;
	int				quote;

	if (!slct_p)
		slct_p = (t_slct *)malloc(sizeof(t_slct));
	while (1337)
	{
		key_pressed = get_key();
		loop_initiate(key_pressed, line);
		standard_commands(key_pressed, line);
		ctrl_commands(key_pressed, line, slct_p);
		quote = 0;
		quote = quote_checker(line, quote);
		if (key_pressed == '\n' && (quote % 2) != 0)
		{
			quote_handler(line, key_pressed, quote);
			quote = quote_checker(line, quote);
		}
		else if (key_pressed == '\n')
			break ;
	}
}

char				*line_editing(void)
{
	t_line			line;

	raw_term_mode();
	ft_bzero(&line, sizeof(line));
	line.hist = retrieve_history();
	line.hist_size = ft_clstsize(line.hist);
	get_cursor_start_pos(&line);
	shell_core(&line);
	cursor_to_end(&line);
	default_term_mode();
	ft_putchar('\n');
	append_history(line.cmd);
	ft_lstdelstr(&line.hist);
	return (ft_strdup(line.cmd));
}
