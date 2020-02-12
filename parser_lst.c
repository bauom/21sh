/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:22:15 by melalj            #+#    #+#             */
/*   Updated: 2019/08/10 00:44:49 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*p_cmd(char **line_ab, int *i)
{
	t_cmd	*cmd;
	static int		c;

	if (*i == 1 && !(c = 0))
		*i = 2;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->type = 'n';
	//token_p(line_ab, &cmd, &c);
	if (token_p(line_ab, &cmd, &c))
	{
		free(cmd);
		cmd = NULL;
		*i = -1;
		return (cmd);
	}
	return (cmd);
}

int		token_p(char **line_ab, t_cmd **cmd, int *j)
{
	int				i;
	static int		c = 'n';

	i = 0;
	(*cmd)->cmd = NULL;
	(*cmd)->type = ((c == 'u' && ft_strchr("cs", line_ab[1][(*j)])) ? c :
														line_ab[1][i + (*j)]);
	c = (c == 'u') ? 'n' : c;
	while (line_ab[1][i + *j])
	{
		if ((line_ab[1][i + *j] == ' ')
				|| (!ft_strchr("cs", line_ab[1][i + (*j)]) && i != 0))
			break ;
		else if (!ft_strchr("cs", line_ab[1][i + (*j)]) && i == 0 && ++i
				&& (c = ((ft_strchr("arih&", line_ab[1][(*j)])) ? 'u' : c)))
			break ;
		i++;
	}
	if (i == 0)
		return (1);
	(*cmd)->cmd = ft_strsub(line_ab[0], (*j), i);
	while (line_ab[1][i + (*j)] == ' ')
		i++;
	(*j) += i;
	return (0);
}

char	*r_token(t_list	**lst_token, char **redi)
{
	t_cmd	*token;
	char	*cmd;
	char	*tmp;
	t_list	*current;

	current = *lst_token;
	cmd = ft_strnew(0);
	*redi = ft_strdup("");
	while (current && (token = (t_cmd *)((current)->content)))
	{
		if (token->type == 'p')
			break ;
		if (token->type != 'c' && token->type != 's')
		{
			if (r_r(token, redi) == -1)
				return (NULL);
			current = (current)->next;
			continue ;
		}
		if (*cmd)
		{
			tmp = ft_joinwith(cmd, token->cmd, "\002");
			free(cmd);
			cmd = tmp;
		}
		else
			add_line(&cmd, token->cmd);
		//tmp = (*cmd) ? ft_joinwith(cmd, token->cmd, "\002") : ft_strjoin(cmd, token->cmd);
		current = (current)->next;
	}
	return (cmd);
}

int		r_r(t_cmd *token, char **line)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*line);
	if (token->type == 'f')
		add_line(line, token->cmd);
	else if (token->type == '&')
		add_line(line, token->cmd);
	else if (token->type == 'r' || token->type == 'a'
			|| (token->type == 'u' && ft_strchr("&ar", (*line)[i - 1])))
	{
		if (r_a(token, line, &i))
			return (-1);
	}
	else if (token->type == 'i' || token->type == 'u' || token->type == 'h')
		in_r(token, line, &i);
	return (i);
}
