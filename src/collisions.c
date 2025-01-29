/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/27 22:14:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_collision(t_game *gdata, double target_x, double target_y)
{
	int cell_x;
    int cell_y;
    double angle;
    double angle_step;

    angle = 0;
    angle_step = M_PI / 36;

    while (angle <= 2 * M_PI)
    {
        double contour_x = target_x + gdata->player.radius * cos(angle);
        double contour_y = target_y + gdata->player.radius * sin(angle);
         mlx_put_pixel(gdata->mlx.image, contour_x, contour_y, YELLOW1);

        cell_x = (int)(contour_x / gdata->minimap.cell_width);
        cell_y = (int)(contour_y / gdata->minimap.cell_height);

        if (gdata->map.matrix[cell_y][cell_x] == '1')
            return 0;

        angle += angle_step;
    }

    return 1;
}
