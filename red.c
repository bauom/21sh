/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 00:36:01 by melalj            #+#    #+#             */
/*   Updated: 2019/08/10 00:17:45 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_red(char **line_ab, char **cmd)
{
	char	**buff;
	int		f;
	t_list	*lst;
	char	*line;
	int		w;
	t_cmd	*tmp;

	f = 1;
	lst = NULL;
	while (f != -1)
	{
		tmp = p_cmd(line_ab, &f);
		if (f != -1)
			ft_lstaddend(&lst, (void *)tmp, sizeof(t_cmd));
		free(tmp);
	}
	line = NULL;
	if (!(*cmd = r_token(&lst, &line)))
		return (NULL);
	t_list *tmp_f;
	while (lst)
	{
		tmp_f = lst;
		lst = lst->next;
		if (tmp_f->content && ((t_cmd *)(tmp_f->content))->cmd)
			free(((t_cmd *)(tmp_f->content))->cmd);
		if (tmp_f->content)
			free(tmp_f->content);
		free(tmp_f);
	}
	buff = ft_strsplit(line, ';');
	free(line);
	w = dup_fd(0);
	while (buff && buff[++f])
	{
		if (buff[f][ft_strlen(buff[f]) - 1] == '-' && buff[f][ft_strlen(buff[f]) - 2] == '&')
			close(ft_atoi(buff[f]));
		else if (ft_strchr("rai", buff[f][1]))
		{
			if (ft_strchr(buff[f], '&'))
			{
				dup2(fd_tored(buff[f]), 1);
				dup2(fd_tored(buff[f]), 2);
			}
			dup2(fd_tored(buff[f]), ft_atoi(buff[f]));
		}
		else if (buff[f][1] == 'h')
		{
			dup2(w, 0);
			h_doc(buff[f]);
		}
	}
	close(w);
	return (buff);
}

int		fd_tored(char *buff)
{
	int i;
	int fd;

	i = 2;
	i += ft_strchr(buff, 'o') ? 1 : 0;
	i += buff[2] == '&' ? 1 : 0;
	return (fd = ft_atoi(&buff[i]));
}

void	h_doc(char *eof)
{
	char	*line;
	int		eof_i;
	char	*tmp;
	int		fd[2];

	line = NULL;
	tmp = NULL;
	pipe(fd);
	while (1)
	{
		ft_putstr("heredoc> ");
		if (get_next_line(0, &tmp) < 1)
		{
			ft_putstr("\n");
			break ;
		}
		if (!ft_strequ(&eof[2], tmp))
		{
			add_line(&line, tmp);
			if (tmp[ft_strlen(tmp) - 1] != '\\')
				add_line(&line, "\n");
			free(tmp);
		}
		else if (free_sl(tmp))
			break ;
	}
	dup2(fd[0], ft_atoi(eof));
	close(fd[0]);
	write(fd[1], line, ft_strlen(line));
	close(fd[1]);
	free(line);
}

int		r_a(t_cmd *token, char **line, int *i)
{
	char	*tmp;

	if (token->type == 'r' || token->type == 'a')
	{
		if (!((*line)[0]) || (*line)[*i - 1] == ';')
			add_line(line, "1");
		add_line(line, (token->type == 'r') ? "r" : "a");
	}
	else if (token->type == 'u' && ft_strchr("ar&", (*line)[*i - 1]))
	{
		if (ft_isnumber(token->cmd) && (*line)[*i - 1] == '&')
		{
			if (check_fd(token->cmd))
				return (1);
			tmp = ft_strdup(token->cmd);
		}
		else
			tmp = open_red(token, line, token->cmd, i);
		add_line(line, tmp);
		free(tmp);
		add_line(line, ";");
	}
	return (0);
}

void	in_r(t_cmd *token, char **line, int *i)
{
	char	*tmp;

	if (token->type == 'i' || token->type == 'h')
	{
		if (!((*line)[0]) || (*line)[*i - 1] == ';')
			add_line(line, "0");
		add_line(line, token->type == 'i' ? "i" : "h");
	}
	else if (token->type == 'u' && (*line)[*i - 1] == 'i')
	{
		if (ft_isnumber(token->cmd) && *line[ft_strlen(*line) - 1] == '&')
			tmp = ft_strdup(token->cmd);
		else
			tmp = open_red(token, line, token->cmd, i);
		add_line(line, tmp);
		free(tmp);
		add_line(line, ";");
	}
	else if (token->type == 'u' && (*line)[*i - 1] == 'h')
	{
		add_line(line, token->cmd);
		add_line(line, ";");
	}
}

char	*open_red(t_cmd *token, char **line, char *file, int *i)
{
	char	*tmp;
	int		skip_agr;

	skip_agr = (*line)[*i - 1] == '&' ? 2 : 1;
	tmp = NULL;
	if (ft_strequ(token->cmd, "-") && (*line)[ft_strlen(*line) - 1] == '&')
		tmp = ft_strdup("-");
	else if (ft_strchr("ar", (*line)[*i - skip_agr]))
	{
		if ((*i = open(file, ((*line)[*i - skip_agr] == 'r' ?
			O_TRUNC : O_APPEND) | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			return (NULL);
		else
		{
			add_line(line, "o");
			tmp = ft_itoa(*i);
		}
	}
	else if ((*line)[*i - skip_agr] == 'i')
	{
		if (((*i = open(file, O_RDONLY)) < 0) && access_c(file, 'r', i))
			return (NULL);
		else
		{
			add_line(line, "o");
			tmp = ft_itoa(*i);
		}
	}
	return (tmp);
}

int		access_c(char *file, int per, int *error)
{
	*error = access_check(file);
	if (*error == 'r')
	{
		if (!access(file, per))
		{
			ft_putstr_fd("21sh: permission denied: ", 2);
			ft_putendl_fd(file, 2);
			*error = -1;
		}
	}
	else
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		*error = -1;
	}
	return (1);
}
