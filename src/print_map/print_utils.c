/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:32:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 01:58:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

t_image	*get_wall_texture(t_ray *ray, t_game *gdata)
{
	if (ray->line_crossing == 1)
	{
		if (ray->y_sign == 1)
			return (&gdata->texture.south_wall_img);
		else
			return (&gdata->texture.north_wall_img);
	}
	else
	{
		if (ray->x_sign == 1)
			return (&gdata->texture.east_wall_img);
		else
			return (&gdata->texture.west_wall_img);
	}
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int			index;
	uint8_t		*pixel;
	uint32_t	color;

	if (tex_x < 0 || (uint32_t)tex_x >= texture->xpm->texture.width || tex_y < 0
		|| (uint32_t)tex_y >= texture->xpm->texture.height)
		return (0x000000);
	index = (tex_y * texture->xpm->texture.width + tex_x) * 4;
	pixel = &texture->xpm->texture.pixels[index];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}
