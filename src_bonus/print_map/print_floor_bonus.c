/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:08:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 03:13:58 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_floor_pixel(t_game *gdata, t_ray *ray, int column, int row)
{
	t_image	*texture;
	double	dist;
	double	row_offset;
	int		color;

	texture = &gdata->texture.floor_img;
	row_offset = row - (gdata->map.px_height / 2.0);
	if (row_offset <= 0)
		return ;
	dist = (gdata->player.height * gdata->vision.projection_factor)
		/ row_offset;
	dist = dist / gdata->print_map.print_floor.view_angle_correction;
	compute_floor_world_coords(gdata, &gdata->print_map.print_floor, ray, dist);
	compute_texture_coords(&gdata->print_map.print_floor, texture);
	color = get_texture_pixel(texture, gdata->print_map.print_floor.tex_x,
			gdata->print_map.print_floor.tex_y);
	mlx_put_pixel(gdata->mlx.image, column, row, color);
}

void	print_floor_texture(t_game *gdata, t_ray *ray, int row, int column)
{
	double	scale;
	double	row_offset;

	scale = 12.0;
	gdata->print_map.print_floor.view_angle_correction = cos(ray->current_angle
			- gdata->vision.vision_angle);
	gdata->print_map.print_floor.inv_scale_x = 1.0
		/ (gdata->minimap.px_in_cell_width * scale);
	gdata->print_map.print_floor.inv_scale_y = 1.0
		/ (gdata->minimap.px_in_cell_height * scale);
	if (row <= gdata->print_map.draw_wall_end)
		row = gdata->print_map.draw_wall_end + 1;
	while (row < gdata->map.px_height)
	{
		row_offset = row - (gdata->map.px_height / 2.0);
		if (row_offset > 0)
			draw_floor_pixel(gdata, ray, column, row);
		row++;
	}
}

void	print_floor_color(t_game *gdata, int row, int column)
{
	t_mlx	mlx;

	mlx = gdata->mlx;
	gdata->texture.f_hex_color = rgb_to_hex(gdata->texture.path.f.r,
			gdata->texture.path.f.g, gdata->texture.path.f.b);
	while (row < gdata->map.px_height)
	{
		mlx_put_pixel(mlx.image, column, row, gdata->texture.f_hex_color);
		row++;
	}
}

void	print_floor(t_game *gdata, t_ray *ray, int row, int column)
{
	if (!gdata->texture.path.f.is_path)
		print_floor_color(gdata, row, column);
	else
		print_floor_texture(gdata, ray, row, column);
}
