/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:45:47 by melalj            #+#    #+#             */
/*   Updated: 2019/07/22 21:15:22 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**line_interpret(t_env *env, char *line)
{
	char	**i_line;
	char	*temp;
	int		i;
	char	**f_tab;

	temp = ft_strtrim(line);
	i_line = ft_strssplit(temp, "\002");
	free(temp);
	i = 0;
	return (i_line);
}

char	**env_tab(t_env *list_env)
{
	char	**new_env;
	int		i;
	t_env	*current;

	i = 0;
	current = list_env;
	while (current)
	{
		i++;
		current = current->next;
	}
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((list_env != NULL))
	{
		new_env[i++] = ft_strdup(list_env->name);
		list_env = list_env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_printt(char **tt)
{
	int i;

	i = -1;
	while (tt[++i])
	{
		ft_putstr("tab[");
		ft_putnbr(i);
		ft_putendl("] : ");
		ft_putendl(tt[i]);
	}
}
