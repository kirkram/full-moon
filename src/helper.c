/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/30 12:44:48 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
