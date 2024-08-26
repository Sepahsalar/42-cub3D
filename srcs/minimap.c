/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 19:25:50 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 14:10:09 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_there_a_wall(t_all *all, int x, int y)
{
	int		x_minimap_to_loc;
	int		y_minimap_to_loc;
	t_loc	*loc;

	x_minimap_to_loc = all->x - 0.5 - MINIMAP_COVERAGE / 2
			+ (x + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE)))
			/ (MINIMAP_SIDE / MINIMAP_COVERAGE);
	y_minimap_to_loc = all->y - 0.5 - MINIMAP_COVERAGE / 2
			+ (y + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE)))
			/ (MINIMAP_SIDE / MINIMAP_COVERAGE);
	loc = all->map->start;
	while (loc)
	{
		if (loc->x == x_minimap_to_loc && loc->y == y_minimap_to_loc)
			return (1);
		loc = loc->next;
	}
	return (0);
}

void	create_minimap(t_all *all)
{
	int	int_color_wall;
	int	int_color_floor;
	int	i;
	int	j;

	all->minimap = mlx_new_image(all->window, MINIMAP_SIDE, MINIMAP_SIDE);
	int_color_wall = color(0, 0, 0, 255);
	int_color_floor = color(255, 255, 255, 150);
	i = 0;
	while (i < (int)all->minimap->width)
	{
		j = 0;
		while (j < (int)all->minimap->height)
		{
			if (is_there_a_wall(all, i, j))
				mlx_put_pixel(all->minimap, i, j, int_color_wall);
			else
				mlx_put_pixel(all->minimap, i, j, int_color_floor);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->window, all->minimap,
			MINIMAP_PADDING, MINIMAP_PADDING);
	all->minimap->instances[0].z = 1;
}

mlx_image_t	*rotate_image(t_all *all, mlx_image_t *image, double angle)
{
	mlx_image_t	*new_image;
	t_rotate	rotate;
	int			color_player;

	new_image = mlx_new_image(all->window, image->width, image->height);
	rotate.i = 0;
	while (rotate.i < (int)new_image->width)
	{
		rotate.j = 0;
		while (rotate.j < (int)new_image->height)
		{
			rotate.new_x = (int)round(rotate.i - new_image->width / 2.0);
			rotate.new_y = (int)round(rotate.j - new_image->height / 2.0);
			rotate.x = (int)(round(rotate.new_x * ft_cos(-angle)
						- rotate.new_y * ft_sin(-angle)) + image->width / 2.0);
			rotate.y = (int)(round(rotate.new_x * ft_sin(-angle)
						+ rotate.new_y * ft_cos(-angle)) + image->height / 2.0);
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
		(rotate.i)++;
	}
	return (new_image);
}

t_player	*create_player_image_node(t_all *all, double angle)
{
	t_player	*new;

	new = malloc(sizeof(t_player));
	if (!new)
		return (NULL);
	new->image = rotate_image(all, all->player_at_0, angle);
	new->angle = angle;
	mlx_image_to_window(all->window, new->image, 0, 0);
	new->image->instances[0].z = 2;
	new->image->instances[0].enabled = 0;
	new->next = 0;
	return (new);
}

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

void	enable_correct_player(t_all *all)
{
	t_player	*current;

	current = all->player_image;
	while (current)
	{
		if (current->image->instances[0].enabled == 1)
		{
			current->image->instances[0].enabled = 0;
			break ;
		}
		current = current->next;
	}
	current = all->player_image;
	while (current)
	{
		if (same(current->angle, all->angle))
		{
			current->image->instances[0].x = MINIMAP_SIDE / 2 + MINIMAP_PADDING - current->image->width / 2;
			current->image->instances[0].y = MINIMAP_SIDE / 2 + MINIMAP_PADDING - current->image->height / 2;
			current->image->instances[0].enabled = 1;
			break ;
		}
		current = current->next;
	}
}
