/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:34:45 by melalj            #+#    #+#             */
/*   Updated: 2019/06/25 21:29:39 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_var(char *var)
{
	t_env	*new_dr;

	if (!(new_dr = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new_dr->next = NULL;
	new_dr->name = ft_strdup(var);
	return (new_dr);
}

void	add_var(t_env **lst_var, char *var)
{
	t_env	*current;

	if (*lst_var == NULL)
		*lst_var = new_var(var);
	else
	{
		current = *lst_var;
		while (current->next)
			current = current->next;
		current->next = new_var(var);
	}
}

t_env	*get_env(char **env)
{
	t_env	*ev;
	int		i;

	i = -1;
	ev = NULL;
	while (env[++i] != NULL)
		add_var(&ev, env[i]);
	return (ev);
}

void	print_env(t_env *list_env)
{
	while (list_env)
	{
		ft_putendl(list_env->name);
		list_env = list_env->next;
	}
}

void	del_var(t_env **list_env, t_env *to_del)
{
	t_env	*current;

	current = *list_env;
	while (current)
	{
		if (current->next == to_del)
		{
			current->next = to_del->next;
			free(to_del->name);
			free(to_del);
			break ;
		}
		current = current->next;
	}
}
