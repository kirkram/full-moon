/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:21:13 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/08 17:03:54 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_ptrs(t_data *data, int i, int j)
{
	t_enemy	*tmp;

	tmp = data->enemies[i];
	data->enemies[i] = data->enemies[j];
	data->enemies[j] = tmp;
}

// atm just a bubble sort
void	sort_enemy_arr(t_data *data)
{
	int n;
	int i;
	int j;

	n = 0;
	i = -1;
	j = -1;
	while (data->enemies[n] != NULL)
		n++;
	while (++i < n - 1)
	{
		while (++j < n - i - 1)
		{
			if (data->enemies[j]->distance < data->enemies[j + 1]->distance)
				swap_ptrs(data, j, j + 1);
		}
		j = -1;
	}
}