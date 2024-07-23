/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/23 13:48:45 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void size_grid (t_all *all)
{
	t_loc *loc;
	t_loc *temp_loc;
	int x;
	int y;
	int angle;
	double angle_rad;
	double temp_x;
	double temp_y;
	double min_d;
	double final_x;
	double final_y;
		
	loc = all->map->start;
	x = 0;
	y = 0;
	while (loc)
	{
		if (x < loc->x)
			x = loc->x;
		if (y < loc->y)
			y = loc->y;
		loc = loc->next;
	}
	printf("size of map : x = %d, y = %d\n", x + 1, y + 1);
	loc = all->map->start;
	while (loc)
	{
		if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
			break ;
		loc = loc->next;
	}
	printf("loc of player : x = %d, y = %d\n", loc->x, loc->y);
	angle = 45;
	min_d = sqrt(pow(x + 1, 2) + pow(y + 1, 2));
	// while (angle < 90)
	// {
		angle_rad = angle * M_PI / 180;
		temp_x = loc->x;
		while (temp_x < x + 1)
		{
			temp_loc = all->map->start;
			temp_y = (tan((M_PI / 2) - angle_rad) * (temp_x - loc->x)) + loc->y;
			while (temp_loc)
			{
				if (temp_loc->x == temp_x && temp_loc->y <= ceil(temp_y) && temp_loc->y >= floor(temp_y) && temp_loc->c == '1')
				{
					if (sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2)) < min_d)
					{
						min_d = sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2));
						final_x = temp_loc->x;
						final_y = temp_loc->y;
					}
				}
				temp_loc = temp_loc->next;
			}
			
			// printf("angle = %d, for x = %f, intersection y = %f\n", angle, temp_x, temp_y);
			temp_x++;
		}
		printf("final x = %f, final y = %f\n", final_x, final_y);
		temp_y = loc->y;
		min_d = sqrt(pow(x + 1, 2) + pow(y + 1, 2));
		while (temp_y)
		{
			temp_loc = all->map->start;
			temp_x = temp_y - loc->y / tan((M_PI / 2) - angle_rad) + loc->x;
			while (temp_loc)
			{
				// printf("loc->x = %d, loc->y = %d, temp_x = %f, temp_y = %f\n", loc->x, loc->y, temp_x, temp_y);
				if (temp_loc->y == temp_y && temp_loc->x <= ceil(temp_x) && temp_loc->x >= floor(temp_x) && temp_loc->c == '1')
				{
					if (sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2)) < min_d)
					{
						min_d = sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2));
						final_x = temp_loc->x;
						final_y = temp_loc->y;
					}
				}
				temp_loc = temp_loc->next;
			}
			
			// printf("angle = %d, for y = %f, intersection x = %f\n", angle, temp_y, temp_x);
			// printf("floor y = %f and ceil y = %f\n", floor(temp_y), ceil(temp_y));
			temp_y--;
		}
		printf("final x = %f, final y = %f\n", final_x, final_y);	
	// 	angle++;
		
	// }
	
}

int main(int argc, char **argv)
{
	t_all *all;

	(void)argc;
	all = malloc(sizeof(t_all));
	if (!all)
		terminate(all, 1);
	all->argv = argv[1];
	all->fd = -1;
	all->map = map_parser(all);
	size_grid(all);
	terminate(all, 0);
}
