/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:57:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_textures_and_colors_path(t_texture *texture, t_path *path)
{
	texture->north_wall_img.data = NULL;
	texture->south_wall_img.data = NULL;
	texture->west_wall_img.data = NULL;
	texture->east_wall_img.data = NULL;
	path->NO = NULL;
	path->SO = NULL;
	path->EA = NULL;
	path->WE = NULL;
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->C.R = 0;
	path->C.G = 0;
	path->C.B = 0;
	path->C.path = path;
	path->C.assigned = 0;
	path->F.R = 0;
	path->F.G = 0;
	path->F.B = 0;
	path->F.path = path;
	path->F.assigned = 0;
	texture->sky_img.data = NULL;
	texture->floor_img.data = NULL;
	texture->door_img.data = NULL;
	texture->dragon_img[0].data = NULL;
}

void	init_map_params(t_game *gdata, t_map *map)
{
	map->matrix = NULL;
	map->tmp_matrix = NULL;
	map->void_matrix = NULL;
	map->is_map = 0;
	map->j = 0;
	map->c_width = 0;
	map->c_height = 0;
	map->px_width = MAP_PX_WIDTH;
	map->px_height = MAP_PX_HEIGHT;
	gdata->vision.FOV.rays = NULL;
}

void	init_minimap_params(t_game *gdata)
{
	gdata->minimap.px_width = MINIMAP_PX_WIDTH;
	gdata->minimap.px_height = MINIMAP_PX_HEIGHT;
	gdata->minimap.px_in_cell_width = MINIMAP_PX_CELL_WIDTH;
	gdata->minimap.px_in_cell_height = MINIMAP_PX_CELL_HEIGHT;
	gdata->minimap.center_x = gdata->minimap.px_width / 2;
	gdata->minimap.center_y = gdata->minimap.px_height / 2;
}

int	init_gdata_values(t_game *gdata)
{
	gdata->finish_game = 0;
	init_minimap_params(gdata);
	init_player_params(gdata, &gdata->player);
	if (init_vision_params(gdata, &gdata->vision) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (init_mlx(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (create_new_images(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (put_image_to_window(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}
