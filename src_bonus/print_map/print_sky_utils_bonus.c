/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sky_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:30:00 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 20:30:29 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	compute_sky_offset_x(t_game *gdata, t_ray *ray)
{
	double	offset;

	offset = -ray->current_angle / (2 * M_PI);
	offset += gdata->player.x * 0.0005;
	offset = fmod(offset, 1.0);
	if (offset < 0)
		offset += 1.0;
	return (offset);
}

int	compute_tex_y(t_game *gdata, int row, int tex_height)
{
	double	vertical_offset;
	double	screen_ratio;
	int		tex_y;

	vertical_offset = gdata->player.y * 0.0005;
	screen_ratio = (double)(row - (gdata->mlx.window_height / 4))
		/ (gdata->mlx.window_height / 4);
	tex_y = (int)((0.5 + screen_ratio * 0.5 + vertical_offset) * tex_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return (tex_y);
}
