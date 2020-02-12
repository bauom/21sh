/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:25:50 by melalj            #+#    #+#             */
/*   Updated: 2019/08/10 00:20:17 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_read(char **str, int fd)
{
	int		ret;
	char	*s;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[ret] = '\0';
	s = ft_strdup(*str);
	free(*str);
	*str = ft_joinwith(s, buf, "");
	free(s);
	return (ret);
}

static int		ft_get_line(char **str, char **line, char *s)
{
	int	i;

	i = 0;
	if (*s == '\n')
		i = 1;
	*s = 0;
	*line = NULL;
	free(*line);
	*line = ft_strdup(*str);
	if (i == 0 && ft_strlen(*str) != 0)
	{
		free(*str);
		*str = ft_strdup("");
		return (1);
	}
	else if (i == 0 && !(ft_strlen(*str)))
		return (0);
	free(*str);
	*str = NULL;
	//*str = ft_strdup(s + 1);
	//free(*str);
	//*str = NULL;
	return (i);
}

int				get_next_line(int const fd, char **line)
{
	int			ret;
	char		*s;
	static char	*str;

	if (str == 0)
		str = ft_strnew(0);
	if (!line || BUFF_SIZE < 1)
		return (-1);
	ret = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || ret < BUFF_SIZE)
		{
			if (*s == '\n' || *s == 0)
				return (ft_get_line(&str, line, s));
			s++;
		}
		ret = ft_read(&str, fd);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

// #include "libft.h"
// #include <stdio.h>

// int			new_line(char *s)
// {
// 	int		i;
// 	char	*c_s;

// 	i = 0;
// 	c_s = ft_strdup(s);
// 	while (c_s[i])
// 	{
// 		if (c_s[i] == '\n')
// 		{
// 			free(c_s);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	free(c_s);
// 	return (0);
// }

// t_file		*fd_exist(t_file **lst, int fd)
// {
// 	t_file	*current;

// 	current = *lst;
// 	while (current != 0)
// 	{
// 		if (current->fd == fd)
// 			return (current);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// t_file		*lstfile_new(const char *content, int fd)
// {
// 	t_file *new;

// 	if (!(new = (t_file *)malloc(sizeof(t_file))))
// 		return (NULL);
// 	new->next = NULL;
// 	if (!content)
// 	{
// 		new->stock = NULL;
// 		new->fd = fd;
// 	}
// 	else
// 	{
// 		new->stock = (char *)malloc(ft_strlen(content));
// 		new->stock = ft_memcpy(new->stock, content, ft_strlen(content));
// 		new->fd = fd;
// 	}
// 	return (new);
// }

// t_file		*lstfile_add(t_file *head, t_file *new)
// {
// 	t_file *start;

// 	start = head;
// 	while (start->next)
// 		start = start->next;
// 	start->next = new;
// 	return (new);
// }

// int			get_next_line(const int fd, char **text)
// {
// 	static t_file	*lst;
// 	t_file			*current;
// 	int				ret;
// 	char			buff[BUFF_SIZE + 1];
// 	char *tmp;

// 	if (fd < 0 || (read(fd, buff, 0) < 0) || !text)
// 		return (-1);
// 	lst = (lst == NULL) ? lstfile_new("", fd) : lst;
// 	if (!(current = fd_exist(&lst, fd)))
// 		current = lstfile_add(lst, lstfile_new("", fd));
// 	ret = read(fd, buff, BUFF_SIZE);
// 	if (ret == -1)
// 		return (ret);
// 	buff[ret] = '\0';
// 	tmp = ft_strjoin(current->stock, buff);
// 	free(current->stock);
// 	current->stock = ft_strdup(tmp);
// 	free(tmp);
// 	while (!new_line(current->stock) && ret)
// 	{
// 		ret = read(fd, buff, BUFF_SIZE);
// 		buff[ret] = '\0';
// 		tmp = ft_strjoin(current->stock, buff);
// 		free(current->stock);
// 		current->stock = ft_strdup(tmp);
// 		free(tmp);
// 	}
// 	ret = (!ft_strchr(current->stock, '\n')) ? 3 : 1;
// 	*text = ft_strcut(current->stock, '\n');
// 	ret = (current->stock[0] == '\0') ? 0 : ret;
// 	current->stock += ft_strlen(*text) + new_line(current->stock);
// 	return (ret);
// }
