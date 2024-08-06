/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_instance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:17:35 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/06 16:13:18 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void load_image(t_all *all, char type)
{
    t_data *data;
    if (type == 'w')
        data = all->display->wall;
    else if (type == 'c')
        data = all->display->ceil;
    else
        data = all->display->floor;
    while (data)
    {
        // if (data->x < WINDOW_WIDTH && data->y < WINDOW_HEIGHT)
        // {
            printf("data->x: %d ", data->x);
            printf("data->y: %d\n", data->y);
            if (mlx_image_to_window(all->window, data->image, data->x, data->y) == -1)
                terminate(all, 1);
        // }
        data = data->next;
    }

}

void create_instance(t_all *all)
{
    load_image(all, 'f');
    load_image(all, 'w');
    load_image(all, 'c');
}