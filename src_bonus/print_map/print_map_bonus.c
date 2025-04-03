/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/02 23:35:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	prepare_print_params(t_game *gdata, t_ray *ray, t_map map)
{
	gdata->print_map.wall_height = map.px_height / ray->perpendicular_distance;
	gdata->print_map.draw_wall_start = (map.px_height / 2)
		- (gdata->print_map.wall_height / 2);
	gdata->print_map.draw_wall_end = (map.px_height / 2)
		+ (gdata->print_map.wall_height / 2);
	if (gdata->print_map.draw_wall_start < 0)
		gdata->print_map.draw_wall_start = 0;
	if (gdata->print_map.draw_wall_end >= map.px_height)
		gdata->print_map.draw_wall_end = map.px_height - 1;
}

void	print_map(t_game *gdata, t_map map)
{
	int		column;
	int		row;
	t_ray	*ray;

	column = 0;
	while (column < gdata->vision.FOV.num_rays)
	{
		row = 0;
		ray = &gdata->vision.FOV.rays[column];
		prepare_print_params(gdata, ray, map);
		print_sky(gdata, ray, &row, column);
		print_texture_walls(gdata, ray, &row, &column);
		print_floor(gdata, ray, row, column);
		column++;
	}
}
