/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 23:00:55 by melalj            #+#    #+#             */
/*   Updated: 2019/09/15 16:50:50 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_count(char const *s, char c)
{
	unsigned int	i;
	int				cntr;

	i = 0;
	cntr = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cntr++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (cntr);
}

char			***split_ab(char **s, char c)
{
	int		i;
	int		j;
	int		k;
	char	***tt;

	i = 0;
	k = 0;
	tt = (char ***)malloc(sizeof(char **) * (ft_count(s[0], c)) + 1);
	if (tt == NULL)
		return (NULL);
	while (s[0][i])
	{
		while (s[0][i] == c)
			i++;
		j = i;
		while (s[0][i] && s[0][i] != c)
			i++;
		if (i > j)
		{
			tt[k] = (char **)malloc(sizeof(char *) * 3);
			tt[k][0] = ft_strndup(s[0] + j, i - j);
			tt[k][1] = ft_strndup(s[1] + j, i - j);
			tt[k][2] = NULL;
			k++;
		}
	}
	tt[k] = NULL;
	return (tt);
}
