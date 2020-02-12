/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <mouadelalj@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 03:18:26 by melalj            #+#    #+#             */
/*   Updated: 2019/07/19 03:27:16 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfill(char c, size_t len)
{
	char		*s;
	size_t		i;

	i = 0;
	s = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
		s[i++] = c;
	s[len] = '\0';
	return (s);
}
