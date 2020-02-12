/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 23:27:00 by melalj            #+#    #+#             */
/*   Updated: 2019/08/09 22:54:55 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_count(char const *s, char *c)
{
	int	i[2];
	int	cntr;

	i[0] = 0;
	i[1] = 'n';
	cntr = 0;
	while (s[i[0]])
	{
		while (ft_strchr(c, s[i[0]]))
			i[0]++;
		if (s[i[0]] != '\0')
			cntr++;
		while (s[i[0]] && (!ft_strchr(c, s[i[0]])
		| ((i[1] = ft_qc((char *)(s + i[0]), i[1])) != 'n')))
			i[0]++;
	}
	return (cntr);
}

char			**ft_strssplit(char const *s, char *c)
{
	int		i[4];
	char	**tt;

	i[0] = 0;
	i[1] = 0;
	i[3] = 'n';
	if (s == NULL || c == NULL)
		return (NULL);
	if (!(tt = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1))))
		return (NULL);
	while (s[i[0]])
	{
		while (ft_strchr(c, s[i[0]]))
			i[0]++;
		i[2] = i[0];
		while (s[i[0]] && (!ft_strchr(c, s[i[0]])
		| ((i[3] = ft_qc((char *)(s + i[0]), i[3])) != 'n')))
			i[0]++;
		if (i[0] > i[2])
		{
			tt[i[1]] = ft_strndup(s + i[2], i[0] - i[2]);
			i[1]++;
		}
	}
	tt[i[1]] = NULL;
	return (tt);
}
