/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:13:45 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/29 11:18:08 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *msg, int error_code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (error_code);
}

// Calculate the smallest difference between two angles
float	angle_difference_rad(float angle1, float angle2)
{
	float	diff;

	diff = fabs(angle1 - angle2);
	if (diff > PI)
		diff = 2 * PI - diff;
	return (diff);
}
