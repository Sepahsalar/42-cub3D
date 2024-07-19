/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:06:42 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/08 11:37:00 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	ft_make_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_color_backgroubd(mlx_image_t *background, int width, int hight)
{
	int	x_index;
	int	y_index;

	x_index = 0;
	while (x_index < width)
	{
		y_index = 0;
		while (y_index < hight)
		{
			mlx_put_pixel(background, x_index, y_index,
				ft_make_color(0, 155, 0, 200));
			y_index++;
		}
		x_index++;
	}
}

mlx_image_t	*ft_create_background(mlx_t *window,
	int window_width, int window_height)
{
	mlx_image_t		*background;

	background = mlx_new_image (window, window_width,
			window_height);
	if (!background)
		ft_exit_failure(window, 0, "background creation problem");
	ft_color_backgroubd(background, window_width, window_height);
	return (background);
}

void	ft_map_to_instance_background_resize(mlx_t *window,
	t_elements *elements)
{
	mlx_image_t	*background;

	background = elements->empty_space;
	if (mlx_image_to_window(window, background, 0, 0) == -1)
		ft_exit_failure(window, elements, "backgroubd instance making problem");
}
