/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rectangular.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:40:25 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/07 12:40:26 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_read_data	ft_read_line(int fd_map)
{
	t_read_data	read_data;

	read_data.buffer = '\0';
	read_data.counter = 0;
	read_data.read = read(fd_map, &(read_data.buffer), 1);
	while (read_data.read)
	{
		if (read_data.buffer == '\n')
			return (read_data);
		else
			read_data.counter++;
		read_data.read = read(fd_map, &(read_data.buffer), 1);
	}
	return (read_data);
}

void	ft_check_rectangular(char *map)
{
	int				fd_map;
	t_read_data		line1;
	t_read_data		next_line;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	line1 = ft_read_line(fd_map);
	next_line = ft_read_line(fd_map);
	while (next_line.read)
	{
		if (next_line.counter != line1.counter)
		{
			close(fd_map);
			ft_exit_failure(0, 0, "Map is not rectangular");
		}
		next_line = ft_read_line(fd_map);
	}
	close(fd_map);
	if (next_line.counter != line1.counter)
		ft_exit_failure(0, 0, "Map is not rectangular");
}
