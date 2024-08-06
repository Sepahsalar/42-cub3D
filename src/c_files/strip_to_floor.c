/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/06 14:34:07 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
    int         length;
    int         height;
    // uint8_t     *pixel;
    // int         int_color;
    // int         i;
    t_data      *floor;
    t_data      *new;

    strip = all->strip;
    floor = last_node_data(all->display->floor);
    while(strip)
    {
        base_image = all->elems->f;
        height = WINDOW_HEIGHT - -round(strip->ceil_h) - round(strip->wall_h);
        length = 1;
        new_image = mlx_new_image(all->window, 1, height);
        if (!new_image)
            terminate(all, 1);
        if (!mlx_resize_image(base_image, length, height))
            terminate(all, 1);
        new = malloc(sizeof(t_data));
        if (!new)
            terminate(all, 1);
        new->image = new_image;
        new->x = strip->x;
        new->y = 0;
        new->previous = 0;
        new->next = 0;
        if (!floor)
            all->display->floor = new;
        else
        {
            floor->next = new;
            new->previous = floor;
        }
        strip= strip->next;
    }
}

