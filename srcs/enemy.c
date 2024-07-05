/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/05 18:44:57 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_enemy(t_data *data, int i, float x, float y)
{
    int current;

    current = data->enemies[i]->current_frame;
    mlx_image_to_window(data->mlx, data->enemy_frame[current], x, y);    
}

void	hook_enemies(t_data *data)
{
    // relative position of enemy to player
    int     i;
    float   dx;
    float   dy;
    float   distance;
    float   angle;
    float   rel_angle;
    // int     is_visible;
    int     screen_x;
    int     screen_y;

    i = -1;
    while (data->enemies[++i] != NULL)
    {
        dx = data->enemies[i]->x_pos - data->player->x_pos;
        dy = data->enemies[i]->y_pos - data->player->y_pos;
        printf("player angle: %f\n", data->player->angle);
        distance = sqrtf(dx * dx + dy * dy);
        angle = atan2(dy, dx);
        printf("angle: %f\n", angle);
        rel_angle = data->player->angle - angle;
        rel_angle = atan2(sin(rel_angle), cos(rel_angle));
        if (rel_angle >= -(FOV / 2) && rel_angle <= (FOV / 2))
        {
            screen_x = (rel_angle + (FOV / 2) / FOV) * data->mlx->width;
            screen_y = data->mlx->height / 2;
            draw_enemy(data, i, screen_x, screen_y);
        }
    }    
}