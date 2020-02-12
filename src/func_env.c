/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:14:10 by melalj            #+#    #+#             */
/*   Updated: 2019/09/15 16:30:14 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		f_cd_check(t_env **list_env, char **i_line)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	cwd[256];

	if (!i_line)
		return (1);
	if (!ft_varget(*list_env, "HOME"))
	{
		ft_putstr("environment variabeles is corupted\n");
		return (1);
	}
	if (i_line[1] && i_line[2])
	{
		ft_putendl("cd: too many arguments");
		return (1);
	}
	if (!(pwd = ft_varget(*list_env, "PWD")) && f_setenv(list_env, NULL, 1,
				ft_joinwith("setenv", getcwd(cwd, sizeof(cwd)), " PWD ")))
		ft_putstr("no PWD found\n");
	if (!(oldpwd = ft_varget(*list_env, "OLDPWD")) && f_setenv(list_env,
	NULL, 1, ft_joinwith("setenv", ft_valget(*list_env, "HOME"), " OLDPWD ")))
		ft_putstr("no oldPWD found redirected to your home\n");
	return (0);
}

int		f_cd(t_env **list_env, char **i_line)
{
	char	buffer[255];
	int		i;
	char	*temp;


	if (f_cd_check(list_env, i_line))
		return (1);
	if (!i_line[1] && (i = 2))
		i_line[1] = ft_valget(*list_env, "HOME");
	if (i_line[1])
	{
		if (ft_strequ(i_line[1], "-") && free_sl(i_line[1]))
			i_line[1] = ft_valget(*list_env, "OLDPWD");
		if (!access_error("cd", i_line[1], access_check(i_line[1])))
			return (1);
	}
	chdir(i_line[1]);
	getcwd(buffer, sizeof(buffer));
	f_unsetenv(list_env, ft_strsplit("unsetenv OLDPWD", ' '), 1);
	temp = ft_valget(*list_env, "PWD");
	f_setenv(list_env, NULL, 1, ft_joinwith("setenv", temp, " OLDPWD "));
	f_unsetenv(list_env, ft_strsplit("unsetenv PWD", ' '), 1);
	f_setenv(list_env, NULL, 1, ft_joinwith("setenv", buffer, " PWD "));
	if (free_sl(temp) && i == 2 && free_sl(i_line[1]))
		i_line[1] = NULL;
	return (0);
}

int		f_setenv(t_env **list_env, char **i_line, int mode, char *line)
{
	t_env	*var;
	char	*var_val;

	var = NULL;
	if ((mode == 0) && (!i_line[1] || !i_line[2] || i_line[3]))
		return (1);
	if (mode == 1)
	{
		i_line = ft_strsplit(line, ' ');
		free_sl(line);
	}
	var_val = ft_joinwith(i_line[1], i_line[2], "=");
	if ((var = ft_varget(*list_env, i_line[1])) != NULL)
		var->name = ft_strdup(var_val);
	else
		add_var(list_env, var_val);
	if (mode)
		free_tab(i_line);
	free(var_val);
	return (0);
}

int		f_unsetenv(t_env **list_env, char **i_line, int mode)
{
	t_env	*var;

	var = NULL;
	if (!i_line[1] || i_line[2])
	{
		ft_putstr("usage : unsetenv variable_name\n");
		return (1);
	}
	if ((var = ft_varget(*list_env, i_line[1])) != NULL)
		del_var(list_env, var);
	if (mode)
		free_tab(i_line);
	i_line = NULL;
	return (0);
}

char	*f_which(t_env *list_env, char **i_line, int mode)
{
	char	**splited_path;
	char	*val_path;
	int		i;
	int		j;

	if (((val_path = ft_valget(list_env, "PATH")) == NULL))
		return (NULL);
	splited_path = ft_strsplit(val_path, ':');
	j = 0;
	while (i_line[++j])
	{
		i = -1;
		while (splited_path[++i])
		{
			val_path = ft_pathjoin(splited_path[i], i_line[j]);
			if (access(val_path, F_OK) != -1)
			{
				if (mode == 1)
					return (val_path);
				ft_putendl(val_path);
			}
			free(val_path);
		}
	}
	return (NULL);
}
