/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/07 11:28:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// t_data *last_node_data(t_data *node)
// {
// 	if (!node)
// 		return (0);
// 	while (node->next)
// 		node = node->next;
// 	return (node);
// }

void strip_to_floor(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *base_image;
    mlx_image_t *new_image;
    // int         length;
    int         height;
    uint8_t     *pixel;
    int         int_color;
    int         i;
    t_data      *end_floor;
    t_data      *start_floor;
    t_data      *new;

    strip = all->strip;
    start_floor = all->display->floor;
    end_floor = last_node_data(all->display->floor);
    while(strip)
    {
        base_image = all->elems->f;
        height = WINDOW_HEIGHT - round(strip->ceil_h) - round(strip->wall_h);
        // length = 1;
        new_image = mlx_new_image(all->window, 1, height);
        if (!new_image)
            terminate(all, 1);
        pixel = base_image->pixels;
        int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
        i = 0;
        while (i < height)
        {
            mlx_put_pixel(new_image, 0, i, int_color);
            i++;
        }
        new = malloc(sizeof(t_data));
        if (!new)
            terminate(all, 1);
        new->image = new_image;
        new->x = strip->x;
        new->y = round(strip->ceil_h) + round(strip->wall_h);
        new->previous = 0;
        new->next = 0;
        if (!end_floor)
            start_floor = new;
        else
        {
            end_floor->next = new;
            new->previous = end_floor;
        }
        strip= strip->next;
        end_floor = new;
    }
    all->display->floor = start_floor;
}

