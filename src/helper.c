/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 01:54:18 by melalj            #+#    #+#             */
/*   Updated: 2019/12/29 16:47:02 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		f_env(t_env *list_env)
{
	if (list_env)
		print_env(list_env);
	else
		return (1);
	return (0);
}

int		buildin_check(t_env **list_env, char **i_line)
{
	int			i;

	i = -1;
	if (ft_strequ(i_line[0], "env"))
		i = f_env(*list_env);
	else if (ft_strequ(i_line[0], "setenv"))
		i = f_setenv(list_env, i_line, 0, NULL);
	else if (ft_strequ(i_line[0], "unsetenv"))
		i = f_unsetenv(list_env, i_line, 0);
	else if (ft_strequ(i_line[0], "which"))
		i = f_which(*list_env, i_line, 0) ? 1 : 0;
	else if (ft_strequ(i_line[0], "cd"))
		i = f_cd(list_env, i_line);
	else if (ft_strequ(i_line[0], "echo"))
		i = b_echo(i_line);
	else if (ft_strequ(i_line[0], "refresh"))
		i = refresh_up(list_env);
	else if (ft_strequ(i_line[0], "type"))
		i = type_builtin(*list_env, i_line, 0) ? 1 : 0;
	if (i != -1)
		free_tab(i_line);
	return (i);
}

int		ft_envlen(t_env **alst)
{
	t_env	*current;
	int		i;

	i = 0;
	current = *alst;
	while (current != 0)
	{
		i++;
		current = current->next;
	}
	return (i);
}

t_env	*ft_varget(t_env *alst, char *var_name)
{
	t_env	*current;
	char	**to_free;

	current = alst;
	while (current)
	{
		to_free = ft_strsplit(current->name, '=');
		if (ft_strequ(to_free[0], var_name))
		{
			free_tab(to_free);
			return (current);
		}
		free_tab(to_free);
		current = current->next;
	}
	return (NULL);
}

char	*ft_valget(t_env *alst, char *var_name)
{
	t_env	*current;
	char	**to_free;
	char	*ret;

	current = alst;
	if (current != NULL)
	{
		while (current)
		{
			to_free = ft_strsplit(current->name, '=');
			if (ft_strequ(to_free[0], var_name))
			{
				ret = ft_strdup(to_free[1]);
				free_tab(to_free);
				return (ret);
			}
			free_tab(to_free);
			current = current->next;
		}
	}
	return (NULL);
}
