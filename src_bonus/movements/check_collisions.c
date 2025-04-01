/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 02:08:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_collision_x(t_game *gdata, double target_x)
{
    int cell_x;
    int cell_y;
    double angle;
    double angle_step;

    angle = 0;
    angle_step = M_PI / 36;

    while (angle <= 2 * M_PI)
    {
        double contour_x = target_x + (gdata->player.radius) * cos(angle);
        double contour_y = gdata->player.y + (gdata->player.radius) * sin(angle);
        cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
        cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);
        if (gdata->map.matrix[cell_y][cell_x] == '1')
            return 0;
        angle += angle_step;
    }

    return 1;
}

int check_collision_y(t_game *gdata, double target_y)
{
    int cell_x;
    int cell_y;
    double angle;
    double angle_step;

    angle = 0;
    angle_step = M_PI / 36;

    while (angle <= 2 * M_PI)
    {
        double contour_x = gdata->player.x + (gdata->player.radius) * cos(angle);
        double contour_y = target_y + (gdata->player.radius) * sin(angle);
         cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
         cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);
       if (gdata->map.matrix[cell_y][cell_x] == '1')
            return 0;
        angle += angle_step;
    }

    return 1;

}