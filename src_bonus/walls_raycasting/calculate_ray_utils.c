/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:02 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 02:49:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void check_matrix_lines (t_ray *ray, int *check_ray_x_in_map, int *check_ray_y_in_map)
{
	if (ray->first_dist_x < ray->first_dist_y)
		{
			ray->first_dist_x += ray->other_dist_x;
			*check_ray_x_in_map += ray->x_sign;
			ray->line_crossing = 0;
		}
		else
		{
			ray->first_dist_y += ray->other_dist_y;
			*check_ray_y_in_map += ray->y_sign;
			ray->line_crossing = 1;
		}

}

double	compute_collision_coordinate(int check_ray_coord, int ray_sign,
		double px_in_cell_size)
{
	if (ray_sign > 0)
		return (check_ray_coord * px_in_cell_size);
	else
		return ((check_ray_coord + 1) * px_in_cell_size);
}

void	controll_y_limit_case(t_ray *ray, int check_ray_y_in_map,
		double cell_player_y)
{
	if (fabs(ray->dir_y) < 1e-6)
	{
		ray->other_dist_y = 1e6;
		ray->first_dist_y = 1e6;
		ray->y_sign = 0;
	}
	else
	{
		ray->other_dist_y = fabs(1 / ray->dir_y);
		if (ray->dir_y < 0)
		{
			ray->y_sign = -1;
			ray->first_dist_y = (cell_player_y - check_ray_y_in_map)
				* ray->other_dist_y;
		}
		else
		{
			ray->y_sign = 1;
			ray->first_dist_y = ((check_ray_y_in_map + 1) - cell_player_y)
				* ray->other_dist_y;
		}
	}
}

void	controll_x_limit_case(t_ray *ray, int check_ray_x_in_map,
		double cell_player_x)
{
	if (fabs(ray->dir_x) < 1e-6)
	{
		ray->other_dist_x = 1e6;
		ray->first_dist_x = 1e6;
		ray->x_sign = 0;
	}
	else
	{
		ray->other_dist_x = fabs(1 / ray->dir_x);
		if (ray->dir_x < 0)
		{
			ray->x_sign = -1;
			ray->first_dist_x = (cell_player_x - check_ray_x_in_map)
				* ray->other_dist_x;
		}
		else
		{
			ray->x_sign = 1;
			ray->first_dist_x = ((check_ray_x_in_map + 1) - cell_player_x)
				* ray->other_dist_x;
		}
	}
}

void    prepare_horizontal_final_collision_params(t_ray *ray, t_game *gdata, double y)
{
    ray->cell_collision_x = ray->check_ray_x_in_map;
    ray->cell_collision_y = ray->check_ray_y_in_map;
    if (gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'D' || gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'd')
        {
            if (ray->x_sign > 0)
                ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width) + (gdata->minimap.px_in_cell_width / 2);
            else
                ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width) - (gdata->minimap.px_in_cell_width / 2); 
        }
        else 
            ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);

    ray->diagonal_distance = ((ray->px_collision_x / gdata->minimap.px_in_cell_width) - gdata->player.cell_player_x) / ray->dir_x;
        ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  
}

void    prepare_vertical_final_collision_params(t_ray *ray, t_game *gdata, double x)
{
    ray->cell_collision_x = ray->check_ray_x_in_map;
    ray->cell_collision_y = ray->check_ray_y_in_map;
    if (gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'D' || gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'd')
        {
            if (ray->y_sign > 0)
                ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height) + (gdata->minimap.px_in_cell_height / 2);
            else
                ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height) - (gdata->minimap.px_in_cell_height / 2);
        }
        else
            ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);

    ray->diagonal_distance = ((ray->px_collision_y / gdata->minimap.px_in_cell_height) - gdata->player.cell_player_y) / ray->dir_y;
        ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;
}