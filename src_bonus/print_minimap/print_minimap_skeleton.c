/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_skeleton.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 04:44:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_player(t_game *gdata, t_player player, int x, int y)
{

    int draw_x;
    int draw_y;
   	int x_limit;
    int y_limit;

    draw_y = y - player.radius;
    x_limit = x + player.radius;
    y_limit = y + player.radius;
    while (draw_y <= y_limit) {
        draw_x = x - player.radius;
        while (draw_x <= x_limit) {
            if ((draw_x - x) * (draw_x - x) + (draw_y - y) * (draw_y - y) <= player.radius * player.radius) {
                mlx_put_pixel(gdata->mlx.mini_image, (int)draw_x, (int)draw_y, RED1);  // Color del jugador en el centro
            }
            draw_x++;
        }
        draw_y++;
    }
}


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

void	render_pixel(t_game *gdata, int pixel_x, int pixel_y)
{
	int	matrix_cell_x;
	int	matrix_cell_y;
	char cell;

	matrix_cell_x = (gdata->print_minimap.start_x + pixel_x) / gdata->minimap.px_in_cell_width;
	matrix_cell_y = (gdata->print_minimap.start_y + pixel_y) / gdata->minimap.px_in_cell_height;

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
	print_player(gdata, gdata->player, gdata->minimap.center_x, gdata->minimap.center_y);
}
