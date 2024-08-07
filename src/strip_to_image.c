/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/07 16:29:50 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

int	color_maker(t_all *all, char type)
{
	char	*full_color;
	char	**split;
	int		int_color;

	if (type == 'f')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	int_color = color(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	clean_2d_char_array(split);
	return (int_color);
}

void strip_to_image(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *brick;
    mlx_image_t *final_image;
    int         length;
    int         height;
    uint8_t     *pixel;
    int         int_color;
    int         i;
    int         j;
    int         i2;
    int         j2;
    int         h_brick;
    int         w_brick;

    final_image = mlx_new_image(all->window, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!final_image)
        terminate(all, 1);
    strip = all->strip;
    while (strip)
    {
        height = round(strip->wall_h);
        length = strip->wall_length;
        brick = image_maker(all, strip->wall);
        if (!brick)
            terminate(all, 1);
        h_brick = round(height / BRICKS_IN_H);
        w_brick = round(length * BRICKS_IN_H / WALL);
        if (!mlx_resize_image(brick, w_brick, h_brick))
            terminate(all, 1);
        for (i = 0; i < WINDOW_HEIGHT; i++)
        {
            if (i <= (int)round(strip->ceil_h))
                int_color = all->ceil_color;
            else if (i > (int)round(strip->ceil_h) && i < ((int)round(strip->ceil_h) + height))
            {
                j = i - (int)round(strip->ceil_h);
                i2 = strip->index % w_brick;
                j2 = j % h_brick;
                pixel = brick->pixels + 4 * (i2 + j2 * w_brick);
                int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
            }
            else
                int_color = all->floor_color;

            if (strip->x >= 0 && strip->x < WINDOW_WIDTH)
                mlx_put_pixel(final_image, strip->x, i, int_color);
        }
        mlx_delete_image(all->window, brick);
        strip = strip->next;
    }
    mlx_image_to_window(all->window, final_image, 0, 0);
}


