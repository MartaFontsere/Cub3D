/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 05:04:06 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 05:05:07 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_wall_column(t_game *gdata, t_ray *ray, double *wall_x)
{
	if (ray->line_crossing == 0)
		*wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_width;
	else
		*wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;
	*wall_x = *wall_x - floor(*wall_x);
}

void	get_texture_column(t_image *texture, double *wall_x, int *tex_x)
{
	*tex_x = (int)(*wall_x * texture->xpm->texture.width);
	if (*tex_x < 0)
		*tex_x = 0;
	if ((uint32_t) * tex_x >= texture->xpm->texture.width)
		*tex_x = texture->xpm->texture.width - 1;
}

void	get_texture_row(t_game *gdata, t_image *texture,
		double *tex_start_offset)
{
	*tex_start_offset = 0;
	if (gdata->print_map.wall_height > gdata->map.px_height)
		*tex_start_offset = ((gdata->print_map.wall_height
					- gdata->map.px_height) / 2.0)
			* ((double)texture->xpm->texture.height
				/ gdata->print_map.wall_height);
}

void	print_wall_column(t_game *gdata, int *row, int *column,
		t_image *texture)
{
	double	tex_y_ratio;
	int		tex_y;
	int		tex_x;

	tex_y_ratio = (double)texture->xpm->texture.height
		/ gdata->print_map.wall_height;
	tex_x = gdata->print_map.tex_x;
	while (*row <= gdata->print_map.draw_wall_end)
	{
		tex_y = (int)((*row - gdata->print_map.draw_wall_start) * tex_y_ratio
				+ gdata->print_map.tex_start_offset);
		if (tex_y < 0)
			tex_y = 0;
		if ((uint32_t)tex_y >= texture->xpm->texture.height)
			tex_y = texture->xpm->texture.height - 1;
		gdata->print_map.color = get_texture_pixel(texture, tex_x, tex_y);
		mlx_put_pixel(gdata->mlx.image, *column, *row, gdata->print_map.color);
		(*row)++;
	}
}

void	print_texture_walls(t_game *gdata, t_ray *ray, int *row, int *column)
{
	double	wall_x;
	t_image	*texture;

	texture = get_wall_texture(ray, gdata);
	get_wall_column(gdata, ray, &wall_x);
	get_texture_column(texture, &wall_x, &gdata->print_map.tex_x);
	get_texture_row(gdata, texture, &gdata->print_map.tex_start_offset);
	print_wall_column(gdata, row, column, texture);
}
