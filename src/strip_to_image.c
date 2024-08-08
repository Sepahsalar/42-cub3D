/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/08 11:40:12 by nnourine         ###   ########.fr       */
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
mlx_image_t *choose_brick(t_all *all, char wall)
{
	if (wall == 'N')
		return (all->north);
	else if (wall == 'W')
		return (all->west);
	else if (wall == 'S')
		return (all->south);
	else
		return (all->east);
}

// int dimension_resized_brick()


// void strip_to_image(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *brick;
//     mlx_image_t *final_image;
//     // int         length;
//     // int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     int         j;
//     int         i2;
//     int         j2;
// 	int			i3;
// 	int			j3;
//     int         h_brick;
//     int         w_brick;

//     final_image = mlx_new_image(all->window, WINDOW_WIDTH, WINDOW_HEIGHT);
//     if (!final_image)
//         terminate(all, 1);
//     strip = all->strip;
//     while (strip)
//     {
//         height = round(strip->wall_h);
//         length = strip->wall_length;
// 		brick = choose_brick(all, strip->wall);
// 		h_brick = round(height / BRICKS_IN_H);
//         w_brick = round(length * BRICKS_IN_H / WALL);
// 		// h_brick = round(height);
//         // w_brick = round(length/ WALL);
//         for (i = 0; i < WINDOW_HEIGHT; i++)
//         {
//             if (i <= (int)round(strip->ceil_h))
//                 int_color = all->ceil_color;
//             else if (i > (int)round(strip->ceil_h) && i < ((int)round(strip->ceil_h) + height))
//             {
//                 j = i - (int)round(strip->ceil_h);
//                 i2 = strip->index % w_brick;
//                 j2 = j % h_brick;
// 				i3 = round(i2 * brick->width / w_brick);
// 				j3 = round(j2 * brick->height / h_brick);
// 				pixel = brick->pixels + 4 * (i3 + j3 * brick->width);
//                 int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//             }
//             else
//                 int_color = all->floor_color;

//             if (strip->x >= 0 && strip->x < WINDOW_WIDTH)
//                 mlx_put_pixel(final_image, strip->x, i, int_color);
//         }
//         // mlx_delete_image(all->window, brick);
//         strip = strip->next;
//     }
//     mlx_image_to_window(all->window, final_image, 0, 0);
// }

int dimension_resized_brick(t_strip *strip, char type)
{
	if (type == 'h')
		return (round(strip->wall_h / BRICKS_IN_H));
	else
		return (round(strip->wall_length * BRICKS_IN_H / WALL));
}

int get_pixel(mlx_image_t *image, int i, int j)
{
	uint8_t *pixel;

	pixel = image->pixels + 4 * (i + j * image->width);
	return (color(pixel[0], pixel[1], pixel[2], pixel[3]));
}



int image_to_wall_height_change(t_strip *strip, int i)
{
	return (i - (int)round(strip->ceil_h));
}

// int image_to_wall_height_change(t_strip *strip, int j)
// {
// 	return (j - (int)round(strip->ceil_h));
// }

// int wall_to_resized_brick_dimension_change(t_strip *strip, int image_j, char type)
// {
// 	if (type == 'h')
// 		return (strip->index % dimension_resized_brick(strip, 'w'));
// 	else
// 		return (image_to_wall_height_change(strip, image_j) % dimension_resized_brick(strip, 'h'));
// }


void strip_to_image(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *brick;
    mlx_image_t *final_image;
    int         int_color;
    int         i;
    // int         j;
    int         i2;
    int         j2;
	int			i3;
	int			j3;
    int         h_resized_brick;
    int         w_resized_brick;

    final_image = mlx_new_image(all->window, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!final_image)
        terminate(all, 1);
    strip = all->strip;
    while (strip)
    {
		brick = choose_brick(all, strip->wall);
		h_resized_brick = dimension_resized_brick(strip, 'h');
		w_resized_brick = dimension_resized_brick(strip, 'w');
        for (i = 0; i < WINDOW_HEIGHT; i++)
        {
            if (i <= (int)round(strip->ceil_h))
                int_color = all->ceil_color;
            else if (i > (int)round(strip->ceil_h) && i < ((int)(round(strip->ceil_h) + round(strip->wall_h))))
            { 
				// j = image_to_wall_height_change(strip, i);
				i2 = strip->index % w_resized_brick;
				j2 = image_to_wall_height_change(strip, i) % h_resized_brick;
				i3 = round(i2 * brick->width / w_resized_brick);
				j3 = round(j2 * brick->height / h_resized_brick);
				int_color = get_pixel(brick, i3, j3);
            }
            else
                int_color = all->floor_color;

            if (strip->x >= 0 && strip->x < WINDOW_WIDTH)
                mlx_put_pixel(final_image, strip->x, i, int_color);
        }
        strip = strip->next;
    }
    mlx_image_to_window(all->window, final_image, 0, 0);
}



