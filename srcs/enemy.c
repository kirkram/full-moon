/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/08 12:47:32 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Here account for not visible: skip drawing: partially visible: draw partially
void    draw_enemy(t_data *data, int i, float x, float y)
{
    mlx_image_t*    current;
    mlx_image_t*    drawframe;
    int             new_width;
    int             new_height;

    current = data->enemy_frame[data->enemies[i]->current_frame];
    drawframe = NULL;
    drawframe = mlx_new_image(data->mlx, current->width, current->height);
    if (!drawframe)
        free_all_and_quit(data, "sprite frame draw error", 35);
    ft_memcpy(drawframe->pixels, current->pixels, current->width * current->height * sizeof(uint32_t));
    printf("distance was: %f\n", data->enemies[i]->distance);
    new_height = (ESH * 20  / (int)data->enemies[i]->distance);
    new_width = (ESW * 20 / (int)data->enemies[i]->distance);
    printf("new width: %d\n", new_width);
    printf("new height: %d\n", new_height);
    if (mlx_resize_image(drawframe, new_width, new_height) != 1)
        free_all_and_quit(data, "sprite frame resize error", 35);
    mlx_image_to_window(data->mlx, drawframe, x, y);
}

void	hook_enemies(t_data *data)
{
    // relative position of enemy to player
    int     i;
    float   dx;
    float   dy;
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
        data->enemies[i]->distance = sqrtf(dx * dx + dy * dy);
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