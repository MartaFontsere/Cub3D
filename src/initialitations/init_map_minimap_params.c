/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_minimap_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:05:26 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 03:29:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	gdata->vision.fov.rays = NULL;
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
