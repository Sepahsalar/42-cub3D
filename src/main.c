/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/15 13:07:42 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// 1) fill_strip_utils3 --------- needs 4 more functions
// 2) strip_to_image ------------ needs 1 more function
// 3) loc_possibility ----------- needs 3 more functions
// 4) find_winner --------------- needs to be 3 separate files

// from subject:
// Floor color:
// F 220,100,0
// · identifier: F
// · R,G,B colors in range [0,255]: 0, 255, 255

// maybe we should just check 3 elements for C and F

// decide whether we should check for file availability in walls identifier

// agar zavie rond nabud ham x ham y bere jelo?

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_putendl_fd("Error", 2);
		return (1);
	}
	if (!check_map_format(argv[1]))
	{
		ft_putendl_fd("Invalid map format", 2);
		ft_putendl_fd("Error", 2);
		return (1);
	}
	all = init_all(argv);
	fill_strips(all);
	mlx_key_hook(all->window, &press_key, all);
	mlx_loop(all->window);
	terminate(all, 0);
}
