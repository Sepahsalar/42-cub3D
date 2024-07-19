/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ber.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:41:20 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/08 12:00:52 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ft_check_ber(char *map)
{
	int		len;
	char	*end;

	len = (int)ft_strlen(map);
	if (len <= 4)
		ft_exit_failure(0, 0, "Wrong map format");
	end = map + len - 4;
	if (ft_strncmp(end, ".ber", 4))
		ft_exit_failure(0, 0, "Wrong map format");
}
