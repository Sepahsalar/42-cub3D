/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 14:47:17 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	reader(t_all *all)
{
	char	c[2];
	int		byte;
	char	*temp;
	
	c[1] = '\0';
	all->strmap = NULL;
	all->fd = open(all->argv, O_RDONLY);
	check_failure(all->fd, NULL, 1, all);
	byte = read(all->fd, c, 1);
	check_failure(byte, NULL, 1, all);
	while (byte)
	{
		temp = all->strmap;
		all->strmap = ft_strjoin(all->strmap, c);
		free(temp);
		check_failure(0, all->strmap, 2, all);
		byte = read(all->fd, c, 1);
		check_failure(byte, NULL, 1, all);
	}
}