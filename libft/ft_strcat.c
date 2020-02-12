/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:50:50 by melalj            #+#    #+#             */
/*   Updated: 2018/10/11 04:41:36 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char *s1c;

	s1c = s1 + ft_strlen(s1);
	while (*s2)
	{
		*s1c = *s2;
		s1c++;
		s2++;
	}
	*s1c = '\0';
	return (s1);
}