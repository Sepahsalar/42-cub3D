/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:49:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	ft_tan(double a)
{
	double	angle;

	angle = M_PI * a / 180;
	return (tan(angle));
}

double	ft_cos(double a)
{
	double	angle;

	angle = M_PI * a / 180;
	return (cos(angle));
}
