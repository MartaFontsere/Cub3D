/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/22 03:27:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_gdata_values(t_game *gdata)
{
	gdata->map.rawmap = NULL;
	gdata->map.matrix = NULL;
	gdata->map.width = 0;
	gdata->map.height = 0;
	gdata->mlx.window_height = 0;
	gdata->mlx.window_width = 0;
	gdata->player.raw_x = 0;
	gdata->player.raw_y = 0;
	gdata->player.x = 0;
	gdata->player.y = 0;
	gdata->player.orientation = NORTH;
	gdata->player.mov_right = 0;
	gdata->player.mov_left = 0;
	gdata->player.mov_up = 0;
	gdata->player.mov_down = 0;


	gdata->finish_game = 0;





	// gdata->player.mov_right = 0;
	// gdata->player.mov_left = 0;
	// gdata->player.mov_up = 0;
	// gdata->player.mov_down = 0;
	// gdata->exit_x = 0;
	// gdata->exit_y = 0;
	// gdata->player.speed = 0;
	// gdata->num_collectibles = 0;
	// gdata->loop_clock = 0;
	// gdata->portal_clock = 0;
	// gdata->end_images_loaded = 0;
	// gdata->finish_game = 0;
}

void init_player_parameters (t_game *gdata, t_player *player)
{

	init_player_position(gdata, &gdata->map, &gdata->player);
	init_player_orientation(&gdata->map, &gdata->player);
	player->radius = gdata->minimap.cell_width / 4;

	
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
	player->x = (player->raw_x * gdata->minimap.cell_width);
	player->y = (player->raw_y * gdata->minimap.cell_height);
	player->midle_x = (player->raw_x * gdata->minimap.cell_width) + (gdata->minimap.cell_width / 2);
	player->midle_y = (player->raw_y * gdata->minimap.cell_height) + (gdata->minimap.cell_height / 2);
}

void	init_player_orientation(t_map *map, t_player *player)
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
				player->orientation = NORTH;
				break;
			}
			if (map->matrix[i][j] == 'S')
			{
				player->orientation = SOUTH;
				break;
			}
			if (map->matrix[i][j] == 'E')
			{
				player->orientation = EAST;
				break;
			}
			if (map->matrix[i][j] == 'W')
			{
				player->orientation = WEST;
				break;
			}
			j++;
		}
		i++;
	}
	player->vision_angle = (double)player->orientation;
}

void	init_minimap(t_game *gdata, t_map *map)
{
	gdata->minimap.width = 1500; // CAMBIAR, ESTA HARDCODEADO
	gdata->minimap.height = 1500; // CAMBIAR, ESTA HARDCODEADO
	gdata->minimap.cell_width = gdata->minimap.width / map->width;
	gdata->minimap.cell_height = gdata->minimap.height / map->height;
	
}

int	init_mlx_and_create_new_image(t_game *gdata, t_mlx *mlx)
{
	// gdata->window_width = SPRITES_WIDTH * gdata->map_width;
	// gdata->window_height = SPRITES_HEIGHT * gdata->map_height;

	mlx->init = mlx_init((gdata->minimap.width), (gdata->minimap.height),
			"The Game", true); // ESTO CAMBIARA, LAS MEDIDAS DE LA VENTANA
	if (!mlx->init)
	{
		write_error("It's not possible to initialize the mlx");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	mlx->image = mlx_new_image(mlx->init, gdata->minimap.width, gdata->minimap.height);
	if (!mlx->image)
	{
		write_error("It's not possible to generate new image");
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}
