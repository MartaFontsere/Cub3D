/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:58:24 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 12:59:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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