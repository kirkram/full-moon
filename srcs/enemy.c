/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/08 15:33:31 by mburakow         ###   ########.fr       */
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
            if ((dest_x + pt.x) >= 0 && (uint32_t)(dest_x + pt.x) < dest->width &&
                (dest_y + pt.y) >= 0 && (uint32_t)(dest_y + pt.y) < dest->height) {
                mlx_put_pixel(dest, dest_x + pt.x, dest_y + pt.y, pt.color);
            }
        }
        pt.y = -1;
    }
}

// Here account for not visible: skip drawing: partially visible: draw partially
void    draw_enemy(t_data *data, int i, uint32_t screen_x)
{
    mlx_image_t*    current;
    mlx_image_t*    drawframe;
    int             new_width;
    int             new_height;
    uint32_t        screen_y;

    printf("screen x: %u\n", screen_x);
    current = data->enemy_frame[data->enemies[i]->current_frame];
    drawframe = NULL;
    drawframe = mlx_new_image(data->mlx, current->width, current->height);
    if (!drawframe)
        free_all_and_quit(data, "sprite frame draw error", 35);
    ft_memcpy(drawframe->pixels, current->pixels, current->width * current->height * sizeof(uint32_t));
    printf("distance was: %f\n", data->enemies[i]->distance);
    if (data->enemies[i]->distance < 1.0)
        data->enemies[i]->distance = 1.0;
    new_height = (int)(ESH * 20 / data->enemies[i]->distance);
    new_width = (int)(ESW * 20 / data->enemies[i]->distance);
    //printf("new width: %d\n", new_width);
    //printf("new height: %d\n", new_height);
    if (mlx_resize_image(drawframe, new_width, new_height) != 1)
        free_all_and_quit(data, "sprite frame resize error", 35);
    screen_x = screen_x - new_width / 2;
    screen_y = data->mlx->height / 2 - new_height / 2;
    printf("Enemy sx:%u sy:%u\n", screen_x, screen_y);
    draw_image_onto_image(data->enemy_img, drawframe, screen_x, screen_y);
    mlx_delete_image(data->mlx, drawframe);
}

void	hook_enemies(t_data *data)
{
    // relative position of enemy to player
    int         i;
    float       dx;
    float       dy;
    float       angle;
    float       rel_angle;
    uint32_t     screen_x;

    i = -1;
    while (data->enemies[++i] != NULL)
    {
        dx = data->enemies[i]->x_pos - data->player->x_pos;
        dy = data->enemies[i]->y_pos - data->player->y_pos;
        printf("player angle: %f\n", data->player->angle);
        data->enemies[i]->distance = sqrtf(dx * dx + dy * dy);
        angle = atan2(dy, dx);
        printf("angle: %f\n", angle);
        rel_angle = angle - data->player->angle; // - angle;
        rel_angle = atan2f(sinf(rel_angle), cosf(rel_angle));
        printf("REL angle: %f\n", angle);
        if (rel_angle >= -rad(FOV / 2) && rel_angle <= rad(FOV / 2))
        {
            screen_x = (uint32_t)((rel_angle + rad(FOV / 2)) / rad(FOV) * data->width);
            printf("screen x: %u", screen_x);
            data->enemies[i]->visible = 1;
            draw_enemy(data, i, screen_x);
        }
        else
            data->enemies[i]->visible = 0;
    } 
    mlx_image_to_window(data->mlx, data->enemy_img, 0, 0); 
}