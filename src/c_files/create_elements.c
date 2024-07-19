/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:04:03 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/08 10:43:29 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

mlx_image_t	*ft_create_image(mlx_t *window, char c,
	int image_width, int image_height)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	if (c == '1')
		texture = mlx_load_png("./src/images/wall.png");
	else if (c == 'C')
		texture = mlx_load_png("./src/images/collectible.png");
	else if (c == 'E')
		texture = mlx_load_png("./src/images/exit.png");
	else
		texture = mlx_load_png("./src/images/player.png");
	if (!texture)
		ft_exit_failure(window, 0, "Texture creation problem");
	image = mlx_texture_to_image (window, texture);
	mlx_delete_texture(texture);
	if (!image)
		ft_exit_failure(window, 0, "Image creation problem");
	if (!mlx_resize_image(image, image_width, image_height))
		ft_exit_failure(window, 0, "Resize problem");
	return (image);
}

t_elements	*ft_create_elements(mlx_t *window,
	t_elements_count elements_count)
{
	t_elements	*elements;
	int			window_width;
	int			window_height;
	int			image_width;
	int			image_height;

	elements = malloc(sizeof(t_elements));
	if (!elements)
		ft_exit_failure(window, 0, "Elements memory allocation problem");
	elements->player_collectible = ft_start_position(window, elements_count);
	image_width = elements_count.image_width;
	image_height = elements_count.image_height;
	window_width = elements_count.window_width;
	window_height = elements_count.window_height;
	elements->empty_space = ft_create_background(window,
			window_width, window_height);
	elements->wall = ft_create_image(window, '1', image_width, image_height);
	elements->collectible = ft_create_image(
			window, 'C', image_width, image_height);
	elements->exit = ft_create_image(window, 'E', image_width, image_height);
	elements->player = ft_create_image(window, 'P', image_width, image_height);
	return (elements);
}

void	ft_create_elements_resize(mlx_t *window,
	t_elements_count elements_count, t_elements	*elements)
{
	int			window_width;
	int			window_height;
	int			image_width;
	int			image_height;

	mlx_delete_image(window, elements->empty_space);
	mlx_delete_image(window, elements->collectible);
	mlx_delete_image(window, elements->wall);
	mlx_delete_image(window, elements->exit);
	mlx_delete_image(window, elements->player);
	image_width = elements_count.image_width;
	image_height = elements_count.image_height;
	window_width = elements_count.window_width;
	window_height = elements_count.window_height;
	elements->empty_space = ft_create_background(window,
			window_width, window_height);
	elements->wall = ft_create_image(window, '1', image_width, image_height);
	elements->collectible = ft_create_image(
			window, 'C', image_width, image_height);
	elements->exit = ft_create_image(window, 'E', image_width, image_height);
	elements->player = ft_create_image(window, 'P', image_width, image_height);
}
