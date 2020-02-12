/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isWspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <mouadelalj@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 23:37:26 by melalj            #+#    #+#             */
/*   Updated: 2019/07/23 23:44:29 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_iswspace(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 
			|| c == 32)
		return (1);
	return (0);
}
