/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/09 22:45:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_gdata_values(t_game *gdata)
{
	gdata->map.rawmap = NULL;
	gdata->map.matrix = NULL;
	gdata->map.cells_width = 20;// ESTA HARDCODEADO
	gdata->map.cells_height = 20; //ESTA HARDCODEADO
	gdata->map.px_width = PX_MAP_WIDTH;// ESTA HARDCODEADO
	gdata->map.px_height = PX_MAP_HEIGHT; //ESTA HARDCODEADO
	gdata->mlx.window_width = PX_MAP_WIDTH;
	gdata->mlx.window_height = PX_MAP_HEIGHT;
	gdata->player.raw_x = 0;
	gdata->player.raw_y = 0;
	gdata->player.x = 0;
	gdata->player.y = 0;
	gdata->player.mov_right = 0;
	gdata->player.mov_left = 0;
	gdata->player.mov_up = 0;
	gdata->player.mov_down = 0;
	gdata->player.rotate_right = 0;
	gdata->player.rotate_left = 0;


	gdata->finish_game = 0;
}

int init_vision_parameters (t_game *gdata, t_vision *vision)
{
	vision->last_vision_angle = NORTH;
	vision->FOV.num_rays = gdata->mlx.window_width;
	//vision->FOV.num_rays = gdata->minimap.px_width; // CAMBIAR, ES EL TAMAÑO DE LA VENTANA, NO DEL MINIMAPA
	vision->FOV.fov_rad = 60 * (M_PI / 180); // 60° a radianes
	vision->FOV.rays = malloc (sizeof (t_ray) * vision->FOV.num_rays);
	if (!vision->FOV.rays)
	{
		write_error("Unable to allocate memory for lightning");
		//REVISAR TODO LO QUE HAY QUE LIBERAR
		return (0);
	}
	return (1);
}

void init_player_parameters (t_game *gdata, t_player *player)
{
	init_player_position(gdata, &gdata->map, player); // TENGO QUE MANDARLO COMO PUNTERO O NO CAL PORQUE GDATA YA LO ES?
	init_player_orientation(&gdata->map, &gdata->vision);
	player->radius = gdata->minimap.px_in_cell_width / 4;

	
}

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

void	init_minimap(t_game *gdata, t_map *map)
{
	gdata->minimap.px_width = PX_MINIMAP_WIDTH;
	gdata->minimap.px_height = PX_MINIMAP_HEIGHT;
	gdata->minimap.px_in_cell_width = gdata->minimap.px_width / map->cells_width;
	gdata->minimap.px_in_cell_height = gdata->minimap.px_height / map->cells_height;
}


int	init_mlx(t_mlx *mlx)
{
	// gdata->window_width = SPRITES_WIDTH * gdata->map_width;
	// gdata->window_height = SPRITES_HEIGHT * gdata->map_height;

	mlx->init = mlx_init(mlx->window_width, mlx->window_height,
			"The Game", true); // ESTO CAMBIARA, LAS MEDIDAS DE LA VENTANA
	if (!mlx->init)
	{
		write_error("It's not possible to initialize the mlx");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}

int	create_new_images(t_game *gdata, t_mlx *mlx)
{
	mlx->image = mlx_new_image(mlx->init, mlx->window_width, mlx->window_height);
	printf ("window: %d, %d\n",  mlx->window_width,mlx->window_height);
	if (!mlx->image)
	{
		write_error("It's not possible to generate new image");
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	mlx->mini_image = mlx_new_image(mlx->init, gdata->minimap.px_width, gdata->minimap.px_height);
	if (!mlx->mini_image)
	{
		write_error("It's not possible to generate new mini_image");
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}
