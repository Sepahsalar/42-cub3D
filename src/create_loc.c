/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/14 09:48:37 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_loc	*clean_loc(t_loc *first)
{
	t_loc	*node;
	t_loc	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	return (0);
}

t_loc	*create_loc_node(char temp, int x, int y)
{
	t_loc	*new;

	new = malloc(sizeof(t_loc));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_loc));
	new->c = temp;
	new->x = x;
	new->y = y;
	new->x0 = x;
	new->y0 = y;
	new->x1 = x + 1;
	new->y1 = y + 1;
	new->x_mid = new->x0 + 0.5;
	new->y_mid = new->y0 + 0.5;
	if (temp != '1')
	{
		new->sx = -1;
		new->sy = -1;
		new->ex = -1;
		new->ey = -1;
		new->wx = -1;
		new->wy = -1;
		new->nx = -1;
		new->ny = -1;
	}
	else
	{
		new->sx = new->x + 0.5;
		new->sy = new->y + 1.0;
		new->wx = new->x;
		new->wy = new->y + 0.5;
		new->ex = new->x + 1.0;
		new->ey = new->y + 0.5;
		new->nx = new->x + 0.5;
		new->ny = new->y;
	}
	return (new);
}

void	create_loc(t_all *all)
{
	t_loc	*new;
	t_loc	*old;
	char 	*temp;
	int		x;
	int		y;
	int		index;

	all->map->start = NULL;
	temp = all->strmap;
	x = 0;
	y = 0;
	index = 0;
	while (*temp)
	{
		if(*temp != '\n')
		{
			index++;
			new = create_loc_node(*temp, x, y);
			if (!(all->map->start))
					all->map->start = new;
			else
			{
				old->next = new;
				new->previous = old;
			}
			check_failure(0, new, 2, all);
			old = new;
			x++;
		}
		else if (*temp == '\n')
		{
			y++;
			x = 0;
		}
		temp++;
	}
}

int find_min_x(t_all *all, int y)
{
	t_loc	*temp;
	int		min;

	min = all->map_width;
	temp = all->map->start;
	while(temp)
	{
		if (temp->x < min && temp->y == y)
			min = temp->x;
		temp = temp->next;
	}
	return (min);
}

int find_max_x(t_all *all, int y)
{
	t_loc	*temp;
	int		max;

	max = 0;
	temp = all->map->start;
	while(temp)
	{
		if (temp->x > max && temp->y == y)
			max = temp->x;
		temp = temp->next;
	}
	return (max);
}

int find_min_y(t_all *all, int x)
{
	t_loc	*temp;
	int		min;

	min = all->map_height;
	temp = all->map->start;
	while(temp)
	{
		if (temp->y < min && temp->x == x)
			min = temp->y;
		temp = temp->next;
	}
	return (min);
}

int find_max_y(t_all *all, int x)
{
	t_loc	*temp;
	int		max;

	max = 0;
	temp = all->map->start;
	while(temp)
	{
		if (temp->y > max && temp->x == x)
			max = temp->y;
		temp = temp->next;
	}
	return (max);
}

// void ignore_inside_surface(t_all *all)
// {
// 	t_loc	*temp1;
// 	t_loc	*temp2;
// 	int 	i;
// 	int 	min;
// 	int 	max;

