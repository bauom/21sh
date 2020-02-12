/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:24:31 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/29 14:58:09 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*type_builtin(t_env *list_env, char **i_line, int mode) /* the not found case is still missing */
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
		if ((ft_strlen(i_line[1]) == 2) && i_line[1][0] == '-')
			type_flags(i_line, j, splited_path, val_path);
		else if (ft_strequ(i_line[j], "env") || ft_strequ(i_line[j] , "setenv")
			|| ft_strequ(i_line[j], "unsetenv") || ft_strequ(i_line[j], "which")
			|| ft_strequ(i_line[j], "cd") || ft_strequ(i_line[j], "echo")
			|| ft_strequ(i_line[j], "refresh") || ft_strequ(i_line[j], "type"))
		{
			ft_putstr(i_line[j]);
			ft_putendl(" is a shell builtin");
		}
		else if (if_keyword(&i_line[j], j))
		{
			ft_putstr(i_line[j]);
			ft_putendl(" is a shell keyword");
		}
		else
		{
			while (splited_path[++i])
			{
				val_path = ft_pathjoin(splited_path[i], i_line[j]);
				if (!access(val_path, F_OK) && !access(val_path, X_OK))
				{
					ft_putstr(i_line[j]);
					ft_putstr(" is ");
					ft_putendl(val_path);
					break ;
				}
				free(val_path);
			}
		}
	}
	return (NULL);
}

void	type_flags(char **i_line, int j, char **splited_path, char *val_path)
{
	int		i;
	int		std;

	std = 0;
	if (i_line[1][1] == 'a')
	{
		if (ft_strequ(i_line[j], "env") || ft_strequ(i_line[j] , "setenv")
			|| ft_strequ(i_line[j], "unsetenv") || ft_strequ(i_line[j], "which")
			|| ft_strequ(i_line[j], "cd") || ft_strequ(i_line[j], "echo")
			|| ft_strequ(i_line[j], "refresh") || ft_strequ(i_line[j], "type"))
		{
			ft_putstr(i_line[j]);
			ft_putendl(" is a shell builtin");
		}
		else if (if_keyword(&i_line[j], j))
		{
			ft_putstr(i_line[j]);
			ft_putendl(" is a shell keyword");
		}
		i = -1;
		while (splited_path[++i])
		{
			val_path = ft_pathjoin(splited_path[i], i_line[j]);
			if (!access(val_path, F_OK) && !access(val_path, X_OK))
			{
				ft_putstr(i_line[j]);
				ft_putstr(" is ");
				ft_putendl(val_path);
				break ;
			}
			free(val_path);
		}
	}
	else if (i_line[1][1] == 't')
	{
		if (ft_strequ(i_line[j], "env") || ft_strequ(i_line[j] , "setenv")
			|| ft_strequ(i_line[j], "unsetenv") || ft_strequ(i_line[j], "which")
			|| ft_strequ(i_line[j], "cd") || ft_strequ(i_line[j], "echo")
			|| ft_strequ(i_line[j], "refresh") || ft_strequ(i_line[j], "type"))
		{
			std = 1;
			ft_putendl("builtin");
		}
		else if (if_keyword(&i_line[j], j))
			ft_putendl("keyword");
		i = -1;
		while (splited_path[++i])
		{
			val_path = ft_pathjoin(splited_path[i], i_line[j]);
			if (!access(val_path, F_OK) && !access(val_path, X_OK) && (std == 0))
			{
				ft_putendl("file");
				break ;
			}
			free(val_path);
		}
	}
	else if (i_line[1][1] == 'p')
	{
		if (!ft_strequ(i_line[j], "env") && !ft_strequ(i_line[j] , "setenv")
			&& !ft_strequ(i_line[j], "unsetenv") && !ft_strequ(i_line[j], "which")
			&& !ft_strequ(i_line[j], "cd") && !ft_strequ(i_line[j], "echo")
			&& !ft_strequ(i_line[j], "refresh") && !ft_strequ(i_line[j], "type"))
		{
			i = -1;
			while (splited_path[++i])
			{
				val_path = ft_pathjoin(splited_path[i], i_line[j]);
				if (!access(val_path, F_OK) && !access(val_path, X_OK))
				{
					ft_putendl(val_path);
					break;
				}
				free(val_path);
			}
		}
	}
}

int		if_keyword(char **i_line, int j)
{
	if (ft_strequ(*i_line, "break") || ft_strequ(*i_line , "char")
			|| ft_strequ(*i_line, "const") || ft_strequ(*i_line, "continue")
			|| ft_strequ(*i_line, "else") || ft_strequ(*i_line, "enum")
			|| ft_strequ(*i_line, "extern") || ft_strequ(*i_line, "if")
			|| ft_strequ(*i_line, "int") || ft_strequ(*i_line, "return")
			|| ft_strequ(*i_line, "sizeof") || ft_strequ(*i_line, "static")
			|| ft_strequ(*i_line, "struct") || ft_strequ(*i_line, "typedef")
			|| ft_strequ(*i_line, "void") || ft_strequ(*i_line, "while"))
			return (1);
	else
		return (0);
}