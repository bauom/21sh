/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:17:39 by hhadraou          #+#    #+#             */
/*   Updated: 2019/12/28 07:06:32 by hhadraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

/* POSIX version define */

# define _POSIXSOURCE 1

/* system headers */

# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <fcntl.h>

/* local header */

# include "../../libft/libft.h"

/* command and history length */

# define MAX_KEY_LEN    4
# define MAX_CMD_LEN    4096
# define MAX_HIST_LEN   5092

/* arrows */

# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"

/* delete */

# define KEY_CODE_DEL "\x1b\x5b\x33\x7e"

/* HOME and END keys */

# define KEY_CODE_HOME "\x1b\x5b\x48\0"
# define KEY_CODE_END "\x1b\x5b\x46\0"

/* clear screen */

# define KEY_CTRLL 12

/* select & unselect buttons */

# define KEY_CTRLK 11
# define KEY_CTRLI 9    /* cut */
# define KEY_CTRLJ 10   /* copy */
# define KEY_CTRLH 8    /* paste */
# define KEY_CTRLD 4

/*
where to stock used commands
*/

# define HISTORY_PATH "21sh_history" /* this needs to be changed to the tilda */

/* windows specs */

typedef struct      s_winsz
{
	size_t          row;
	size_t          col;
}                   t_winsz;

/* matching keys */

struct              s_keymatch 
{
	char            *key_code;
	int             key_ret;
};

/* history stocking and browsing list */

typedef struct      s_clist
{
	void            *content;
	size_t          content_size;
	struct s_clist   *next;
	struct s_clist   *prev;
}                   t_clist;

/* line specs */

typedef struct      s_line
{
	t_clist         *hist;
	size_t          cursor;
	size_t          length;
	size_t          hist_depth;
	size_t          hist_size;
	t_winsz         winsz;
	t_winsz         start;
	char            cmd[MAX_CMD_LEN];
}                   t_line;

/* selected elements specs in the select mode */
 
typedef struct      s_slct
{
	size_t          start;
	size_t          end;
	char            slct_cmd[MAX_CMD_LEN];
}                   t_slct;

/* matching movements */

struct              s_keymove
{
	int             key;
	void            (*p)(t_line *line);
};

/* matching history keys */

struct              s_keyhist
{
	int             key;
	void            (*p)(t_line *line, t_clist **hist);
};

/* program functions */

char			*line_editing(void);
void			goto_next_word(t_line *line);
void			goto_prev_word(t_line *line);
void			goto_next_line(t_line *line);
void			goto_prev_line(t_line *line);
void			set_curpos(t_line *line);
void			cursor_to_left(t_line *line);
void			cursor_to_right(t_line *line);
void			cursor_to_end(t_line *line);
void			cursor_to_home(t_line *line);
int			    ft_getwinsz(t_winsz *winsz);
void			delete_char(t_line *line, int key);
void			insert_char(t_line *line, int key);
int			    my_putchar(int c);
size_t			ft_clstsize(t_clist *lst);
void			new_history_entry(t_line *line, t_clist **hist);
void			old_history_entry(t_line *line, t_clist **hist);
void			append_history(char *entry);
t_clist			*retrieve_history(void);
void			default_term_mode(void);
void			raw_term_mode(void);
int			    get_key(void);
void			ft_lstdelstr(t_clist **list);
t_clist			*ft_clstgethead(t_clist *list);
void			ft_lstremovenode(t_clist **hist);
void			ft_clstadd(t_clist **head, t_clist *new);
t_clist			*ft_clstnew(void const *content, size_t content_size);
void		    print_line(char *line);
void	        paste_slct_item(t_line *line, t_slct *slct_p);
void	        select_mode(t_line *line, t_slct *slct_p);
void		    quote_handler(t_line *line, int key_pressed, int quote);
void            get_cursor_start_pos(t_line *line);
void            ctrl_commands(int key_pressed, t_line *line, t_slct  *slct_p);
int			    quote_checker(t_line *line, int quote);
void	        loop_initiate(int key_pressed, t_line *line);
void            match_move(int key_pressed, t_line *line);
void            match_hist(int key_pressed, t_line *line);
void	        standard_commands(int key_pressed, t_line *line);
void            apply_select_1(t_slct *slct_p, t_line *line, int mode);
void            apply_select_0(t_slct *slct_p, t_line *line, int mode);
void		    apply_copy(t_slct *slct_p, t_line *line, int ctr);
void            apply_cut(t_slct *slct_p, t_line *line, int ctr, int tmp);
void            select_initiate(t_line *line, t_slct *slct_p);
void		    select_cases(int key_pressed, t_slct *slct_p, t_line *line);
#endif
