// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   create_possible.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/14 12:27:15 by asohrabi          #+#    #+#             */
// /*   Updated: 2024/08/15 10:03:15 by nnourine         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/cub3D.h"

// t_possible	*clean_possibility(t_possible *first)
// {
// 	t_possible	*node;
// 	t_possible	*temp;

// 	node = first;
// 	while (node)
// 	{
// 		temp = node->next;
// 		free(node);
// 		node = temp;
// 	}
// 	return (0);
// }

// t_possible	*create_possibility_node(t_all *all, t_loc *temp_loc)
// {
// 	t_possible	*new;

// 	new = malloc(sizeof(t_possible));
// 	if (!new)
// 		return (0);
// 	ft_memset(new, 0, sizeof(t_possible));
// 	new->loc = temp_loc;
// 	new->sn_winner_distance = max_distance(all);
// 	new->ew_winner_distance = max_distance(all);
// 	new->sn_winner_texture = '0';
// 	new->ew_winner_texture = '0';
// 	new->sn_winner_x = -1.0;
// 	new->sn_winner_y = -1.0;
// 	new->ew_winner_x = -1.0;
// 	new->ew_winner_y = -1.0;
// 	return (new);
// }

// void	create_possibility(t_all *all, t_range range)
// {
// 	t_possible	*new;
// 	t_possible	*old;
// 	t_loc		*temp_loc;

// 	temp_loc = all->map->start;
// 	while (temp_loc)
// 	{
// 		if (temp_loc->x >= range.x_min && temp_loc->x <= range.x_max
// 			&& temp_loc->y >= range.y_min && temp_loc->y <= range.y_max
// 			&& temp_loc->c == '1')
// 		{
// 			new = create_possibility_node(all, temp_loc);
// 			if (!(all->possible))
// 				all->possible = new;
// 			else
// 			{
// 				old->next = new;
// 				new->previous = old;
// 			}
// 			check_failure(0, new, 2, all);
// 			old = new;
// 		}
// 		temp_loc = temp_loc->next;
// 	}
// }

// // void	find_winner_surface(t_all *all)
// // {
// // 	t_possible	*temp;

// // 	temp = all->possible;
// // 	while (temp)
// // 	{
// // 		if (temp->loc->sx != -1 && temp->loc->sy != -1)
// // 		{
// // 			temp->sn_winner_distance = sqrt(pow(all->x - temp->loc->sx, 2)
// // 					+ pow(all->y - temp->loc->sy, 2));
// // 			temp->sn_winner_texture = 'S';
// // 			temp->sn_winner_x = temp->loc->sx;
// // 			temp->sn_winner_y = temp->loc->sy;
// // 		}
// // 		if (temp->loc->ex != -1 && temp->loc->ey != -1)
// // 		{
// // 			temp->ew_winner_distance = sqrt(pow(all->x - temp->loc->ex, 2)
// // 					+ pow(all->y - temp->loc->ey, 2));
// // 			temp->ew_winner_texture = 'E';
// // 			temp->ew_winner_x = temp->loc->ex;
// // 			temp->ew_winner_y = temp->loc->ey;
// // 		}
// // 		if ((temp->loc->nx != -1 && temp->loc->ny != -1) && sqrt(pow(all->x
// // 					- temp->loc->nx, 2) + pow(all->y - temp->loc->ny,
// // 					2)) < temp->sn_winner_distance)
// // 		{
// // 			temp->sn_winner_distance = sqrt(pow(all->x - temp->loc->nx, 2)
// // 					+ pow(all->y - temp->loc->ny, 2));
// // 			temp->sn_winner_texture = 'N';
// // 			temp->sn_winner_x = temp->loc->nx;
// // 			temp->sn_winner_y = temp->loc->ny;
// // 		}
// // 		if ((temp->loc->wx != -1 && temp->loc->wy != -1) && sqrt(pow(all->x
// // 					- temp->loc->wx, 2) + pow(all->y - temp->loc->wy,
// // 					2)) < temp->ew_winner_distance)
// // 		{
// // 			temp->ew_winner_distance = sqrt(pow(all->x - temp->loc->wx, 2)
// // 					+ pow(all->y - temp->loc->wy, 2));
// // 			temp->ew_winner_texture = 'W';
// // 			temp->ew_winner_x = temp->loc->wx;
// // 			temp->ew_winner_y = temp->loc->wy;
// // 		}
// // 		temp = temp->next;
// // 	}
// // }
