/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_collision_coordinates.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:36:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 00:47:27 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	prepare_horizontal_final_collision_params(t_ray *ray, t_game *gdata,
		double y)
{
	ray->cell_collision_x = ray->check_ray_x_map;
	ray->cell_collision_y = ray->check_ray_y_map;
	if (gdata->map.matrix[ray->check_ray_y_map][ray->check_ray_x_map] == 'D'
		|| gdata->map.matrix[ray->check_ray_y_map][ray->check_ray_x_map] == 'd')
	{
		if (ray->x_sign > 0)
			ray->px_collision_x = compute_collision_coord(ray->check_ray_x_map,
					ray->x_sign, gdata->minimap.px_in_cell_width)
				+ (gdata->minimap.px_in_cell_width / 2);
		else
			ray->px_collision_x = compute_collision_coord(ray->check_ray_x_map,
					ray->x_sign, gdata->minimap.px_in_cell_width)
				- (gdata->minimap.px_in_cell_width / 2);
	}
	else
		ray->px_collision_x = compute_collision_coord(ray->check_ray_x_map,
				ray->x_sign, gdata->minimap.px_in_cell_width);
	ray->diagonal_distance = ((ray->px_collision_x
				/ gdata->minimap.px_in_cell_width)
			- gdata->player.cell_player_x) / ray->dir_x;
	ray->px_collision_y = y + (ray->diagonal_distance
			* gdata->minimap.px_in_cell_height) * ray->dir_y;
}

void	prepare_vertical_final_collision_params(t_ray *ray, t_game *gdata,
		double x)
{
	ray->cell_collision_x = ray->check_ray_x_map;
	ray->cell_collision_y = ray->check_ray_y_map;
	if (gdata->map.matrix[ray->check_ray_y_map][ray->check_ray_x_map] == 'D'
		|| gdata->map.matrix[ray->check_ray_y_map][ray->check_ray_x_map] == 'd')
	{
		if (ray->y_sign > 0)
			ray->px_collision_y = compute_collision_coord(ray->check_ray_y_map,
					ray->y_sign, gdata->minimap.px_in_cell_height)
				+ (gdata->minimap.px_in_cell_height / 2);
		else
			ray->px_collision_y = compute_collision_coord(ray->check_ray_y_map,
					ray->y_sign, gdata->minimap.px_in_cell_height)
				- (gdata->minimap.px_in_cell_height / 2);
	}
	else
		ray->px_collision_y = compute_collision_coord(ray->check_ray_y_map,
				ray->y_sign, gdata->minimap.px_in_cell_height);
	ray->diagonal_distance = ((ray->px_collision_y
				/ gdata->minimap.px_in_cell_height)
			- gdata->player.cell_player_y) / ray->dir_y;
	ray->px_collision_x = x + (ray->diagonal_distance
			* gdata->minimap.px_in_cell_width) * ray->dir_x;
}
