/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:28:14 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 23:52:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	compute_floor_world_coords(t_game *gdata, t_print_floor *print_floor,
		t_ray *ray, double distance)
{
	print_floor->floor_x = gdata->player.x + ray->dir_x * distance;
	print_floor->floor_y = gdata->player.y + ray->dir_y * distance;
}

void	compute_texture_coords(t_print_floor *print_floor, t_image *texture)
{
	double	tex_unit_x;
	double	tex_unit_y;
	double	decimal_tex_unit_x;
	double	decimal_tex_unit_y;

	tex_unit_x = print_floor->floor_x * print_floor->inv_scale_x;
	tex_unit_y = print_floor->floor_y * print_floor->inv_scale_y;
	decimal_tex_unit_x = tex_unit_x - floor(tex_unit_x);
	decimal_tex_unit_y = tex_unit_y - floor(tex_unit_y);
	if (decimal_tex_unit_x < 0)
		decimal_tex_unit_x += 1.0;
	if (decimal_tex_unit_y < 0)
		decimal_tex_unit_y += 1.0;
	print_floor->tex_x = (int)(decimal_tex_unit_x
			* texture->xpm->texture.width);
	print_floor->tex_y = (int)(decimal_tex_unit_y
			* texture->xpm->texture.height);
	if (print_floor->tex_x >= texture->xpm->texture.width)
		print_floor->tex_x = texture->xpm->texture.width - 1;
	if (print_floor->tex_y >= texture->xpm->texture.height)
		print_floor->tex_y = texture->xpm->texture.height - 1;
}
