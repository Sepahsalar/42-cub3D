/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/06 20:26:13 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_data  *last_node_data(t_data *node)
{
	if (!node)
		return (0);
	while (node && node->next)
		node = node->next;
    return (node);
    // tmp = node;
    // while (node)
    // {
    //     tmp = node;
    //     node = node->next;
    // }
	// return (tmp);
}

// void strip_to_wall(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *base_image;
//     mlx_image_t *new_image;
//     int         length;
//     int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     t_data      *wall;
//     t_data      *new;
//     int         original_height;
//     int         original_width;

//     strip = all->strip;
//     wall = last_node_data(all->display->wall);
//     while(strip)
//     {
//         if (strip->wall == 'E')
//             base_image = all->elems->east;
//         else if (strip->wall == 'W')
//             base_image = all->elems->west;
//         else if (strip->wall == 'N')
//             base_image = all->elems->north;
//         else
//             base_image = all->elems->south;
//         height = round(strip->wall_h);
//         length = strip->wall_length;
//         new_image = mlx_new_image(all->window, 1, height);
//         if (!new_image)
//             terminate(all, 1);
//         original_height = base_image->height;
//         original_width = base_image->width;
//         if (!mlx_resize_image(base_image, length, height))
//             terminate(all, 1);
//         i = 0;
//         while (i < height)
//         {
//             pixel = base_image->pixels + 4*(i * length + strip->index);
//             // pixel = base_image->pixels + i;
//             int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//             mlx_put_pixel(new_image, 0, i, int_color);
//             i++;
//         }
//         if (!mlx_resize_image(base_image, original_width, original_height))
//             terminate(all, 1);
//         new = malloc(sizeof(t_data));
//         if (!new)
//             terminate(all, 1);
//         new->image = new_image;
//         new->x = strip->x;
//         new->y = round(strip->ceil_h);
//         new->previous = 0;
//         new->next = 0;
//         if (!wall)
//             all->display->wall = new;
//         else
//         {
//             wall->next = new;
//             new->previous = wall;
//         }
//         strip= strip->next;
//         wall = new;
//     }
// }

// 

void strip_to_wall(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *brick;
	mlx_image_t *wall_before_resize;
	mlx_image_t *real_wall;
	int brick_in_width;
	int wall_br_height;
	int wall_br_width;
    mlx_image_t *new_image;
    int         length;
    int         height;
    uint8_t     *pixel;
    int         int_color;
    int         i;
    int j;
    t_data      *wall;
    t_data      *new;
    // int         original_height;
    // int         original_width;
    // mlx_image_t *built;
    int         i2;
    int         j2;
    // double      ratio;
    
    // char type;

    strip = all->strip;
    wall = last_node_data(all->display->wall);
    while(strip)
    {
        // if (strip->wall == 'E')
        //     type = 'e';
        // else if (strip->wall == 'W')
        //     type = 'w';
        // else if (strip->wall == 'N')
        //     type = 'n';
        // else
        //     type = 's';
        brick = image_maker(all, strip->wall);
		if (!mlx_resize_image(brick, BRICKS_WIDTH, BRICKS_HEIGHT))
            terminate(all, 1);
		wall_br_height = BRICKS_IN_H * BRICKS_HEIGHT;
		brick_in_width = floor(strip->wall_length/WALL) * BRICKS_IN_H;
		wall_br_width = brick_in_width * BRICKS_WIDTH;
		wall_before_resize = mlx_new_image(all->window, wall_br_width, wall_br_height);
		i = 0;
        j = 0;
        while (i < wall_br_width)
        {
            j = 0;
            while (j < wall_br_height)
            {
                i2 = i % BRICKS_WIDTH;
                j2 = j % BRICKS_HEIGHT;
                pixel = brick->pixels + 4*(i2 + j2 * BRICKS_WIDTH);
                int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
                mlx_put_pixel(wall_before_resize, i, j, int_color);
                j++;
            }
            i++;
        }
		
        height = round(strip->wall_h);
        length = strip->wall_length;
		if (!mlx_resize_image(wall_before_resize, length, height))
            terminate(all, 1);
		// if (!mlx_resize_image(wall_before_resize, 10, 10))
        //     terminate(all, 1);
		real_wall = wall_before_resize;
		new_image = mlx_new_image(all->window, 1, height);
        if (!new_image)
            terminate(all, 1);
        i = 0;
        while (i < height)
        {
            pixel = real_wall->pixels + 4*(i * length + strip->index);
            int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
            mlx_put_pixel(new_image, 0, i, int_color);
            i++;
        }
        mlx_delete_image(all->window, brick);
        mlx_delete_image(all->window, wall_before_resize);
        new = malloc(sizeof(t_data));
        if (!new)
            terminate(all, 1);
        new->image = new_image;
        new->x = strip->x;
        new->y = round(strip->ceil_h);
        new->previous = 0;
        new->next = 0;
        if (!wall)
            all->display->wall = new;
        else
        {
            wall->next = new;
            new->previous = wall;
        }
        strip= strip->next;
        wall = new;
    }
}

