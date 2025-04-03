/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:58:24 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/02 17:37:04 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_checkerboard_pixel(t_game *gdata, int pixel_x, int pixel_y)
{
	if ((pixel_x / 4) % 2 == (pixel_y / 4) % 2)
		mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, BLACK);
	else
		mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, MEDIUM_GREY);
}

void	draw_cell_pixel(t_game *gdata, char cell, int pixel_x, int pixel_y)
{

	if (cell == '1')
		mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, SOFT_GREY);
	else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
		mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, DARK_GREY);
	else if (cell == 'D' || cell == 'd')
		mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, BLUE1);
	else
		draw_checkerboard_pixel(gdata, pixel_x, pixel_y);
}

int	is_valid_matrix_cell(t_game *gdata, int  matrix_cell_x, int matrix_cell_y)
{
	if (matrix_cell_x >= 0 && matrix_cell_x < gdata->map.c_width && matrix_cell_y >= 0 && matrix_cell_y < gdata->map.c_height)
		return 1;
	return 0;
}

int	is_out_of_bounds(t_game *gdata, int pixel_x, int pixel_y)
{
	int map_px_width = gdata->minimap.px_in_cell_width * gdata->map.c_width;
	int map_px_height = gdata->minimap.px_in_cell_height * gdata->map.c_height;

	if (gdata->print_minimap.start_x + pixel_x < 0 || gdata->print_minimap.start_y + pixel_y < 0)
		return 1;
	if (gdata->print_minimap.start_x + pixel_x >= map_px_width || gdata->print_minimap.start_y + pixel_y >= map_px_height)
		return 1;
	return 0;
}

