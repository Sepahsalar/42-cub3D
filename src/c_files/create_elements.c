/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:45:45 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/24 16:01:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static mlx_texture_t	*load_image(mlx_t *window, char c)
{
	mlx_texture_t	*texture;

	if (c == '1')
		texture = mlx_load_png("./textures/wall.png");
	else if (c == 'P')
		texture = mlx_load_png("./textures/player.png");
	else if (c == 'C')
		texture = mlx_load_png("./textures/collectible.png");
	else
		texture = mlx_load_png("./textures/exit.png");
	if (!texture)
	{
		mlx_terminate(window);
		ft_exit("Loading PNG failed");
	}
	return (texture);
}

static mlx_image_t	*image(mlx_t *window, int i_width, int i_height, char c)
{
	mlx_texture_t	*texture;
	mlx_image_t		*picture;

	texture = load_image(window, c);
	picture = mlx_texture_to_image(window, texture);
	if (!picture)
	{
		mlx_terminate(window);
		ft_exit("Creating image failed");
	}
	mlx_delete_texture(texture);
	if (!mlx_resize_image(picture, i_width, i_height))
	{
		mlx_terminate(window);
		ft_exit("Resizing pictures failed");
	}
	return (picture);
}

static int	color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static mlx_image_t	*color_maker(t_all *all, char *str)
{
	mlx_image_t	*image_color;
	int			i;
	int			j;

	i = 0;
	j = 0;
	image_color = mlx_new_image(all->window, 1, 1);
	if (!image_color)
		terminate(all, 1);
	// while (i < w_width)
	// {
	// 	j = 0;
	// 	while (j < w_height)
	// 	{
	// 		mlx_put_pixel(image_color, i, j, color(, 160, 170, 255));
	// 		j++;
	// 	}
	// 	i++;
	// }
	mlx_put_pixel(image_color, 0, 0, color(ft_atoi(ft_split(str, ',')[0]), ft_atoi(ft_split(str, ',')[1]), ft_atoi(ft_split(str, ',')[2]), 255));
	return (image_color);
}

t_elem	*create_elements(t_all *all)
{
	t_elem	*elements;

	elements = malloc(sizeof(t_elem));
	// if (!elements)
	// {
	// 	mlx_terminate(window);
	// 	ft_exit("Allocating memory for elements failed");
	// }
	// elements->collect_loc = collectible_list(argv, 0);
	// if (!elements->collect_loc)
	// {
	// 	free(elements);
	// 	mlx_terminate(window);
	// 	ft_exit("Creating collectible list failed");
	// }
	elements->f = background(all, all->map->f);
	elements->c = background(all, all->map->c);
	elements->wall = image(window, map->image_width, map->image_height, '1');
	elements->player = image(window, map->image_width, map->image_height, 'P');
	elements->collect = image(window, map->image_width, map->image_height, 'C');
	elements->exit = image(window, map->image_width, map->image_height, 'E');
	return (elements);
}
