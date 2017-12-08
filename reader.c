/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledru <aledru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 18:59:47 by aledru            #+#    #+#             */
/*   Updated: 2017/11/29 11:16:55 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Check if the tetri is valid by checking if each '#' has an other adjacent
** '#' and if the total number of connections are equals to 8 or 6.
*/

int		is_validpiece(char *tetris)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (i <= 19)
	{
		if (tetris[i] == '#')
		{
			if (i - 1 >= 0 && tetris[i - 1] == '#')
				count++;
			if (i + 1 <= 19 && tetris[i + 1] == '#')
				count++;
			if (i + 5 <= 19 && tetris[i + 5] == '#')
				count++;
			if (i - 5 >= 0 && tetris[i - 5] == '#')
				count++;
		}
		i++;
	}
	if (count == 8)
		return (1);
	if (count == 6)
		return (1);
	return (0);
}

/*
** Check if the tetri block is valid :
** Contains only '.' and '#' (max 4).
** Tetri is 4x4
** Line separated with \n.
** Block is separated with \n with the next (if there is).
*/

int		is_blockvalid(char *tetris)
{
	int	i;
	int	hash;

	i = 0;
	hash = 0;
	while ((tetris[i] == '.' || tetris[i] == '#' || tetris[i] == '\n') &&
			hash < 5 && tetris[i])
	{
		if (i == 20)
			break ;
		if ((i + 1 % 5 == 0) && tetris[i] != '\n' && i != 0)
			return (0);
		if (tetris[i] == '#')
			hash++;
		i++;
	}
	if (hash == 4 && is_validpiece(tetris))
	{
		if (((tetris[i] == '\n' && tetris[i - 1] == '\n') || tetris[i] == '\0')
				&& hash == 4 && i == 20)
			return (1);
	}
	return (0);
}

/*
** Check if file is valid :
** Loop on file content, check if each block is valid and add blocks to list.
*/

int		is_filevalid(char *tetris)
{
	int		i;

	i = 0;
	if (tetris == NULL || tetris[0] == '\0')
		return (0);
	while (tetris[i])
	{
		if (i >= 546)
			return (0);
		if (is_blockvalid(&tetris[i]) == 0)
			return (0);
		i += 19;
		if (tetris[i + 1] && tetris[i + 2] == '\0')
			return (0);
		if (tetris[i + 1] == '\n')
			i += 2;
		else
			break ;
	}
	return (1);
}

/*
** Add each tetrimino to the chained list and reverse the final list to get
** the first link.
*/

t_list	*get_tetri_list(char *tetris)
{
	int		i;
	char	c;
	t_list	*tetri_list;
	t_tetri *tetri;

	tetri_list = NULL;
	tetri = NULL;
	c = 'A';
	i = 0;
	while (tetris[i])
	{
		tetri = get_block(&tetris[i], c);
		ft_list_add(&tetri_list, ft_list_new(tetri, sizeof(t_tetri)));
		i += 19;
		if (tetris[i + 1] == '\n')
			i += 2;
		else
			break ;
		c++;
	}
	ft_list_rev(&tetri_list);
	return (tetri_list);
}

/*
** Read the file with the given file descriptor and return the content of it.
*/

char	*read_file(int fd)
{
	char	*tetris;
	char	*buffer;
	int		fr;

	buffer = ft_strnew(20);
	if ((fd < 0 || read(fd, buffer, 0) < 0))
		return (NULL);
	tetris = (char*)ft_memalloc(sizeof(char));
	while ((fr = read(fd, buffer, 20)))
	{
		buffer[fr] = '\0';
		tetris = ft_strjoin(tetris, buffer);
		if (ft_strlen(tetris) > 570)
			return (NULL);
	}
	ft_memdel((void**)&buffer);
	tetris = ft_strjoin(tetris, "\0");
	return (tetris);
}
