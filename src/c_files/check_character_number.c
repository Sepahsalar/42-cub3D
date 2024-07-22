/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_character_number.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:34:48 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_check_each_char(char c)
{
	if (c == '0')
		return (1);
	if (c == '1')
		return (1);
	if (c == 'C')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'P')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

void	ft_check_all_char(char *map)
{
	int		fd_map;
	char	buffer;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
	{
		if (!ft_check_each_char(buffer))
		{
			close(fd_map);
			ft_exit_failure(0, 0, "Wrong characters");
		}
	}
	close(fd_map);
}

void	ft_check_one_exit(char *map)
{
	int		fd_map;
	char	buffer;
	int		counter;

	counter = 0;
	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
		if (buffer == 'E')
			counter++;
	close(fd_map);
	if (counter != 1)
		ft_exit_failure(0, 0, "Wrong number of exit");
}

void	ft_check_one_starting_position(char *map)
{
	int		fd_map;
	char	buffer;
	int		counter;

	counter = 0;
	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
		if (buffer == 'P')
			counter++;
	close(fd_map);
	if (counter != 1)
		ft_exit_failure(0, 0, "Wrong number of starting position");
}

void	ft_check_one_collectible(char *map)
{
	int		fd_map;
	char	buffer;
	int		counter;

	counter = 0;
	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	while (read(fd_map, &buffer, 1))
		if (buffer == 'C')
			counter++;
	close(fd_map);
	if (counter == 0)
		ft_exit_failure(0, 0, "No collectible");
}
