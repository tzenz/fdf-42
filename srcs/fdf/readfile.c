/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 12:57:48 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/01 17:13:16 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		freebuf(char **buf, t_file *st)
{
	int		n;

	n = 0;
	while (buf[n])
	{
		free(buf[n]);
		buf[n++] = NULL;
	}
	free(buf);
	buf = NULL;
	if (n != st->width)
	{
		ft_putstr("incorrect MAP_FILE\n");
		exit(0);
	}
}

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
		freebuf(buf, st);
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
		if (ft_isdigit(line[i]))
		{
			lengt++;
			while (ft_isdigit(line[i + 1]))
				i++;
		}
		i++;
	}
	free(line);
	return (lengt);
}

void		fd_check(char *argv)
{
	int		i;
	int		r;
	char	*point;

	i = 0;
	r = 0;
	point = NULL;
	while (argv[i])
	{
		if (argv[i] == '.')
		{
			r = 1;
			if (!(point = ft_strstr(&argv[i], "fdf")))
				r = -1;
		}
		i++;
	}
	if (r != 1 || (point && point[3]))
	{
		ft_putstr("incorrect MAP_FILE\n");
		exit(0);
	}
}

void		readfile(t_file *st, char **argv)
{
	char	*line;
	char	buf[10];
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0 || (read(fd, buf, 5)) <= 0)
	{
		ft_putstr("incorrect MAP_FILE\n");
		exit(0);
	}
	fd_check(argv[1]);
	while (get_next_line(fd, &line))
	{
		st->hight++;
		free(line);
	}
	close(fd);
	st->width = s_leght(argv);
	s_int(st, argv, 0, 0);
}
