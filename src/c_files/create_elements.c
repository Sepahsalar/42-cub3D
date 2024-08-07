/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:45:45 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/07 10:10:04 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// static mlx_texture_t	*load_image(mlx_t *window, char c)
// {
// 	mlx_texture_t	*texture;

// 	if (c == '1')
// 		texture = mlx_load_png("./textures/wall.png");
// 	else if (c == 'P')
// 		texture = mlx_load_png("./textures/player.png");
// 	else if (c == 'C')
// 		texture = mlx_load_png("./textures/collectible.png");
// 	else
// 		texture = mlx_load_png("./textures/exit.png");
// 	if (!texture)
// 	{
// 		mlx_terminate(window);
// 		ft_exit("Loading PNG failed");
// 	}
// 	return (texture);
// }

// static mlx_image_t	*image(mlx_t *window, int i_width, int i_height, char c)
// {
// 	mlx_texture_t	*texture;
// 	mlx_image_t		*picture;

// 	texture = load_image(window, c);
// 	picture = mlx_texture_to_image(window, texture);
// 	if (!picture)
// 	{
// 		mlx_terminate(window);
// 		ft_exit("Creating image failed");
// 	}
// 	mlx_delete_texture(texture);
// 	if (!mlx_resize_image(picture, i_width, i_height))
// 	{
// 		mlx_terminate(window);
// 		ft_exit("Resizing pictures failed");
// 	}
// 	return (picture);
// }



// static mlx_image_t	*color_maker(t_all *all, char *str)
// {
// 	mlx_image_t	*image_color;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	j = 0;
// 	image_color = mlx_new_image(all->window, 1, 1);
// 	if (!image_color)
// 		terminate(all, 1);
// 	// while (i < w_width)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < w_height)
// 	// 	{
// 	// 		mlx_put_pixel(image_color, i, j, color(, 160, 170, 255));
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// 	mlx_put_pixel(image_color, 0, 0, color(ft_atoi(ft_split(str, ',')[0]),
// 			ft_atoi(ft_split(str, ',')[1]), ft_atoi(ft_split(str, ',')[2]), 255)); //free and protect split
// 	return (image_color);
// }

void image(t_all *all, char type)
{
	mlx_texture_t	*texture;
	mlx_image_t		*picture;
	char 			*address;

	
	if (type == 'E')
		address = all->map->east;
	else if (type == 'W')
		address = all->map->west;
	else if (type == 'S')
		address = all->map->south;
	else
		address = all->map->north;
	texture = mlx_load_png(address);
	if (!texture)
		terminate(all, 1);
	picture = mlx_texture_to_image(all->window, texture);
	mlx_delete_texture(texture);
	if (!picture)
		terminate(all, 1);
	if (type == 'E')
		all->elems->east = picture;
	else if (type == 'W')
		all->elems->west = picture;
	else if (type == 'S')
		all->elems->south = picture;
	else
		all->elems->north = picture;
}

mlx_image_t *image_maker(t_all *all, char type)
{
	mlx_texture_t	*texture;
	mlx_image_t		*picture;
	char 			*address;

	
	if (type == 'E')
		address = all->map->east;
	else if (type == 'W')
		address = all->map->west;
	else if (type == 'S')
		address = all->map->south;
	else
		address = all->map->north;
	texture = mlx_load_png(address);
	if (!texture)
		terminate(all, 1);
	picture = mlx_texture_to_image(all->window, texture);
	mlx_delete_texture(texture);
	if (!picture)
		terminate(all, 1);
	return (picture);
}

int	color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void clean_2d_char_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	color_pixel(t_all *all, char type)
{
	mlx_image_t	*image_color;
	char		*full_color;
	char		**split;
	int			int_color;

	if (type == 'f')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	// //printf("full_color: %s\n", full_color);
	image_color = mlx_new_image(all->window, 1, 1);
	if (!image_color)
		terminate(all, 1);
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	int_color = color(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	mlx_put_pixel(image_color, 0, 0, int_color);
	clean_2d_char_array(split);
	if (type == 'f')
		all->elems->f = image_color;
	else
		all->elems->c = image_color;
}

void	create_elements(t_all *all)
{
	t_elem	*elements;

	elements = malloc(sizeof(t_elem));
	if (!elements)
		terminate(all, 1);
	all->elems = elements;
	color_pixel(all, 'f');
	color_pixel(all, 'c');
	//printf("floor height: %d and width: %d\n", all->elems->f->height, all->elems->f->width);
	//printf("ceil height: %d and width: %d\n", all->elems->c->height, all->elems->c->width);
	image(all, 'N');
	image(all, 'S');
	image(all, 'W');
	image(all, 'E');
}
