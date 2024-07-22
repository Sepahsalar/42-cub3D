/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/22 14:18:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
	terminate(all, 0);
}
