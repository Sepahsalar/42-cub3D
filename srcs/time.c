/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:26:12 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/22 11:30:10 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long long	ft_timestamp_ms(t_all *all)
{
	struct timeval	tv;
	long long		timestamp;
	int				error;

	error = gettimeofday(&tv, 0);
	if (error == -1)
	{
		ft_putstr_fd("Gettimeofday failed\n", 2);
		terminate(all, 1);
	}
	timestamp = (((long long)(tv.tv_sec)) * 1000)
		+ (((long long)(tv.tv_usec)) / 1000);
	return (timestamp);
}

// int passed_time(t_all *all, long long start)
// {
// 	long long	current_time;

// 	current_time = ft_timestamp_ms(all);
// 	return ((int)current_time - start);
// }
