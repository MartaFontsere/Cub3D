/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors_status_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 19:03:27 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	get_distance_to_door(t_game *gdata, int door_x, int door_y)
{
	double	door_center_x;
	double	door_center_y;
	double	dx;
	double	dy;
	double	distance_px;

	door_center_x = (door_x + 0.5) * gdata->minimap.px_in_cell_width;
	door_center_y = (door_y + 0.5) * gdata->minimap.px_in_cell_height;
	dx = door_center_x - gdata->player.x;
	dy = door_center_y - gdata->player.y;
	distance_px = sqrt(dx * dx + dy * dy);
	return (distance_px / gdata->minimap.px_in_cell_width);
}

void	update_single_door(t_game *gdata, int x, int y)
{
	double	distance;
	char	*cell;

	cell = &gdata->map.matrix[y][x];
	if (*cell == 'D')
	{
		distance = get_distance_to_door(gdata, x, y);
		if (distance < DOOR_START_OPEN_DISTANCE)
			*cell = 'd';
	}
	else if (*cell == 'd')
	{
		distance = get_distance_to_door(gdata, x, y);
		if (distance > DOOR_START_OPEN_DISTANCE + 0.5)
			*cell = 'D';
	}
}

void	update_doors(t_game *gdata)
{
	int	door_y;
	int	door_x;

	door_y = 0;
	while (door_y < gdata->map.c_height)
	{
		door_x = 0;
		while (door_x < gdata->map.c_width)
		{
			update_single_door(gdata, door_x, door_y);
			door_x++;
		}
		door_y++;
	}
}
