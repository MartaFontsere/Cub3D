/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/13 17:35:22 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_fov(t_game *gdata, double x, double y)
{
	double	start_angle;
	double	end_angle;
	double	angle_step;
	int		i;

	start_angle = gdata->vision.vision_angle + (gdata->vision.FOV.fov_rad / 2);
	end_angle = gdata->vision.vision_angle - (gdata->vision.FOV.fov_rad / 2);
	angle_step = (end_angle - start_angle) / gdata->vision.FOV.num_rays;
	gdata->player.cell_player_x = x / gdata->minimap.px_in_cell_width;
	gdata->player.cell_player_y = y / gdata->minimap.px_in_cell_height;
	i = 0;
	gdata->vision.FOV.rays[i].current_angle = start_angle;
	while (i < gdata->vision.FOV.num_rays)
	{
		calculate_ray(gdata, &gdata->vision.FOV.rays[i], x, y);
		if (i + 1 < gdata->vision.FOV.num_rays)
			gdata->vision.FOV.rays[i
				+ 1].current_angle = gdata->vision.FOV.rays[i].current_angle
				+ angle_step;
		i++;
	}
}
