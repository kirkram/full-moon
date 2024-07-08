/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/08 14:21:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y) 
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t alpha;
    
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return 0;
    int pixel_index = (y * img->width + x) * sizeof(uint32_t);
    red = img->pixels[pixel_index];
	green = img->pixels[pixel_index + 1];
	blue = img->pixels[pixel_index + 2];
	alpha = img->pixels[pixel_index + 3];
    return (red << 24 | green << 16 | blue << 8 | alpha);
}

void draw_image_onto_image(mlx_image_t *dest, mlx_image_t *src, int dest_x, int dest_y) {

    t_point     pt;


    pt.y = -1;
    pt.x = -1;
    pt.color = 0;

    while(++(pt.x) < (int32_t)src->width) 
    {
        while (++(pt.y) < (int32_t)src->height) 
        {
            pt.color = get_pixel_color(src, (uint32_t)pt.x, (uint32_t)pt.y);
            // printf("color: %u\n", pt.color);
            if ((dest_x + pt.x) >= 0 && (uint32_t)(dest_x + pt.x) < dest->width &&
                (dest_y + pt.y) >= 0 && (uint32_t)(dest_y + pt.y) < dest->height) {
                mlx_put_pixel(dest, dest_x + pt.x, dest_y + pt.y, pt.color);
            }
        }
        pt.y = -1;
    }
}

// Here account for not visible: skip drawing: partially visible: draw partially
void    draw_enemy(t_data *data, int i, float screen_x)
{
    mlx_image_t*    current;
    mlx_image_t*    drawframe;
    int             new_width;
    int             new_height;
    float           screen_y;

    current = data->enemy_frame[data->enemies[i]->current_frame];
    drawframe = NULL;
    drawframe = mlx_new_image(data->mlx, current->width, current->height);
    if (!drawframe)
        free_all_and_quit(data, "sprite frame draw error", 35);
    ft_memcpy(drawframe->pixels, current->pixels, current->width * current->height * sizeof(uint32_t));
    printf("distance was: %f\n", data->enemies[i]->distance);
    new_height = (ESH * 20 / (int)data->enemies[i]->distance);
    new_width = (ESW * 20 / (int)data->enemies[i]->distance);
    //printf("new width: %d\n", new_width);
    //printf("new height: %d\n", new_height);
    if (mlx_resize_image(drawframe, new_width, new_height) != 1)
        free_all_and_quit(data, "sprite frame resize error", 35);
    screen_y = data->mlx->height / 2 - new_height / 2;
    draw_image_onto_image(data->enemy_img, drawframe, screen_x, screen_y);
    //mlx_image_to_window(data->mlx, drawframe, screen_x, screen_y);
}

void	hook_enemies(t_data *data)
{
    // relative position of enemy to player
    int     i;
    float   dx;
    float   dy;
    float   angle;
    float   rel_angle;
    int     screen_x;

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
            data->enemies[i]->visible = 1;
            draw_enemy(data, i, screen_x);
        }
    } 
    mlx_image_to_window(data->mlx, data->enemy_img, 0, 0); 
}