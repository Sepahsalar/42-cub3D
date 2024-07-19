/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:03:31 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/05 15:16:07 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ft_move_up(void *param)
{
	mlx_image_t			*player;
	mlx_image_t			*collectible;
	mlx_t				*mlx;
	int					*movement_count;
	t_elements_count	elements_count;

	mlx = ((t_window_elements *) param)->window;
	player = (((t_window_elements *) param)->elements)->player;
	collectible = (((t_window_elements *) param)->elements)->collectible;
	movement_count = (((t_window_elements *) param))->movement_count;
	elements_count = (((t_window_elements *) param))->elements_count;
	if (ft_check_near_wall(((t_window_elements *) param), 'U'))
	{
		*movement_count = *movement_count + 1;
		ft_printf("Movement Count:%d\n", *movement_count);
		player->instances[0].y -= player->height;
		(*(((t_window_elements *) param)->elements)
				->player_collectible).player_position.y += -1;
		ft_check_reach_to_collectible(((t_window_elements *) param));
		ft_check_exit(((t_window_elements *) param));
	}
}

void	ft_move_down(void *param)
{
	mlx_image_t			*player;
	mlx_image_t			*collectible;
	mlx_t				*mlx;
	int					*movement_count;
	t_elements_count	elements_count;

	mlx = ((t_window_elements *) param)->window;
	player = (((t_window_elements *) param)->elements)->player;
	collectible = (((t_window_elements *) param)->elements)->collectible;
	movement_count = (((t_window_elements *) param))->movement_count;
	elements_count = (((t_window_elements *) param))->elements_count;
	if (ft_check_near_wall(((t_window_elements *) param), 'D'))
	{
		*movement_count = *movement_count + 1;
		ft_printf("Movement Count:%d\n", *movement_count);
		player->instances[0].y += player->height;
		(*(((t_window_elements *) param)->elements)
				->player_collectible).player_position.y += +1;
		ft_check_reach_to_collectible(((t_window_elements *) param));
		ft_check_exit(((t_window_elements *) param));
	}
}

void	ft_move_right(void *param)
{
	mlx_image_t			*player;
	mlx_image_t			*collectible;
	mlx_t				*mlx;
	int					*movement_count;
	t_elements_count	elements_count;

	mlx = ((t_window_elements *) param)->window;
	player = (((t_window_elements *) param)->elements)->player;
	collectible = (((t_window_elements *) param)->elements)->collectible;
	movement_count = (((t_window_elements *) param))->movement_count;
	elements_count = (((t_window_elements *) param))->elements_count;
	if (ft_check_near_wall(((t_window_elements *) param), 'R'))
	{
		*movement_count = *movement_count + 1;
		ft_printf("Movement Count:%d\n", *movement_count);
		player->instances[0].x += player->width;
		(*(((t_window_elements *) param)->elements)
				->player_collectible).player_position.x += +1;
		ft_check_reach_to_collectible(((t_window_elements *) param));
		ft_check_exit(((t_window_elements *) param));
	}
}

void	ft_move_left(void *param)
{
	mlx_image_t			*player;
	mlx_image_t			*collectible;
	mlx_t				*mlx;
	int					*movement_count;
	t_elements_count	elements_count;

	mlx = ((t_window_elements *) param)->window;
	player = (((t_window_elements *) param)->elements)->player;
	collectible = (((t_window_elements *) param)->elements)->collectible;
	movement_count = (((t_window_elements *) param))->movement_count;
	elements_count = (((t_window_elements *) param))->elements_count;
	if (ft_check_near_wall(((t_window_elements *) param), 'L'))
	{
		*movement_count = *movement_count + 1;
		ft_printf("Movement Count:%d\n", *movement_count);
		player->instances[0].x -= player->width;
		(*(((t_window_elements *) param)->elements)
				->player_collectible).player_position.x += -1;
		ft_check_reach_to_collectible(((t_window_elements *) param));
		ft_check_exit(((t_window_elements *) param));
	}
}

void	ft_press_key(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		ft_move_up(param);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		ft_move_down(param);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_move_right(param);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_move_left(param);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_escape_key(param);
}
