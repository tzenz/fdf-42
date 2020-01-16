/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 12:57:48 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/24 12:57:55 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		s_int(t_file *st, char **argv, int j, int n)
{
	char	**buf;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	st->s = (int **)ft_memalloc(sizeof(int *) * st->hight);
	while (i < st->hight)
	{
		st->s[i] = (int *)ft_memalloc(sizeof(int) * st->width);
		get_next_line(fd, &line);
		buf = ft_strsplit(line, ' ');
		while (buf[n])
			st->s[i][j++] = ft_atoi(buf[n++]);
		free(line);
		n = 0;
		j = 0;
		i++;
	}
	close(fd);
}

int			s_leght(char **argv)
{
	char	*line;
	int		lengt;
	int		fd;
	int		i;

	lengt = 0;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	while (line[i])
	{
		if (line[i] != ' ')
			lengt++;
		i++;
	}
	free(line);
	return (lengt);
}

void		s_hight(t_file *st, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		st->hight++;
		free(line);
	}
	close(fd);
	st->width = s_leght(argv);
	s_int(st, argv, 0, 0);
}
