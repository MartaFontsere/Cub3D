/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/27 01:29:56 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_collision(t_game *gdata, double target_x, double target_y)
{
	int	cell_x;
	int	cell_y;

	gdata->collision.angle = 0;
	gdata->collision.angle_step = M_PI / 36;
	while (gdata->collision.angle <= 2 * M_PI)
	{
		gdata->collision.player_contour_x = target_x + gdata->player.radius
			* cos(gdata->collision.angle);
		gdata->collision.player_contour_y = target_y + gdata->player.radius
			* sin(gdata->collision.angle);
		cell_x = (int)(gdata->collision.player_contour_x
				/ gdata->minimap.px_in_cell_width);
		cell_y = (int)(gdata->collision.player_contour_y
				/ gdata->minimap.px_in_cell_height);
		if (gdata->map.matrix[cell_y][cell_x] == '1')
			return (0);
		gdata->collision.angle += gdata->collision.angle_step;
	}
	return (1);
}
