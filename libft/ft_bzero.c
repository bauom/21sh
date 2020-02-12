/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 01:04:49 by melalj            #+#    #+#             */
/*   Updated: 2019/08/08 11:40:30 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*val_b;

	val_b = (unsigned char *)malloc(n);
	val_b = s;
	while (n)
	{
		*val_b = 0;
		val_b++;
		n--;
	}
}
