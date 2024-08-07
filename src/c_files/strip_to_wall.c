/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/07 11:21:18 by nnourine         ###   ########.fr       */
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

// void strip_to_wall(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *brick;
// 	mlx_image_t *wall_before_resize;
// 	mlx_image_t *real_wall;
// 	int brick_in_width;
// 	int wall_br_height;
// 	int wall_br_width;
//     mlx_image_t *new_image;
//     int         length;
//     int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     int j;
//     t_data      *wall;
//     t_data      *new;
//     int         i2;
//     int         j2;

//     strip = all->strip;
//     wall = last_node_data(all->display->wall);
//     while(strip)
//     {
//         brick = image_maker(all, strip->wall);
// 		if (!mlx_resize_image(brick, BRICKS_WIDTH, BRICKS_HEIGHT))
//             terminate(all, 1);
// 		wall_br_height = BRICKS_IN_H * BRICKS_HEIGHT;
// 		brick_in_width = floor(strip->wall_length/WALL) * BRICKS_IN_H;
// 		wall_br_width = brick_in_width * BRICKS_WIDTH;
// 		wall_before_resize = mlx_new_image(all->window, wall_br_width, wall_br_height);
// 		i = 0;
//         j = 0;
//         while (i < wall_br_width)
//         {
//             j = 0;
//             while (j < wall_br_height)
//             {
//                 i2 = i % BRICKS_WIDTH;
//                 j2 = j % BRICKS_HEIGHT;
//                 pixel = brick->pixels + 4*(i2 + j2 * BRICKS_WIDTH);
//                 int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//                 mlx_put_pixel(wall_before_resize, i, j, int_color);
//                 j++;
//             }
//             i++;
//         }
		
//         height = round(strip->wall_h);
//         length = strip->wall_length;
// 		if (!mlx_resize_image(wall_before_resize, length, height))
//             terminate(all, 1);
// 		real_wall = wall_before_resize;
// 		new_image = mlx_new_image(all->window, 1, height);
//         if (!new_image)
//             terminate(all, 1);
//         i = 0;
//         while (i < height)
//         {
//             pixel = real_wall->pixels + 4*(i * length + strip->index);
//             int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//             mlx_put_pixel(new_image, 0, i, int_color);
//             i++;
//         }
//         mlx_delete_image(all->window, brick);
//         mlx_delete_image(all->window, wall_before_resize);
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

// void strip_to_ceil(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *base_image;
//     mlx_image_t *new_image;
//     // int         length;
//     int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     t_data      *end_ceil;
//     t_data      *start_ceil;
//     t_data      *new;

//     strip = all->strip;
//     start_ceil = all->display->ceil;
//     end_ceil = last_node_data(all->display->ceil);
//     while(strip)
//     {
//         base_image = all->elems->c;
//         height = round(strip->ceil_h);
//         // length = 1;
//         new_image = mlx_new_image(all->window, 1, height);
//         if (!new_image)
//             terminate(all, 1);
//         pixel = base_image->pixels;
//         int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//         i = 0;
//         while (i < height)
//         {
//             mlx_put_pixel(new_image, 0, i, int_color);
//             i++;
//         }
//         new = malloc(sizeof(t_data));
//         if (!new)
//             terminate(all, 1);
//         new->image = new_image;
//         new->x = strip->x;
//         new->y = 0;
//         new->previous = 0;
//         new->next = 0;
//         if (!end_ceil)
//             start_ceil = new;
//         else
//         {
//             end_ceil->next = new;
//             new->previous = end_ceil;
//         }
//         strip= strip->next;
//         end_ceil = new;
//     }
//     all->display->ceil = start_ceil;
// }

// void strip_to_wall(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *brick;
// 	// mlx_image_t *wall_before_resize;
// 	mlx_image_t *real_wall;
// 	// int brick_in_width;
// 	// int wall_br_height;
// 	// int wall_br_width;
//     mlx_image_t *new_image;
//     int         length;
//     int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     int j;
//     t_data      *wall;
//     t_data      *new;
//     int         i2;
//     int         j2;
// 	int			h_brick;
// 	int			w_brick;

//     strip = all->strip;
//     wall = last_node_data(all->display->wall);
//     while(strip)
//     {
// 		height = round(strip->wall_h);
// 		length = strip->wall_length;
//         brick = image_maker(all, strip->wall);
// 		h_brick = round(height / BRICKS_IN_H);
// 		w_brick = round (length * BRICKS_IN_H / WALL);
// 		if (!mlx_resize_image(brick, w_brick, h_brick))
// 			terminate(all, 1);
// 		real_wall = mlx_new_image(all->window, length, height);
// 		if (!real_wall)
// 			terminate(all, 1);
// 		i = 0;
// 		j = 0;
// 		while (i < length)
// 		{
// 			j = 0;
// 			while (j < height)
// 			{
// 				i2 = i % w_brick;
// 				j2 = j % h_brick;
// 				pixel = brick->pixels + 4*(i2 + j2 * w_brick);
// 				int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
// 				mlx_put_pixel(real_wall, i, j, int_color);
// 				j++;
// 			}
// 			i++;
// 		}
// 		new_image = mlx_new_image(all->window, 1, height);
//         if (!new_image)
//             terminate(all, 1);
//         i = 0;
//         while (i < height)
//         {
//             pixel = real_wall->pixels + 4*(i * length + strip->index);
//             int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//             mlx_put_pixel(new_image, 0, i, int_color);
//             i++;
//         }
//         mlx_delete_image(all->window, brick);
//         mlx_delete_image(all->window, real_wall);
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

