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
	gdata->map_info.rawmap = NULL;
	gdata->map_info.map = NULL;
	gdata->map_info.map_width = 0;
	gdata->map_info.map_height = 0;
	gdata->window_height = 0;
	gdata->window_width = 0;
	gdata->player.x = 0;
	gdata->player.y = 0;
	gdata->player.orientation = NORTH;





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

void	init_player_position(t_map *map_info, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S' || map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
			{
				player->x = j;
				player->y = i;
			}
			j++;
		}
		i++;
	}
	player->cell_x = (double)player->x + 0.5;
	player->cell_y = (double)player->y + 0.5;
}

void	init_player_orientation(t_map *map_info, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == 'N')
			{
				player->orientation = NORTH;
				break;
			}
			if (map_info->map[i][j] == 'S')
			{
				player->orientation = SOUTH;
				break;
			}
			if (map_info->map[i][j] == 'E')
			{
				player->orientation = EAST;
				break;
			}
			if (map_info->map[i][j] == 'W')
			{
				player->orientation = WEST;
				break;
			}
			j++;
		}
		i++;
	}
}


int	init_mlx(t_game *gdata, t_mlx *mlx)
{
	// gdata->window_width = SPRITES_WIDTH * gdata->map_width;
	// gdata->window_height = SPRITES_HEIGHT * gdata->map_height;

	gdata->window_width = 1701; // CAMBIAR, ESTA HARDCODEADO
	gdata->window_height = 701; // CAMBIAR, ESTA HARDCODEADO

	mlx->init = mlx_init((gdata->window_width), (gdata->window_height),
			"The Game", true);
	if (!mlx->init)
	{
		write_error("It's not possible to initialize the mlx");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	game->img = mlx_new_image(game->mlx, WIN_WITH + 1, WIN_LEN + 1);
	while (y < game->map.max_y)
	{
		x = 0;
		while (x < game->map.max_x)
		{
			if (game->map.map[y][x] == '1')
				mlx_put_pixel(game->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	return (1);
}
