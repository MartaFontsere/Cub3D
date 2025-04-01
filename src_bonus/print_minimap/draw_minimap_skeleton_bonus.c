/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_skeleton_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:55:17 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 12:55:55 by mfontser         ###   ########.fr       */
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