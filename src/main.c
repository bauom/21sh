/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 22:02:39 by melalj            #+#    #+#             */
/*   Updated: 2019/12/29 16:25:35 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		main(int ac, char **av, char **ev)
{
	t_env	*env;
	char	*i;

	/*if (!read(0, NULL, 0))
		return (0);*/
	if (ac != 1)
	{
		env = get_env(ev);
		melalsh_exec(&env, ft_strdup(av[ac - 1]));
		return(0);
	}
	env = get_env(ev);
	melalsh_loop(&env);
	free_env(&env);
	return (0);
}
