/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 09:19:29 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static int	check_wall(mlx_image_t *player, mlx_image_t *wall, int i, char c)
// {
// 	int	p_x;
// 	int	p_y;
// 	int	w_x;
// 	int	w_y;

// 	p_x = player->instances[0].x;
// 	p_y = player->instances[0].y;
// 	w_x = wall->instances[i].x;
// 	w_y = wall->instances[i].y;
// 	if (c == 'U' && p_x == w_x && (p_y == w_y + (int)(player->height)))
// 		return (0);
// 	if (c == 'D' && p_x == w_x && (p_y == w_y - (int)(player->height)))
// 		return (0);
// 	if (c == 'L' && p_y == w_y && (p_x == w_x + (int)(player->width)))
// 		return (0);
// 	if (c == 'R' && p_y == w_y && (p_x == w_x - (int)(player->width)))
// 		return (0);
// 	return (i + 1);
// }

// static int	near_wall(t_all *all, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (i < (int)(all->elems->wall->count))
// 	{
// 		if (!check_wall(all->elems->player, all->elems->wall, i, c))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void	move_con(t_all *all, char c)
// {
// 	if (c == 'U')
// 	{
// 		all->elems->player->instances[0].y -= all->elems->player->height;
// 		all->elems->player_loc.y += -1;
// 	}
// 	else if (c == 'D')
// 	{
// 		all->elems->player->instances[0].y += all->elems->player->height;
// 		all->elems->player_loc.y += 1;
// 	}
// 	else if (c == 'L')
// 	{
// 		all->elems->player->instances[0].x -= all->elems->player->width;
// 		all->elems->player_loc.x += -1;
// 	}
// 	else
// 	{
// 		all->elems->player->instances[0].x += all->elems->player->width;
// 		all->elems->player_loc.x += 1;
// 	}
// }

int is_wall_there(t_all *all, int x, int y)
{
	t_loc	*temp;

	temp = all->map->start;
	while (temp)
	{
		if (temp->x == x && temp->y == y && temp->c == '1')
			return (1);
		temp = temp->next;
	}
	return (0);
	
}

double under_full_circle(double angle)
{
	if (angle >= FULL_CIRCLE_DEGREES)
		return (angle -= FULL_CIRCLE_DEGREES);
	if (angle < 0)
		return (angle += FULL_CIRCLE_DEGREES);
	return (angle);
}

static void	turn(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	clean_strip(all);
	mlx_delete_image(all->window, all->image);
	if (c == 'R')
		all->angle += TURN_INTERVAL;
	else
		all->angle -= TURN_INTERVAL;
	all->angle = under_full_circle(all->angle);
	printf("New-> angle: %f\n", all->angle);
	render(all);    
}

// static void	move(void *param, char c)
// {
// 	t_all	*all;

// 	all = (t_all *)param;
//     clean_strip(all);
//     mlx_delete_image(all->window, all->image);
// 	if (all->angle >= 225 && all->angle < 315)
// 	{
// 		if (c == 'A')
// 		{
// 			all->x -= 1;
// 		}
// 		else if (c == 'D')
// 			all->x += 1;
// 		else if (c == 'W')
// 			all->y -= 1;
// 		else
// 			all->y += 1;
// 	}
// 	else if (all->angle >= 135 && all->angle < 225)
// 	{
// 		if (c == 'W')
// 			all->x -= 1;
// 		else if (c == 'S')
// 			all->x += 1;
// 		else if (c == 'A')
// 			all->y += 1;
// 		else
// 			all->y -= 1;
// 	}
// 	else if (all->angle >= 45 && all->angle < 135)
// 	{
// 		if(c == 'W')
// 			all->y += 1;
// 		else if (c == 'S')
// 			all->y -= 1;
// 		else if (c == 'A')
// 			all->x += 1;
// 		else
// 			all->x -= 1;
// 	}
// 	else
// 	{
// 		if (c == 'W')
// 			all->x += 1;
// 		else if (c == 'S')
// 			all->x -= 1;
// 		else if (c == 'A')
// 			all->y -= 1;
// 		else
// 			all->y += 1;
// 	}
//     printf("New-> x: %f, y: %f\n", all->x, all->y);
//     render(all);    
// }

static void	move(void *param, char c)
{
	t_all	*all;
	double	new_x;
	double	new_y;

	all = (t_all *)param;
	new_x = all->x;
	new_y = all->y;
	if (all->angle >= 225 && all->angle < 315)
	{
		if (c == 'A')
			new_x -= 1;
		else if (c == 'D')
			new_x += 1;
		else if (c == 'W')
			new_y -= 1;
		else
			new_y += 1;
	}
	else if (all->angle >= 135 && all->angle < 225)
	{
		if (c == 'W')
			new_x -= 1;
		else if (c == 'S')
			new_x += 1;
		else if (c == 'A')
			new_y += 1;
		else
			new_y -= 1;
	}
	else if (all->angle >= 45 && all->angle < 135)
	{
		if(c == 'W')
			new_y += 1;
		else if (c == 'S')
			new_y -= 1;
		else if (c == 'A')
			new_x += 1;
		else
			new_x -= 1;
	}
	else
	{
		if (c == 'W')
			new_x += 1;
		else if (c == 'S')
			new_x -= 1;
		else if (c == 'A')
			new_y -= 1;
		else
			new_y += 1;
	}
	new_x = (int)(new_x - 0.5);
	new_y = (int)(new_y - 0.5);
	if (!is_wall_there(all, new_x, new_y))
	{
		clean_strip(all);
    	mlx_delete_image(all->window, all->image);
		all->x = new_x + 0.5;
		all->y = new_y + 0.5;
    	printf("New-> x: %f, y: %f\n", all->x, all->y);
		render(all); 
	}       
}

// void	press_key(mlx_key_data_t keydata, void *param)
// {
// 	// if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
// 	// 	&& keydata.action == MLX_PRESS)
// 	// 	move(param, 'U');
// 	// else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
// 	// 	&& keydata.action == MLX_PRESS)
// 	// 	move(param, 'D');
// 	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
// 		&& keydata.action == MLX_PRESS)
// 		move(param, 'L');
// 	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
// 		&& keydata.action == MLX_PRESS)
// 		move(param, 'R');
// 	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
//         terminate(param, 0);
// }

void	press_key(mlx_key_data_t keydata, void *param)
{
// 	t_all	*all;
// // 
// 	all = (t_all *)param;
	// if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
	// {
	// 	all->y -= 1;
	// 	printf("New-> x: %f, y: %f\n", all->x, all->y);
		
	// }
	// else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
	// 		move(param, 'W');
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move(param, 'W');
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move(param, 'S');
    else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        move(param, 'A');
    else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        move(param, 'D');
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		turn(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		turn(param, 'R');
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        terminate(param, 0);
}
