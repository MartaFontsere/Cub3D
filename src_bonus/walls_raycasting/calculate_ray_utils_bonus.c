/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:02 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 00:47:05 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_matrix_lines(t_ray *ray, int *check_ray_x_map,
		int *check_ray_y_map)
{
	if (ray->first_dist_x < ray->first_dist_y)
	{
		ray->first_dist_x += ray->other_dist_x;
		*check_ray_x_map += ray->x_sign;
		ray->line_crossing = 0;
	}
	else
	{
		ray->first_dist_y += ray->other_dist_y;
		*check_ray_y_map += ray->y_sign;
		ray->line_crossing = 1;
	}
}

double	compute_collision_coord(int check_ray_coord, int ray_sign,
		double px_in_cell_size)
{
	if (ray_sign > 0)
		return (check_ray_coord * px_in_cell_size);
	else
		return ((check_ray_coord + 1) * px_in_cell_size);
}

void	controll_y_limit_case(t_ray *ray, int check_ray_y_map,
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
			ray->first_dist_y = (cell_player_y - check_ray_y_map)
				* ray->other_dist_y;
		}
		else
		{
			ray->y_sign = 1;
			ray->first_dist_y = ((check_ray_y_map + 1) - cell_player_y)
				* ray->other_dist_y;
		}
	}
}

void	controll_x_limit_case(t_ray *ray, int check_ray_x_map,
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
			ray->first_dist_x = (cell_player_x - check_ray_x_map)
				* ray->other_dist_x;
		}
		else
		{
			ray->x_sign = 1;
			ray->first_dist_x = ((check_ray_x_map + 1) - cell_player_x)
				* ray->other_dist_x;
		}
	}
}
