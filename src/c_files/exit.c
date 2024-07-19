/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:03:48 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/06 12:20:29 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ft_free_map_data(void *first)
{
	t_map_data	*node;
	t_map_data	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
}

void	ft_free_collectible_list(void *first)
{
	t_collectible_position	*node;
	t_collectible_position	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
}

int	ft_exit_failure(mlx_t *mlx, t_elements *elements,
		char *error_message)
{
	if (elements)
	{
		ft_free_collectible_list((elements->player_collectible)->collectible);
		free(elements->player_collectible);
		free(elements);
	}
	if (mlx)
		mlx_terminate(mlx);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}

int	ft_exit_success(mlx_t *mlx, t_elements *elements)
{
	if (elements)
	{
		ft_free_collectible_list((elements->player_collectible)->collectible);
		free(elements->player_collectible);
		free (elements);
	}
	if (mlx)
		mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}
