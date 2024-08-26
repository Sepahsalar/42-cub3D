/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:30:20 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 11:07:29 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	click(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		use_weapon(param);
	else if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		change_weapon(param);
}

void	mouse(double xpos, double ypos, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	(void)ypos;
	if (xpos > all->x_mouse)
		turn_repeat(param, 'R');
	else if (xpos < all->x_mouse)
		turn_repeat(param, 'L');
	all->x_mouse = xpos;
}

void	scroll(double xpos, double ypos, void *param)
{
	(void)xpos;
	if (ypos > 0)
		move_repeat(param, 'W');
	else if (ypos < 0)
		move_repeat(param, 'S');
}
