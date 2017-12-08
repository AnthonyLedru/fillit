/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledru <aledru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:24:54 by aledru            #+#    #+#             */
/*   Updated: 2017/11/22 17:34:03 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Create an element of type t_tetri and assign value to attributes.
*/

t_tetri		*create_tetri(char **pos, int height, int width, char letter)
{
	t_tetri *tetris;

	if ((tetris = ft_memalloc(sizeof(t_tetri))) == NULL)
		return (NULL);
	tetris->pos = pos;
	tetris->height = height;
	tetris->width = width;
	tetris->letter = letter;
	return (tetris);
}

/*
** Create an element of type t_point and assign value to attributes.
*/

t_point		*create_point(int x, int y)
{
	t_point *point;

	if ((point = ft_memalloc(sizeof(t_point))) == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

/*
** Store the min (x, y) and max (y, x) relative to the char '#' into a point
** struct.
*/

void		get_min_and_max(char *tetri, t_point *min, t_point *max)
{
	int	i;

	i = 0;
	while (i < 19)
	{
		if (tetri[i] == '#')
		{
			if (min->x > i % 5)
				min->x = i % 5;
			if (min->y > i / 5)
				min->y = i / 5;
			if (max->x < i % 5)
				max->x = i % 5;
			if (max->y < i / 5)
				max->y = i / 5;
		}
		i++;
	}
}

/*
** Create a struct tetrimino (t_tetri) with the char given in parameter.
*/

t_tetri		*get_block(char *tetri, char c)
{
	t_point	*min;
	t_point	*max;
	char	**pos;
	int		i;
	t_tetri	*tetri_content;

	i = 0;
	min = create_point(3, 3);
	max = create_point(0, 0);
	get_min_and_max(tetri, min, max);
	pos = ft_memalloc(sizeof(char*) * (max->y - min->y) + 1);
	while (i < max->y - min->y + 1)
	{
		pos[i] = ft_strnew((max->x - min->x) + 1);
		ft_memcpy(pos[i], &tetri[min->x + (i + min->y) * 5],
					(max->x - min->x) + 1);
		i++;
	}
	tetri_content = create_tetri(pos, (max->y - min->y) + 1,
									(max->x - min->x + 1), c);
	ft_memdel((void**)&min);
	ft_memdel((void**)&max);
	return (tetri_content);
}

/*
** Free all the tetriminos and their contents
*/

t_list		*free_all_tetri(t_list *lst_tetri)
{
	t_tetri		*tetri;
	t_list		*next;
	int			i;

	i = 0;
	while (lst_tetri)
	{
		tetri = (t_tetri*)lst_tetri->content;
		next = lst_tetri->next;
		while (i < tetri->height)
		{
			ft_memdel((void**)(&(tetri->pos[i])));
			i++;
		}
		ft_memdel((void**)&lst_tetri);
		lst_tetri = next;
	}
	return (NULL);
}
