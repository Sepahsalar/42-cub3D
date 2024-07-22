/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_side_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:43:33 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_check_char_wall(char buffer, int fd_map)
{
	if (buffer != '1')
	{
		close(fd_map);
		ft_exit_failure(0, 0, "The map is not surrounded by walls");
	}
}

void	ft_check_first_line_wall(char *map)
{
	int		fd_map;
	char	buffer;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
	{
		if (buffer == '\n')
			break ;
		ft_check_char_wall(buffer, fd_map);
	}
	close(fd_map);
}

void	ft_check_last_line_wall(char *map)
{
	int		fd_map;
	int		height;
	int		line_num;
	char	buffer;

	height = ft_hight_counter(map);
	line_num = 1;
	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
	{
		if (line_num == height)
		{
			while (read(fd_map, &buffer, 1))
				ft_check_char_wall(buffer, fd_map);
			break ;
		}
		else if (buffer == '\n')
			line_num++;
	}
	close(fd_map);
}

void	ft_check_left_side_wall(char *map)
{
	int		fd_map;
	int		triger;
	char	buffer;

	triger = 1;
	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
	{
		if (triger == 1)
		{
			ft_check_char_wall(buffer, fd_map);
			triger = 0;
		}
		if (buffer == '\n')
			triger = 1;
	}
	close(fd_map);
}

void	ft_check_right_side_wall(char *map)
{
	int		fd_map;
	char	buffer;
	char	temp;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	temp = '\0';
	while (read(fd_map, &buffer, 1))
	{
		if (buffer == '\n')
			ft_check_char_wall(temp, fd_map);
		temp = buffer;
	}
	ft_check_char_wall(temp, fd_map);
	close(fd_map);
}