// 	temp1 = all->map->start;
// 	while (temp1)
// 	{
// 		if (temp1->c == '1')
// 		{
// 			temp2 = all->map->start;
// 			while(temp2)
// 			{
// 				if (temp2->c == '1')
// 				{
// 					if(temp1->sx== temp2->nx && temp1->sy == temp2->ny)
// 					{
// 						temp1->sx = -1;
// 						temp1->sy = -1;
// 						temp2->nx = -1;
// 						temp2->ny = -1;
// 					}
// 					else if(temp1->nx== temp2->sx && temp1->ny == temp2->sy)
// 					{
// 						temp1->nx = -1;
// 						temp1->ny = -1;
// 						temp2->sx = -1;
// 						temp2->sy = -1;
// 					}
// 					else if(temp1->ex == temp2->wx && temp1->ey == temp2->wy)
// 					{
// 						temp1->ex = -1;
// 						temp1->ey = -1;
// 						temp2->wx = -1;
// 						temp2->wy = -1;
// 					}
// 					else if(temp1->wx == temp2->ex && temp1->wy == temp2->ey)
// 					{
// 						temp1->wx = -1;
// 						temp1->wy = -1;
// 						temp2->ex = -1;
// 						temp2->ey = -1;
// 					}
// 				}
// 				temp2 = temp2->next;
// 			}
// 		}
// 		temp1 = temp1->next;
// 	}
// 	min = 0;
// 	max = 0;
// 	i = 0;
// 	while(i < all->map_width)
// 	{
// 		min = find_min_y(all, i);
// 		max = find_max_y(all, i);
// 		temp1 = all->map->start;
// 		while (temp1)
// 		{
// 			if (temp1->c == '1' && temp1->x == i && temp1->y == min)
// 			{
// 				temp1->nx = -1;
// 				temp1->ny = -1;
// 			}
// 			else if (temp1->c == '1' && temp1->x == i && temp1->y == max)
// 			{
// 				temp1->sx = -1;
// 				temp1->sy = -1;
// 			}
// 			temp1 = temp1->next;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while(i < all->map_height)
// 	{
// 		min = find_min_x(all, i);
// 		max = find_max_x(all, i);
// 		temp1 = all->map->start;
// 		while (temp1)
// 		{
// 			if (temp1->c == '1' && temp1->y == i && temp1->x == min)
// 			{
// 				temp1->wx = -1;
// 				temp1->wy = -1;
// 			}
// 			else if (temp1->c == '1' && temp1->y == i && temp1->x == max)
// 			{
// 				temp1->ex = -1;
// 				temp1->ey = -1;
// 			}
// 			temp1 = temp1->next;
// 		}
// 		i++;
// 	}
// }

void ignore_inside_surface(t_all *all)
{
	t_loc	*temp1;
	t_loc	*temp2;
	int 	i;
	int 	min;
	int 	max;

	temp1 = all->map->start;
	while (temp1)
	{
		if (temp1->c == '1')
		{
			temp2 = all->map->start;
			while(temp2)
			{
				if (temp2->c == '1')
				{
					if(temp1->sx== temp2->nx && temp1->sy == temp2->ny)
					{
						temp1->sx = -1;
						temp1->sy = -1;
						temp2->nx = -1;
						temp2->ny = -1;
					}
					else if(temp1->nx== temp2->sx && temp1->ny == temp2->sy)
					{
						temp1->nx = -1;
						temp1->ny = -1;
						temp2->sx = -1;
						temp2->sy = -1;
					}
					else if(temp1->ex == temp2->wx && temp1->ey == temp2->wy)
					{
						temp1->ex = -1;
						temp1->ey = -1;
						temp2->wx = -1;
						temp2->wy = -1;
					}
					else if(temp1->wx == temp2->ex && temp1->wy == temp2->ey)
					{
						temp1->wx = -1;
						temp1->wy = -1;
						temp2->ex = -1;
						temp2->ey = -1;
					}
				}
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
	}
	min = 0;
	max = 0;
	i = 0;
	while(i < all->map_width)
	{
		min = find_min_y(all, i);
		max = find_max_y(all, i);
		temp1 = all->map->start;
		while (temp1)
		{
			if (temp1->x == i && temp1->y == min)
			{
				if(temp1->c == '1')
				{
					temp1->nx = -1;
					temp1->ny = -1;
				}
				else
				{
					ft_putendl_fd("Not surrounded by walls", 2);
					terminate(all, 1);
				}
			}
			else if (temp1->x == i && temp1->y == max)
			{
				if(temp1->c == '1')
				{
					temp1->sx = -1;
					temp1->sy = -1;
				}
				else
				{
					ft_putendl_fd("Not surrounded by walls", 2);
					terminate(all, 1);
				}
			}
			temp1 = temp1->next;
		}
		i++;
	}
	i = 0;
	while(i < all->map_height)
	{
		min = find_min_x(all, i);
		max = find_max_x(all, i);
		temp1 = all->map->start;
		while (temp1)
		{
			if (temp1->y == i && temp1->x == min)
			{
				if(temp1->c == '1')
				{
					temp1->wx = -1;
					temp1->wy = -1;
				}
				else
				{
					ft_putendl_fd("Not surrounded by walls", 2);
					terminate(all, 1);
				}
			}
			else if (temp1->y == i && temp1->x == max)
			{
				if(temp1->c == '1')
				{
					temp1->ex = -1;
					temp1->ey = -1;
				}
				else
				{
					ft_putendl_fd("Not surrounded by walls", 2);
					terminate(all, 1);
				}
			}
			temp1 = temp1->next;
		}
		i++;
	}
}
