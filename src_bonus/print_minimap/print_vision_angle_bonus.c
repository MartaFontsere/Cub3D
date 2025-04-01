/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vision_angle_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:24 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 15:22:50 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int can_draw_pixel(t_game *gdata, t_vision vision)
{
    int pixel_map_x;
    int pixel_map_y;
    char cell;

    pixel_map_x = (int)((gdata->player.x + vision.draw_va.offset_x) / gdata->minimap.px_in_cell_width);
   	pixel_map_y = (int)((gdata->player.y + vision.draw_va.offset_y) / gdata->minimap.px_in_cell_height);
    if (vision.draw_va.pixel_x < 0 || vision.draw_va.pixel_x >= gdata->minimap.px_width || vision.draw_va.pixel_y < 0 || vision.draw_va.pixel_y >= gdata->minimap.px_height)

    if (pixel_map_x < 0 || pixel_map_x >= gdata->map.c_width ||
        pixel_map_y < 0 || pixel_map_y >= gdata->map.c_height)
        return 0;

    cell = gdata->map.matrix[pixel_map_y][pixel_map_x];
    if (cell == '1' || cell == 'D' || cell == 'd')
        return 0;

    return 1;
}

void draw_thick_ray_segment(t_game *gdata, double current_x, double current_y, t_vision vision)
{
	double thickness;

    vision.draw.origin_x = gdata->minimap.center_x + (current_x - gdata->player.x);
    vision.draw.origin_y = gdata->minimap.center_y + (current_y - gdata->player.y);
    thickness = 0; 
    while (thickness <= 4)
    {
        vision.draw_va.offset_x = (int)(thickness * cos(vision.vision_angle + M_PI_2));
        vision.draw_va.offset_y = -(int)(thickness * sin(vision_vision_angle + M_PI_2));
        vision.draw_va.pixel_x = (int)(vision.draw_va.origin_x + vision.draw_va.offset_x);
        vision.draw_va.pixel_y = (int)(vision.draw_va.origin_y + vision.draw_va.offset_y);

        if (can_draw_pixel(gdata, vision_angle pixel_x, pixel_y, offset_x, offset_y))
            mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, YELLOW1);

        thickness += 0.1;
    }
}

int check_collision_in_y(t_game *gdata, double current_x, double next_y)
{
    int map_x = (int)(current_x / gdata->minimap.px_in_cell_width);
    int map_y = (int)(next_y / gdata->minimap.px_in_cell_height);

    if (map_y < 0 || map_y >= gdata->map.c_height)
        return 1;

    if (gdata->map.matrix[map_y][map_x] == '1' || gdata->map.matrix[map_y][map_x] == 'D' || gdata->map.matrix[map_y][map_x] == 'd')
        return 1;

    return 0;
}

int check_collision_in_x(t_game *gdata, double next_x, double current_y)
{
    int map_x = (int)(next_x / gdata->minimap.px_in_cell_width);
    int map_y = (int)(current_y / gdata->minimap.px_in_cell_height);

    if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
        return 1;

    if (gdata->map.matrix[map_y][map_x] == '1' || gdata->map.matrix[map_y][map_x] == 'D' || gdata->map.matrix[map_y][map_x] == 'd')
        return 1;

    return 0;
}

void print_vision_angle(t_game *gdata, double player_x, double player_y, t_vision vision)
{
    double current_x = player_x;
    double current_y = player_y;
    double dir_x = cos(vision_angle);
    double dir_y = -sin(vision_angle);

    while (1)
    {
        if (check_collision_in_x(gdata, current_x + dir_x, current_y))
            break;
        current_x += dir_x;

        if (check_collision_in_y(gdata, current_x, current_y + dir_y))
            break;
        current_y += dir_y;

        draw_thick_ray_segment(gdata, current_x, current_y, vision);
    }
}