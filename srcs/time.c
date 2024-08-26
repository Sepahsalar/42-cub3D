/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:26:12 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 12:47:50 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long long	ft_timestamp_milis(t_all *all)
{
	struct timeval	tv;
	long long		timestamp;
	int				error;

	error = gettimeofday(&tv, 0);
	if (error == -1)
		terminate(all, "Gettimeofday failed", NULL, NULL);
	timestamp = (((long long)(tv.tv_sec)) * 1000) + (((long long)(tv.tv_usec))
			/ 1000);
	return (timestamp);
}
