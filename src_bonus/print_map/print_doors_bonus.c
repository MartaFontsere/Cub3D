/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:39:56 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 23:52:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	compute_door_draw_limits(t_game *gdata, t_print_door *print_door)
{
	print_door->door_height = gdata->map.px_height / print_door->distance;
	print_door->draw_start = (gdata->map.px_height / 2)
		- (print_door->door_height / 2);
	print_door->draw_end = (gdata->map.px_height / 2) + (print_door->door_height
			/ 2);
	if (print_door->draw_start < 0)
		print_door->draw_start = 0;
	if (print_door->draw_end >= gdata->map.px_height)
		print_door->draw_end = gdata->map.px_height - 1;
}

void	draw_door_texture_slice(t_game *gdata, t_image *texture, int *row,
		int *column)
{
	t_print_door	*print_door;
	int				tex_y;

	print_door = &gdata->print_map.print_door;
	*row = print_door->draw_start;
	while (*row <= print_door->draw_end)
	{
		tex_y = (int)((*row - print_door->draw_start) * print_door->tex_y_ratio
				+ print_door->tex_start_offset);
		if (tex_y < 0)
			tex_y = 0;
		if ((uint32_t)tex_y >= texture->xpm->texture.height)
			tex_y = texture->xpm->texture.height - 1;
		gdata->print_map.color = get_texture_pixel(texture, print_door->tex_x,
				tex_y);
		mlx_put_pixel(gdata->mlx.image, *column, *row, gdata->print_map.color);
		(*row)++;
	}
}

void	print_door_column(t_game *gdata, int *row, int *column,
		t_print_door *print_door)
{
	t_image	*texture;

	texture = &gdata->texture.door_img;
	print_door = &gdata->print_map.print_door;
	compute_door_draw_limits(gdata, print_door);
	print_door->tex_y_ratio = (double)texture->xpm->texture.height
		/ print_door->door_height;
	draw_door_texture_slice(gdata, texture, row, column);
}

void	print_door(t_game *gdata, t_ray *ray, int *row, int *column)
{
	t_print_door	*print_door;
	t_image			*texture;

	print_door = &gdata->print_map.print_door;
	print_door->distance = ray->perpendicular_distance;
	texture = &gdata->texture.door_img;
	get_column(gdata, ray, &print_door->wall_x);
	get_texture_column(texture, &print_door->wall_x, &print_door->tex_x);
	get_texture_row(gdata, texture, &print_door->tex_start_offset);
	print_door_column(gdata, row, column, print_door);
}
