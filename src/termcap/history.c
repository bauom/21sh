/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:38:27 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 06:49:51 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static	void		feed_line(t_line *line, char *entry)
{
	cursor_to_home(line);
	tputs(tgetstr("cd", NULL), 0, &my_putchar);
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
}

void				new_history_entry(t_line *line, t_clist **hist)
{
	if (!line->hist || (line->hist && !line->hist_depth))
		return ;
	line->hist_depth--;
	*hist = (*hist)->prev;
	feed_line(line, (*hist)->content);
	print_line(line->cmd);
	if (!line->hist_depth)
		ft_lstremovenode(hist);
}

void				ft_lstremovenode(t_clist **hist)
{
	t_clist			*ptr;

	if (*hist)
	{
		if ((*hist)->prev)
			(*hist)->prev->next = (*hist)->next;
		if ((*hist)->next)
			(*hist)->next->prev = (*hist)->prev;
		ptr = *hist;
		*hist = (*hist)->next ? (*hist)->next : (*hist)->prev;
		free(ptr->content);
		free(ptr);
	}
}

void				old_history_entry(t_line *line, t_clist **hist)
{
	t_clist			*new_node;

	if (!line->hist || (line->hist && line->hist_depth == line->hist_size))
		return ;
	if (!line->hist_depth)
	{
		new_node = ft_clstnew(line->cmd, ft_strlen(line->cmd) + 1);
		if (new_node)
			new_node->content_size = MAX_HIST_LEN;
		ft_clstadd(hist, new_node);
	}
	*hist = (*hist)->next;
	line->hist_depth++;
	feed_line(line, (*hist)->content);
	print_line(line->cmd);
}
