/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:51:48 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_player_position_x(char *map)
{
	int		fd_map;
	int		player_position_x;
	char	buffer_read;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	player_position_x = 0;
	while (read(fd_map, &buffer_read, 1))
	{
		if (buffer_read == 'P')
			break ;
		else if (buffer_read == '\n')
			player_position_x = 0 ;
		else
			player_position_x++;
	}
	close(fd_map);
	return (player_position_x);
}

int	ft_player_position_y(char *map)
{
	int		fd_map;
	int		player_position_y;
	char	buffer_read;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	player_position_y = 0;
	while (read(fd_map, &buffer_read, 1))
	{
		if (buffer_read == 'P')
			break ;
		else if (buffer_read == '\n')
			player_position_y++;
	}
	close(fd_map);
	return (player_position_y);
}

t_player_position	ft_player_position(char *map)
{
	t_player_position	player_position;

	player_position.x = ft_player_position_x(map);
	player_position.y = ft_player_position_y(map);
	return (player_position);
}
