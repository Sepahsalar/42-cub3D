/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:49:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	ft_tan(double a)
{
	double	angle;

	angle = M_PI * a / 180;
	return (tan(angle));
}

double	ft_sin(double a)
{
	double	angle;

	angle = M_PI * a / 180;
	return (sin(angle));
}

double	ft_cos(double a)
{
	double	angle;

	angle = M_PI * a / 180;
	return (cos(angle));
}
