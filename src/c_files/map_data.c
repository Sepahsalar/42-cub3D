/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:57:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/06 14:42:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_map_data	*ft_create_map_node(t_cell_data cell_data)
{
	t_map_data	*new;

	new = malloc(sizeof(t_map_data));
	if (!new)
		return (0);
	(*new).ch = cell_data.ch;
	(*new).x = cell_data.x;
	(*new).y = cell_data.y;
	(*new).t = 0;
	new->next = 0;
	return (new);
}

void	ft_cell_update(t_cell_data *cell_data)
{
	if ((*cell_data).ch == '\n')
	{
		(*cell_data).x = 0;
		(*cell_data).y++;
	}
	else
		(*cell_data).x++;
}

t_map_data	*ft_malloc_fail_map_data(int fd_map,
	t_map_data *first_cell)
{
	close(fd_map);
	ft_free_map_data(first_cell);
	return (0);
}

void	ft_start_cell_data(t_cell_data *cell_data)
{
	(*cell_data).x = 0;
	(*cell_data).y = 0;
	(*cell_data).ch = '\0';
}

t_map_data	*ft_create_map_data(char *map, int fd_map,
		t_map_data *first_cell)
{
	t_map_data	*new_cell;
	t_map_data	*old_cell;
	t_cell_data	cell_data;

	fd_map = open(map, O_RDONLY);
	if (fd_map == -1)
		ft_exit_failure(0, 0, "Map opening problem");
	ft_start_cell_data(&cell_data);
	while (read(fd_map, &(cell_data.ch), 1))
	{
		if (cell_data.ch != '\n')
		{
			new_cell = ft_create_map_node(cell_data);
			if (!new_cell)
				return (ft_malloc_fail_map_data(fd_map, first_cell));
			if (!first_cell)
				first_cell = new_cell;
			else
				old_cell->next = new_cell;
			old_cell = new_cell;
		}
		ft_cell_update(&cell_data);
	}
	close(fd_map);
	return (first_cell);
}
