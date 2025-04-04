/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 00:04:02 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calculate_and_print_fov_and_vision_angle(t_game *gdata)
{
	calculate_fov(gdata, gdata->player.x, gdata->player.y);
	print_fov(gdata, gdata->vision, gdata->minimap.center_x,
		gdata->minimap.center_y);
	print_vision_angle(gdata, gdata->player.x, gdata->player.y, gdata->vision);
}

void	render_pixel(t_game *gdata, int pixel_x, int pixel_y)
{
	int		matrix_cell_x;
	int		matrix_cell_y;
	char	cell;

	matrix_cell_x = (gdata->print_minimap.start_x + pixel_x)
		/ gdata->minimap.px_in_cell_width;
	matrix_cell_y = (gdata->print_minimap.start_y + pixel_y)
		/ gdata->minimap.px_in_cell_height;
	if (is_out_of_bounds(gdata, pixel_x, pixel_y))
		draw_checkerboard_pixel(gdata, pixel_x, pixel_y);
	else if (is_valid_matrix_cell(gdata, matrix_cell_x, matrix_cell_y))
	{
		cell = gdata->map.matrix[matrix_cell_y][matrix_cell_x];
		draw_cell_pixel(gdata, cell, pixel_x, pixel_y);
	}
	else
		draw_checkerboard_pixel(gdata, pixel_x, pixel_y);
}

void	browse_minimap_pixels(t_game *gdata)
{
	int	pixel_y;
	int	pixel_x;

	pixel_y = 0;
	while (pixel_y < gdata->minimap.px_height)
	{
		pixel_x = 0;
		while (pixel_x < gdata->minimap.px_width)
		{
			render_pixel(gdata, pixel_x, pixel_y);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	print_minimap(t_game *gdata)
{
	gdata->print_minimap.start_x = gdata->player.x - gdata->minimap.center_x;
	gdata->print_minimap.start_y = gdata->player.y - gdata->minimap.center_y;
	browse_minimap_pixels(gdata);
	calculate_and_print_fov_and_vision_angle(gdata);
	print_player(gdata, gdata->player, gdata->minimap.center_x,
		gdata->minimap.center_y);
}
