/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <mouadelalj@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 21:13:42 by melalj            #+#    #+#             */
/*   Updated: 2019/06/11 21:26:32 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char     *ft_strndup(const char *s, int n)
{
	char    *str;

	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}
