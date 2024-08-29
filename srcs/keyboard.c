/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:34:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 12:27:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	key_press(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_W)
		move_press(param, 'W');
	else if (keydata.key == MLX_KEY_S)
		move_press(param, 'S');
	else if (keydata.key == MLX_KEY_A)
		move_press(param, 'A');
	else if (keydata.key == MLX_KEY_D)
		move_press(param, 'D');
	else if (keydata.key == MLX_KEY_SPACE)
		use_weapon(param);
	else if (keydata.key == MLX_KEY_LEFT)
		turn_press(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT)
		turn_press(param, 'R');
	else if (keydata.key == MLX_KEY_LEFT_SHIFT
		|| keydata.key == MLX_KEY_RIGHT_SHIFT)
		change_weapon(param);
	else if (keydata.key == MLX_KEY_ESCAPE)
		terminate((t_all *)param, NULL, NULL, NULL);
}

void	key_repeat(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_W)
		move_repeat(param, 'W');
	else if (keydata.key == MLX_KEY_S)
		move_repeat(param, 'S');
	else if (keydata.key == MLX_KEY_A)
		move_repeat(param, 'A');
	else if (keydata.key == MLX_KEY_D)
		move_repeat(param, 'D');
	else if (keydata.key == MLX_KEY_LEFT)
		turn_repeat(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT)
		turn_repeat(param, 'R');
}

void	key_release(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		all->started_button = 0;
}

void	keyboard(mlx_key_data_t keydata, void *param)
{
	if (keydata.action == MLX_PRESS)
		key_press(keydata, param);
	else if (keydata.action == MLX_REPEAT)
		key_repeat(keydata, param);
	else if (keydata.action == MLX_RELEASE)
		key_release(keydata, param);
}
