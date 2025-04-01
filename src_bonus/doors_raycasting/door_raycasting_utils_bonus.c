/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycasting_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:08 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void vertical_coords_convert (t_ray *ray, t_game *gdata)
{
	ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);
    ray->diagonal_distance = ((ray->px_collision_x / gdata->minimap.px_in_cell_width) - gdata->player.cell_player_x) / ray->dir_x;
    ray->px_collision_y = gdata->player.y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  
}     

void horizontal_coords_convert (t_ray *ray, t_game *gdata)
{
	ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);
    ray->diagonal_distance = ((ray->px_collision_y / gdata->minimap.px_in_cell_height) - gdata->player.cell_player_y) / ray->dir_y;
    ray->px_collision_x = gdata->player.x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;       
}


void update_door_vertical_coords (t_ray *ray, double first_dist_x_tmp, int check_ray_x_in_map_tmp, int line_crossing)
{
	ray->first_dist_x = first_dist_x_tmp;
    ray->check_ray_x_in_map = check_ray_x_in_map_tmp;
    ray->line_crossing = line_crossing;
}

void update_door_horizontal_coords (t_ray *ray, double first_dist_y_tmp, int check_ray_y_in_map_tmp, int line_crossing)
{
	ray->first_dist_y = first_dist_y_tmp;
    ray->check_ray_y_in_map = check_ray_y_in_map_tmp;
    ray->line_crossing = line_crossing;
}
