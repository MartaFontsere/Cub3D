/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/27 22:51:07 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void check_horizontal_door(t_ray *ray, t_door door_ray, t_game *gdata, int *check_ray_y_in_map)
{
	double door_midpoint;

	door_midpoint = 0;
	if (ray->line_crossing == 1)
    	update_door_horizontal_coords (ray, door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, door_ray.line_crossing_tmp);
    else if (ray->line_crossing == 0)
    {
    	vertical_coords_convert (ray,gdata);
        if (ray->y_sign > 0)
        {

            door_midpoint = (*check_ray_y_in_map + 0.5) * gdata->minimap.px_in_cell_height;
            if (ray->px_collision_y > door_midpoint)
                update_door_vertical_coords (ray, door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, 1);
        }
        else if (ray->y_sign < 0)
        {
            door_midpoint = (*check_ray_y_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_height;
            if (ray->px_collision_y < door_midpoint)
                 update_door_vertical_coords (ray, door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, 1);
        }  
    }
}

void check_vertical_door(t_ray *ray, t_door door_ray, t_game *gdata, int *check_ray_x_in_map)
{
	double door_midpoint;

	door_midpoint = 0;
	if (ray->line_crossing == 0)
    	update_door_vertical_coords (ray, door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, door_ray.line_crossing_tmp);

    else if (ray->line_crossing == 1)
    {
    	horizontal_coords_convert (ray, gdata);
    	if (ray->x_sign > 0)
        {
            door_midpoint = (*check_ray_x_in_map + 0.5) * gdata->minimap.px_in_cell_width;
            if (ray->px_collision_x > door_midpoint)
            	 update_door_horizontal_coords (ray, door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, 0);
        }
        else if (ray->x_sign < 0)
        {
            door_midpoint = (*check_ray_x_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_width;
            if (ray->px_collision_x < door_midpoint)
            	update_door_horizontal_coords (ray, door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, 0);
        }  
    }
}

void door_raycast (t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map)
{
	ray->door_ray.line_crossing_tmp = ray->line_crossing;
    ray->door_ray.check_ray_y_in_map_tmp = *check_ray_y_in_map;
    ray->door_ray.check_ray_x_in_map_tmp = *check_ray_x_in_map;
    ray->door_ray.first_dist_x_tmp = ray->first_dist_x;
    ray->door_ray.first_dist_y_tmp = ray->first_dist_y;
    check_matrix_lines (ray, check_ray_x_in_map, check_ray_y_in_map);
    if (ray->door_ray.line_crossing_tmp == 1)
    	check_horizontal_door(ray, ray->door_ray, gdata, check_ray_y_in_map);
    if (ray->door_ray.line_crossing_tmp == 0)
    	check_vertical_door(ray, ray->door_ray, gdata, check_ray_x_in_map);    
}
