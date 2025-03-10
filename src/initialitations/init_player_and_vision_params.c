/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_vision_params.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:47:23 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/26 21:57:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player_position(t_game *gdata, t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S' || map->matrix[i][j] == 'E' || map->matrix[i][j] == 'W')
			{
				player->raw_x = j;
				player->raw_y = i;
			}
			j++;
		}
		i++;
	}
	player->x = (player->raw_x * gdata->minimap.px_in_cell_width) + (gdata->minimap.px_in_cell_width / 2);
	player->y = (player->raw_y * gdata->minimap.px_in_cell_height) + (gdata->minimap.px_in_cell_height / 2);
	// printf ("posicion en x |%f|\n", player->x);
	// printf ("posicion en y |%f|\n", player->y);
	// printf ("cos del angulo |%f|\n", cos(gdata->player.ray.vision_angle));
	// printf ("sen del angulo |%f|\n", sin(gdata->player.ray.vision_angle));
	// printf ("posicion 2 en x |%f|\n", player->x);
	// printf ("posicion 2 en y |%f|\n", player->y);
	// player->midle_x = player->x + (gdata->minimap.px_in_cell_width / 2);
	// player->midle_y = player->y + (gdata->minimap.px_in_cell_height / 2);
}

void	init_player_orientation(t_map *map, t_vision *vision)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] == 'N')
			{
				vision->vision_angle = NORTH;
				break;
			}
			if (map->matrix[i][j] == 'S')
			{
				vision->vision_angle = SOUTH;
				break;
			}
			if (map->matrix[i][j] == 'E')
			{
				vision->vision_angle = EAST;
				break;
			}
			if (map->matrix[i][j] == 'W')
			{
				vision->vision_angle = WEST;
				break;
			}
			j++;
		}
		i++;
	}	
}

void init_player_parameters (t_game *gdata, t_player *player)
{
	player->raw_x = 0;
	player->raw_y = 0;
	player->mov_right = 0; 
	player->mov_left = 0;
	player->mov_up = 0;
	player->mov_down = 0;
	player->rotate_right = 0;
	player->rotate_left = 0;
	player->height = gdata->minimap.px_height / 2;
	player->radius = gdata->minimap.px_in_cell_width / 4;	
	init_player_position(gdata, &gdata->map, player); // TENGO QUE MANDARLO COMO PUNTERO O NO CAL PORQUE GDATA YA LO ES?
	init_player_orientation(&gdata->map, &gdata->vision);
}

int init_vision_parameters (t_game *gdata, t_vision *vision)
{
	//vision->last_vision_angle = NORTH;
	vision->FOV.num_rays = gdata->map.px_width;
	vision->FOV.fov_rad = 60 * (M_PI / 180); // 60° a radianes
	vision->FOV.rays = malloc (sizeof (t_ray) * vision->FOV.num_rays);
	if (!vision->FOV.rays)
	{
		write_error("Unable to allocate memory for FOV rays");
		//REVISAR TODO LO QUE HAY QUE LIBERAR
		return (0);
	}

	//PARA EL SUELO
	vision->projection_factor = (gdata->map.px_height / 2) / tan(vision->FOV.fov_rad / 2); // Es como un factor de escala que convierte distancias del mundo 2D (minimapa) en una altura en la pantalla (3D), asegurando que los objetos más lejanos sean más pequeños y los cercanos sean más grandes.
	vision->camera_height_scale = gdata->player.height * vision->projection_factor; // SI LA ALTURA DEL JUGADOR CAMBIARA, ESTO SE TENDRIA QUE IR RECALCULANDO
	// camera_height_scale Es la cantidad de pixeles que corresponde a la altura del jugador, ya escalada para la proyección.
	//Por ejemplo, si el jugador mide 1.75 pixeles y el projection factor (derivado del FOV y la altura de la pantalla) es 415, 
	//el constant factor sería aproximadamente 1.75 * 415 = 726.25. 
	//Esto quiere decir que, en términos de proyección, 726.25 pixeles se distribuyen verticalmente desde el centro de la pantalla 
	//(en el eje de la proyección)
	//se trata de un factor que escala (o transforma) la altura del jugador a las dimensiones de la proyección en pantalla. 
	//Este valor se usa para ajustar la altura de la cámara o del jugador a la escala de la imagen renderizada.
	
	return (1);
}