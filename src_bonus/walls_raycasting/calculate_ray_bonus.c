/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 02:36:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_ray_direction(t_ray *ray, t_game *gdata, int check_ray_x_in_map,
		int check_ray_y_in_map)
{
	ray->dir_x = cos(ray->current_angle);
	ray->dir_y = -sin(ray->current_angle);
	controll_x_limit_case(ray, check_ray_x_in_map, gdata->player.cell_player_x);
	controll_y_limit_case(ray, check_ray_y_in_map, gdata->player.cell_player_y);
}

void	traverse_ray_until_hit(t_ray *ray, t_game *gdata,
		int *check_ray_x_in_map, int *check_ray_y_in_map)
{
	int	wall_hit;

	ray->hit_door = 0; // Resetear por si quedó de un rayo anterior
	wall_hit = 0;
	while (wall_hit == 0)
	{

        if (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == 'D' || (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == 'd' && should_block_ray(ray, gdata, *check_ray_x_in_map, *check_ray_y_in_map)))
        {
        	door_raycast(ray, gdata, check_ray_x_in_map, check_ray_y_in_map);
        	break;
        }
		check_matrix_lines (ray, check_ray_x_in_map, check_ray_y_in_map);
		if (*check_ray_x_in_map < 0 || *check_ray_x_in_map >= gdata->map.c_width
			|| *check_ray_y_in_map < 0
			|| *check_ray_y_in_map >= gdata->map.c_height)
			break ;
		if (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == '1')
			wall_hit = 1;
	}
}

void	find_ray_distance_and_collision_point(t_ray *ray, t_game *gdata,
		double x, double y)
{
	if (ray->line_crossing == 0)
		prepare_horizontal_final_collision_params (ray, gdata, y);
	else
		prepare_vertical_final_collision_params (ray, gdata, x);
ray->perpendicular_distance = ray->diagonal_distance * cos(ray->current_angle - gdata->vision.vision_angle);
}

void	calculate_ray(t_game *gdata, t_ray *ray, double x, double y)
{
	ray->check_ray_x_in_map = (int)(x / gdata->minimap.px_in_cell_width);
	ray->check_ray_y_in_map = (int)(y / gdata->minimap.px_in_cell_height);
	init_ray_direction(ray, gdata, ray->check_ray_x_in_map,
		ray->check_ray_y_in_map);
	traverse_ray_until_hit(ray, gdata, &ray->check_ray_x_in_map,
		&ray->check_ray_y_in_map);
	find_ray_distance_and_collision_point(ray, gdata, x, y);
}
