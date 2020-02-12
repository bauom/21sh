/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_history_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 06:47:08 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 06:47:22 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "line_editing.h"

void	append_history(char *entry)
{
	int	fd;

	if (!(*entry))
		return ;
	fd = open(HISTORY_PATH, O_RDWR | O_APPEND | O_CREAT, 0777);
	ft_putendl_fd(entry, fd);
	close(fd);
}

t_clist     *retrieve_history(void)
{
	int     fd;
	t_clist *hist;
	char    *line;
	size_t  len;

	hist = NULL;
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line);
		if (len < MAX_CMD_LEN)
			ft_clstadd(&hist, ft_clstnew(line, len + 1));
		free(line); 
	}
	close(fd);
	return (hist);
}
