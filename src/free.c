/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:13:36 by melalj            #+#    #+#             */
/*   Updated: 2019/06/25 21:29:49 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_env(t_env **env)
{
	t_env	*current;
	t_env	*to_free;

	current = *env;
	while (current)
	{
		to_free = current;
		current = current->next;
		del_var(env, to_free);
	}
	return (1);
}

int	free_tab(char **to_free)
{
	int i;

	i = -1;
	if (to_free)
	{
		while (to_free[++i])
			free_sl(to_free[i]);
		free_sl(to_free);
	}
	return (1);
}
