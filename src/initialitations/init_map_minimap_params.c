/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_minimap_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:06:18 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/25 18:16:20 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
 #include "cub3D.h"

void init_map (t_map *map)
{
	// map->rawmap = NULL;
	// map->matrix = NULL;
	map->cells_width = 20;// cantidad de celdas ancho ESTA HARDCODEADO - SUSTITUIR CON PARSING YAJAIRA
	map->cells_height = 20; //cantidad de celdas alto ESTA HARDCODEADO - SUSTITUIR CON PARSING YAJAIRA
	map->px_width = MAP_PX_WIDTH; //ancho de ventana maximo en pixeles 
	map->px_height = MAP_PX_HEIGHT; //alto de ventana maximo en pixeles 
	printf("map->px_width= |%d|\n", map->px_width);
}

void	init_minimap(t_game *gdata, t_map *map)
{
	gdata->minimap.px_width = MINIMAP_PX_WIDTH; //ancho de minimapa maximo en pixeles 
	gdata->minimap.px_height = MINIMAP_PX_HEIGHT; //alto de minimapa maximo en pixeles 
	gdata->minimap.px_in_cell_width = gdata->minimap.px_width / map->cells_width; // cantidad de pixeles de ancho por casilla
	gdata->minimap.px_in_cell_height = gdata->minimap.px_height / map->cells_height;//cantidad de pixeles de alto por casilla
}
