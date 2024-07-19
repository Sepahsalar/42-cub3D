/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:32:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/01 16:47:45 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ft_escape_key(void *param)
{
	mlx_t		*window;
	t_elements	*elements;

	window = ((t_window_elements *) param)->window;
	elements = (((t_window_elements *) param))->elements;
	ft_exit_success(window, elements);
}
