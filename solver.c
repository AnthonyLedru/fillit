/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thebigbacktrack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguret <bsiguret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:49:13 by bsiguret          #+#    #+#             */
/*   Updated: 2017/11/22 17:31:01 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		back_track(t_map *map, t_list *lst)
{
	int		i;
	int		j;
	t_tetri	*tetri;

	if (lst == NULL)
		return (1);
	j = 0;
	tetri = (t_tetri*)(lst->content);
	while (j < map->size - tetri->height + 1)
	{
		i = 0;
		while (i < map->size - tetri->width + 1)
		{
			if (place_tetri(map, tetri, i, j))
			{
				if (back_track(map, lst->next))
					return (1);
				else
					setchar_tetri(map, tetri, create_point(i, j), '.');
			}
			i++;
		}
		j++;
	}
	return (0);
}

t_map	*solve(t_list *lst)
{
	t_map	*map;
	int		size;

	size = 2;
	while (size * size < list_count(lst) * 4)
		size++;
	map = create_map(size);
	while (!back_track(map, lst))
	{
		size++;
		free_map(map);
		map = create_map(size);
	}
	return (map);
}
