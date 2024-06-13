/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/13 15:07:03 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *msg, int	error_code)
{
	printf("%s\n", msg);
	return (error_code);
}

int	ft_abs(int result)
{
	if (result < 0)
		result = -result;
	return (result);
}

int	free_2d_int(int **int_arr)
{
	int	i;

	i = 0;
	if (int_arr)
	{
		while (i < MAPHEIGHT)
		{
			free (int_arr[i]);
			i ++;
		}
		free (int_arr);
	}
	return (0);
}
