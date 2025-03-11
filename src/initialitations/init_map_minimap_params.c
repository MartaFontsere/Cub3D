/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_minimap_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:06:18 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 01:46:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
 #include "cub3D.h"

// void init_floor_and_ceil_colors (t_texture *texture) 
// {
// 	//ESTO LO HACE YA YAJA??????
// 	texture->path.C.R = CEELING_R; 
// 	texture->path.C.G = CEELING_G;
// 	texture->path.C.B = CEELING_B;
// 	texture->path.F.R = FLOOR_R;
// 	texture->path.F.G = FLOOR_G;
// 	texture->path.F.B = FLOOR_B;
// }

void init_map_params (t_map *map)
{
	map->matrix = NULL;
	map->tmp_matrix = NULL;
	map->void_matrix = NULL;
	map->is_map = 0;
	map->j = 0;
	map->c_width = 0; // cantidad de celdas ancho
	map->c_height = 0; //cantidad de celdas alto
	// map->c_width = 20;// cantidad de celdas ancho ESTA HARDCODEADO - SUSTITUIR CON PARSING YAJAIRA
	// map->c_height = 20; //cantidad de celdas alto ESTA HARDCODEADO - SUSTITUIR CON PARSING YAJAIRA
	map->px_width = MAP_PX_WIDTH; //ancho de ventana maximo en pixeles 
	map->px_height = MAP_PX_HEIGHT; //alto de ventana maximo en pixeles 
	printf("map->px_width= |%d|\n", map->px_width);
	printf("map->px_height= |%d|\n", map->px_height);
	//init_floor_and_ceil_colors (&gdata->texture);
}

void	init_minimap_params(t_game *gdata)
{
	gdata->minimap.px_width = MINIMAP_PX_WIDTH; //ancho de minimapa maximo en pixeles 
	gdata->minimap.px_height = MINIMAP_PX_HEIGHT; //alto de minimapa maximo en pixeles 
	
	// minimapa proporcional
	// gdata->minimap.px_in_cell_width = gdata->minimap.px_width / map->c_width; // cantidad de pixeles de ancho por casilla
	// gdata->minimap.px_in_cell_height = gdata->minimap.px_height / map->c_height;//cantidad de pixeles de alto por casilla
	
	//minimapa fijo
	gdata->minimap.px_in_cell_width = MINIMAP_PX_CELL_WIDTH; // cantidad de pixeles de ancho por casilla
	gdata->minimap.px_in_cell_height = MINIMAP_PX_CELL_HEIGHT;//cantidad de pixeles de alto por casilla
	printf("minimap.px_in_cell_width= |%d|\n", gdata->minimap.px_in_cell_width);
	printf("minimap.px_in_cell_height= |%d|\n", gdata->minimap.px_in_cell_height);
	




	// gdata->minimap.c_width = gdata->minimap.px_width / gdata->minimap.px_in_cell_width;
	// gdata->minimap.c_height = gdata->minimap.px_height / gdata->minimap.px_in_cell_height;
	// printf("minimap.c_width= |%d|\n", gdata->minimap.c_width);
	// printf("minimap.c_height= |%d|\n", gdata->minimap.c_height);
	// // Asegurar que el número de celdas es impar para que, cuando imprimamos el minimapa, el jugador pueda estar exactamente en el centro
	// if (gdata->minimap.c_width % 2 == 0) 
	// 	gdata->minimap.c_width++;
	// if (gdata->minimap.c_height % 2 == 0) 
	// 	gdata->minimap.c_height++;

	//Determinar el centro del minimapa
	gdata->minimap.center_x = gdata->minimap.px_width / 2;  // Calcula la columna central del minimapa en pixels
	gdata->minimap.center_y = gdata->minimap.px_height / 2; // Calcula la fila central del minimapa en pixels
		printf ("minimap.center_x = %d\n", gdata->minimap.center_x);
	printf ("minimap.center_y = %d\n", gdata->minimap.center_y);

}
