/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 14:15:01 by mfontser         ###   ########.fr       */
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

void	init_player_position(t_map *map, t_player *player)
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
	// player->cell_x = (double)player->x + 0.5;
	// player->cell_y = (double)player->y + 0.5;

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

void	init_minimap(t_game *gdata, t_map *map, t_player *player)
{
	gdata->minimap.width = 2000; // CAMBIAR, ESTA HARDCODEADO
	gdata->minimap.height = 2000; // CAMBIAR, ESTA HARDCODEADO
	gdata->minimap.cell_width = gdata->minimap.width / map->width;
	gdata->minimap.cell_height = gdata->minimap.height / map->height;
	gdata->minimap.player_x = (player->raw_x * gdata->minimap.cell_width) + (gdata->minimap.cell_width / 2);
	gdata->minimap.player_y = (player->raw_y * gdata->minimap.cell_height) + (gdata->minimap.cell_height / 2);
	gdata->minimap.player_radius = gdata->minimap.cell_width / 5;
}

int	init_mlx(t_game *gdata, t_mlx *mlx)
{
	// gdata->window_width = SPRITES_WIDTH * gdata->map_width;
	// gdata->window_height = SPRITES_HEIGHT * gdata->map_height;

	mlx->init = mlx_init((gdata->minimap.width), (gdata->minimap.height),
			"The Game", true);
	if (!mlx->init)
	{
		write_error("It's not possible to initialize the mlx");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	gdata->minimap.background_img = mlx_new_image(mlx->init, gdata->minimap.width, gdata->minimap.height); //PORQUE +1?????
	if (!gdata->minimap.background_img)
	{
		write_error("It's not possible to generate new image");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}
