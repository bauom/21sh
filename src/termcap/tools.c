/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:42:07 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 07:04:51 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void			ft_clstadd(t_clist **head, t_clist *new)
{
	t_clist		*ptr;

	ptr = NULL;
	if (!head)
		*head = (t_clist *)malloc(sizeof(t_clist));
	if (!new)
		return ;
	new->next = *head;
	if (*head)
	{
		ptr = (*head)->prev;
		(*head)->prev = new;
	}
	new->prev = ptr;
	if (ptr)
		ptr->next = new;
	*head = new;
}

t_clist			*ft_clstnew(void const *content, size_t content_size)
{
	t_clist		*new_node;

	new_node = (t_clist *)malloc(sizeof(t_clist));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_clist));
	if (!content)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	else
	{
		new_node->content = (void *)malloc(content_size);
		if (!new_node->content)
			return (NULL);
		ft_memcpy(new_node->content, content, content_size);
		new_node->content_size = content_size;
	}
	return (new_node);
}

void			ft_lstdelstr(t_clist **list)
{
	t_clist		*tmp;

	*list = ft_clstgethead(*list);
	while (*list)
	{
		tmp = *list;
		free((*list)->content);
		*list = (*list)->next;
		free(tmp);
	}
}

t_clist			*ft_clstgethead(t_clist *list)
{
	while (list)
	{
		if (list->prev)
			list = list->prev;
		else
			break ;
	}
	return (list);
}

size_t			ft_clstsize(t_clist *lst)
{
	size_t		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
