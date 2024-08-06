/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/06 19:10:16 by asohrabi         ###   ########.fr       */
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

void strip_to_wall(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *base_image;
    mlx_image_t *new_image;
    int         length;
    int         height;
    uint8_t     *pixel;
    int         int_color;
    int         i;
    int j;
    t_data      *wall;
    t_data      *new;
    int         original_height;
    int         original_width;
    mlx_image_t *built;
    int         i2;
    int         j2;
    double      ratio;
    
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
        base_image = image_maker(all, strip->wall);
        height = round(strip->wall_h);
        length = strip->wall_length;
        new_image = mlx_new_image(all->window, 1, height);
        if (!new_image)
            terminate(all, 1);
        ratio = strip->wall_h / WALL;
        int int_ratio = floor(70 * ratio); 
        if (!mlx_resize_image(base_image, int_ratio, int_ratio))
            terminate(all, 1);
        original_height = base_image->height;
        original_width = base_image->width;
        built = mlx_new_image(all->window, length, height);
        i = 0;
        j = 0;
        while (i < length)
        {
            j = 0;
            while (j < height)
            {
                // pixel = base_image->pixels + 4*(i * length + strip->index);
                i2 = i%original_width;
                j2 = j%original_height;
                pixel = base_image->pixels + 4*(i2 + j2 * original_width);
                int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
                mlx_put_pixel(built, i, j, int_color);
                j++;
            }
            i++;
        }
        
        // if (!mlx_resize_image(base_image, length, height))
        //     terminate(all, 1);
        i = 0;
        while (i < height)
        {
            pixel = built->pixels + 4*(i * length + strip->index);
            // pixel = base_image->pixels + i;
            int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
            mlx_put_pixel(new_image, 0, i, int_color);
            i++;
        }
        mlx_delete_image(all->window, base_image);
        mlx_delete_image(all->window, built);
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

