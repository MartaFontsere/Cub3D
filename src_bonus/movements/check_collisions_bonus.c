/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 20:24:12 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_collision_x(t_game *gdata, t_player player, double target_x)
{
	double	angle;
	double	angle_step;
	int		cell_x;
	int		cell_y;

	angle = 0;
	angle_step = M_PI / 36;
	while (angle <= 2 * M_PI)
	{
		player.collision.contour_x = target_x + (player.radius) * cos(angle);
		player.collision.contour_y = player.y + (player.radius) * sin(angle);
		cell_x = (int)(player.collision.contour_x
				/ gdata->minimap.px_in_cell_width);
		cell_y = (int)(player.collision.contour_y
				/ gdata->minimap.px_in_cell_height);
		if (gdata->map.matrix[cell_y][cell_x] == '1')
			return (0);
		angle += angle_step;
	}
	return (1);
}

int	check_collision_y(t_game *gdata, t_player player, double target_y)
{
	double	angle;
	double	angle_step;
	int		cell_x;
	int		cell_y;

	angle = 0;
	angle_step = M_PI / 36;
	while (angle <= 2 * M_PI)
	{
		player.collision.contour_x = player.x + (player.radius) * cos(angle);
		player.collision.contour_y = target_y + (player.radius) * sin(angle);
		cell_x = (int)(player.collision.contour_x
				/ gdata->minimap.px_in_cell_width);
		cell_y = (int)(player.collision.contour_y
				/ gdata->minimap.px_in_cell_height);
		if (gdata->map.matrix[cell_y][cell_x] == '1')
			return (0);
		angle += angle_step;
	}
	return (1);
}
