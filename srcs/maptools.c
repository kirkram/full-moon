/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maptools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:21:32 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/05 12:29:06 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_2d_int(int **int_arr, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			dprintf(2, "%d", int_arr[y][x]);
			x++;
		}
		dprintf(2, "\n");
		y++;
	}
	dprintf(2, "\n");
}

int** alloc_2d_int(int rows, int cols) 
{
    int	**array;
    int	i;

    array = (int **)ft_calloc(rows, sizeof(int *));
    if (array == NULL)
		exit(ft_error("Malloc error on int**", 22));
	i = 0;
	while (i < rows)
    {
        array[i] = (int *)ft_calloc(cols, sizeof(int));
        if (array[i] == NULL) 
			exit(ft_error("Malloc error on int*", 22));
		i++;
    }
    return array;
}

int	**copy_2d_int(int **int_arr, int rows, int cols)
{
	int	**new_arr;
	int	y;

	new_arr = malloc(rows * sizeof(int *));
	if (!new_arr)
		exit(ft_error("Malloc error on int**", 22));
	y = -1;
	while (++y < rows)
	{
		new_arr[y] = malloc(cols * sizeof(int));
		if (!new_arr[y])
			exit(ft_error("Malloc error on int*", 22));
		ft_memmove(new_arr[y], int_arr[y], cols * sizeof(int));
	}
	return (new_arr);
}

int	free_2d_int(int **int_arr, int rows)
{
	int	i;

	i = 0;
	if (int_arr)
	{
		while (i < rows)
		{
			free(int_arr[i]);
			i++;
		}
		free(int_arr);
	}
	return (0);
}