// void strip_to_floor(t_all *all)
// {
//     t_strip     *strip;
//     mlx_image_t *base_image;
//     mlx_image_t *new_image;
//     int         height;
//     uint8_t     *pixel;
//     int         int_color;
//     int         i;
//     t_data      *end_floor;
//     t_data      *start_floor;
//     t_data      *new;

//     strip = all->strip;
//     start_floor = all->display->floor;
//     end_floor = last_node_data(all->display->floor);
//     while(strip)
//     {
//         base_image = all->elems->f;
//         height = WINDOW_HEIGHT - round(strip->ceil_h) - round(strip->wall_h);
//         // length = 1;
//         new_image = mlx_new_image(all->window, 1, height);
//         if (!new_image)
//             terminate(all, 1);
//         pixel = base_image->pixels;
//         int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
//         i = 0;
//         while (i < height)
//         {
//             mlx_put_pixel(new_image, 0, i, int_color);
//             i++;
//         }
//         new = malloc(sizeof(t_data));
//         if (!new)
//             terminate(all, 1);
//         new->image = new_image;
//         new->x = strip->x;
//         new->y = round(strip->ceil_h) + round(strip->wall_h);
//         new->previous = 0;
//         new->next = 0;
//         if (!end_floor)
//             start_floor = new;
//         else
//         {
//             end_floor->next = new;
//             new->previous = end_floor;
//         }
//         strip= strip->next;
//         end_floor = new;
//     }
//     all->display->floor = start_floor;
// }

void strip_to_image(t_all *all)
{
    t_strip     *strip;
    mlx_image_t *brick;
	mlx_image_t *real_wall;
    mlx_image_t *new_image;
    int         length;
    int         height;
    uint8_t     *pixel;
    int         int_color;
    int         i;
    int j;
    t_data      *wall;
    t_data      *new;
    int         i2;
    int         j2;
	int			h_brick;
	int			w_brick;

    strip = all->strip;
    wall = last_node_data(all->display->wall);
    while(strip)
    {
		//printf("strip->x: %d\n", strip->x);
		height = round(strip->wall_h);
		length = strip->wall_length;
        brick = image_maker(all, strip->wall);
		h_brick = round(height / BRICKS_IN_H);
		w_brick = round (length * BRICKS_IN_H / WALL);
		if (!mlx_resize_image(brick, w_brick, h_brick))
			terminate(all, 1);
		real_wall = mlx_new_image(all->window, length, height);
		if (!real_wall)
			terminate(all, 1);
		i = 0;
		j = 0;
		//printf("strip->x: %d\n", strip->x);
		while (i < length)
		{
			j = 0;
			while (j < height)
			{
				i2 = i % w_brick;
				j2 = j % h_brick;
				pixel = brick->pixels + 4*(i2 + j2 * w_brick);
				int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
				mlx_put_pixel(real_wall, i, j, int_color);
				j++;
			}
			i++;
		}
		//printf("strip->x: %d\n", strip->x);
		new_image = mlx_new_image(all->window, 1, WINDOW_HEIGHT);
        if (!new_image)
            terminate(all, 1);
        i = 0;
		//printf("ceil_h: %f\n", round(strip->ceil_h));
		//printf("wall_h: %d\n", height);
		//printf("floer_h: %f\n", WINDOW_HEIGHT - round(strip->ceil_h) - height);
        while (i < WINDOW_HEIGHT)
        {
			// if(strip->x == 1)
				//printf("i: %d\n", i);
			if (i <= (int)round(strip->ceil_h))
				int_color = all->ceil_color;
			else if (i > (int)round(strip->ceil_h) && i < ((int)round(strip->ceil_h) + height))
			{
				// if(strip->x == 1 && i > 432)
					//printf("i am here\n");
				pixel = real_wall->pixels + 4*((i - (int)round(strip->ceil_h)) * length + strip->index);
				int_color = color(pixel[0], pixel[1], pixel[2], pixel[3]);
				
			}
			else
				int_color = all->floor_color;
			
            mlx_put_pixel(new_image, 0, i, int_color);
            i++;
        }
		mlx_image_to_window(all->window, new_image, strip->x, 0); //
		//printf("strip->x: %d\n", strip->x);
        mlx_delete_image(all->window, brick);
        mlx_delete_image(all->window, real_wall);
        new = malloc(sizeof(t_data));
        if (!new)
            terminate(all, 1);
        new->image = new_image;
        new->x = strip->x;
        new->y = 0;
        new->previous = 0;
        new->next = 0;
		//printf("strip->x: %d\n", strip->x);
        if (!wall)
            all->display->wall = new;
        else
        {
            wall->next = new;
            new->previous = wall;
        }
		//printf("strip->x: %d\n", strip->x);
        strip = strip->next;
        wall = new;
    }
}

