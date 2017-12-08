/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledru <aledru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:57:00 by aledru            #+#    #+#             */
/*   Updated: 2017/11/22 17:57:09 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*
** ------------------------------ libft functions ------------------------------
*/

void			*ft_memalloc(size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memset(void *str, int c, size_t size);
void			ft_putstr(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strlen(char *str);
char			*ft_strnew(size_t size);

/*
** -------------------------------- structures ---------------------------------
*/

typedef	struct	s_map
{
	int			size;
	char		**content;
}				t_map;

typedef struct	s_tetri
{
	char		**pos;
	int			height;
	int			width;
	char		letter;
}				t_tetri;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
** ---------------------------- list.c functions -------------------------------
*/

t_list			*ft_list_new(void const *content, size_t size);
void			ft_list_add(t_list **alst, t_list *new_list);
void			ft_list_rev(t_list **lst);
int				list_count(t_list *lst);

/*
** ---------------------------- reader.c functions -----------------------------
*/

int				is_filevalid(char *tetris);
char			*read_file(int file);
t_list			*get_tetri_list(char *tetris);

/*
** ------------------------------ map.c functions ------------------------------
*/
void			print_map(t_map *map);
t_map			*create_map(int size);
void			free_map(t_map *map);
int				place_tetri(t_map *map, t_tetri *tetri, int x, int y);
void			setchar_tetri(t_map *map, t_tetri *t, t_point *point, char c);

/*
** -------------------------- tetrimino.c functions ----------------------------
*/

t_point			*create_point(int x, int y);
t_tetri			*get_block(char *tetris, char c);
t_list			*free_all_tetri(t_list *lst_tetri);

/*
** --------------------------- solver.c functions ------------------------------
*/

t_map			*solve(t_list *lst);

#endif
