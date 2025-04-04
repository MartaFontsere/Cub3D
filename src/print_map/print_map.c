/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 03:31:10 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_floor(t_game *gdata, t_mlx mlx, int *row, int *column)
{
	gdata->texture.f_hex_color = rgb_to_hex(gdata->texture.path.f.r,
			gdata->texture.path.f.g, gdata->texture.path.f.b);
	while (*row < gdata->map.px_height)
	{
		mlx_put_pixel(mlx.image, *column, *row, gdata->texture.f_hex_color);
		(*row)++;
	}
}

void	print_sky(t_game *gdata, t_mlx mlx, int *row, int *column)
{
	gdata->texture.c_hex_color = rgb_to_hex(gdata->texture.path.c.r,
			gdata->texture.path.c.g, gdata->texture.path.c.b);
	while (*row < gdata->print_map.draw_wall_start)
	{
		mlx_put_pixel(mlx.image, *column, *row, gdata->texture.c_hex_color);
		(*row)++;
	}
}

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

void	print_map(t_game *gdata, t_mlx mlx, t_map map)
{
	int		column;
	int		row;
	t_ray	*ray;

	column = 0;
	while (column < gdata->vision.fov.num_rays)
	{
		row = 0;
		ray = &gdata->vision.fov.rays[column];
		prepare_print_params(gdata, ray, map);
		print_sky(gdata, mlx, &row, &column);
		print_texture_walls(gdata, ray, &row, &column);
		print_floor(gdata, mlx, &row, &column);
		column++;
	}
}
