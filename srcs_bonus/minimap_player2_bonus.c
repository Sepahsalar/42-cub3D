/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:08:07 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	clean_player_image(t_all *all)
{
	t_player	*current;
	t_player	*next;

	current = all->player_image;
	while (current)
	{
		next = current->next;
		mlx_delete_image(all->window, current->image);
		free(current);
		current = next;
	}
}

static void	rotate_image_helper(int i, mlx_image_t *image,
	mlx_image_t *new_image, double angle)
{
	t_rotate	rotate;
	int			color_player;

	rotate.i = i;
	rotate.j = 0;
	while (rotate.j < (int)new_image->height)
	{
		rotate.new_x = (int)round(rotate.i - new_image->width / 2.0);
		rotate.new_y = (int)round(rotate.j - new_image->height / 2.0);
		rotate.x = (int)(round(rotate.new_x * ft_cos(-angle) - rotate.new_y
					* ft_sin(-angle)) + image->width / 2.0);
		rotate.y = (int)(round(rotate.new_x * ft_sin(-angle) + rotate.new_y
					* ft_cos(-angle)) + image->height / 2.0);
		if (rotate.x >= 0 && rotate.x < (int)image->width && rotate.y >= 0
			&& rotate.y < (int)image->height)
		{
			color_player = get_pixel(image, rotate.x, rotate.y);
			if (color_player)
				color_player = color(255, 0, 0, 255);
			mlx_put_pixel(new_image, rotate.i, rotate.j, color_player);
		}
		(rotate.j)++;
	}
}

mlx_image_t	*rotate_image(t_all *all, mlx_image_t *image, double angle)
{
	mlx_image_t	*new_image;
	int			i;

	new_image = mlx_new_image(all->window, image->width, image->height);
	i = 0;
	while (i < (int)new_image->width)
	{
		rotate_image_helper(i, image, new_image, angle);
		i++;
	}
	return (new_image);
}

static t_player	*create_player_image_node(t_all *all, double angle)
{
	t_player	*new;

	new = malloc(sizeof(t_player));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_player));
	new->image = rotate_image(all, all->player_at_0, angle);
	new->angle = angle;
	mlx_image_to_window(all->window, new->image, 0, 0);
	new->image->instances[0].z = 2;
	new->image->instances[0].enabled = 0;
	return (new);
}

void	create_player_image(t_all *all)
{
	t_player	*new;
	t_player	*old;
	double		angle;

	angle = 0.0;
	old = NULL;
	new = NULL;
	while (angle < FULL_CIRCLE_DEGREES)
	{
		new = create_player_image_node(all, angle);
		if (all->player_image == NULL)
			all->player_image = new;
		else
			old->next = new;
		if (!new)
			terminate(all, "Allocating memory failed", NULL, NULL);
		old = new;
		angle += TURN_INTERVAL;
	}
}
