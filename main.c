/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguret <bsiguret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:12:13 by bsiguret          #+#    #+#             */
/*   Updated: 2017/11/22 17:21:13 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int ac, char **av)
{
	t_map	*map;
	char	*tetris;
	t_list	*tetri_list;

	if (ac != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (0);
	}
	if ((tetris = read_file(open(av[1], O_RDONLY))) == NULL)
	{
		ft_putstr("error\n");
		return (0);
	}
	if (!is_filevalid(tetris))
	{
		ft_putstr("error\n");
		return (0);
	}
	tetri_list = get_tetri_list(tetris);
	map = solve(tetri_list);
	print_map(map);
	free_map(map);
	free_all_tetri(tetri_list);
	return (1);
}
