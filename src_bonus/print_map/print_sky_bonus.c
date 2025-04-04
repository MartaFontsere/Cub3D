/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sky_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:54:17 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 13:31:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_sky_slice(t_game *gdata, int tex_x_start, int column, int *row)
{
	t_image	*sky_texture;
	int		tex_y;
	int		tex_x;
	int		color;

	sky_texture = &gdata->texture.sky_img;
	while (*row < gdata->print_map.draw_wall_start)
	{
		tex_y = compute_tex_y(gdata, *row, sky_texture->xpm->texture.height);
		tex_x = (tex_x_start + column) % sky_texture->xpm->texture.width;
		color = get_texture_pixel(sky_texture, tex_x, tex_y);
		mlx_put_pixel(gdata->mlx.image, column, *row, color);
		(*row)++;
	}
}

void	print_sky_texture(t_game *gdata, t_ray *ray, int *row, int column)
{
	double	sky_offset_x;
	int		tex_x_start;
	t_image	*sky_texture;

	sky_offset_x = compute_sky_offset_x(gdata, ray);
	sky_texture = &gdata->texture.sky_img;
	tex_x_start = (int)(sky_offset_x * sky_texture->xpm->texture.width);
	*row = 0;
	draw_sky_slice(gdata, tex_x_start, column, row);
}

void	print_sky_color(t_game *gdata, int *row, int column)
{
	t_mlx	mlx;

	mlx = gdata->mlx;
	gdata->texture.c_hex_color = rgb_to_hex(gdata->texture.path.c.r,
			gdata->texture.path.c.g, gdata->texture.path.c.b);
	while (*row < gdata->print_map.draw_wall_start)
	{
		mlx_put_pixel(mlx.image, column, *row, gdata->texture.c_hex_color);
		(*row)++;
	}
}

void	print_sky(t_game *gdata, t_ray *ray, int *row, int column)
{
	if (!gdata->texture.path.f.is_path)
		print_sky_color(gdata, row, column);
	else
		print_sky_texture(gdata, ray, row, column);
}
