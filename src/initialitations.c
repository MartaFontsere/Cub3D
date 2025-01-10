/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 01:42:52 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_gdata_values(t_game *gdata)
{
	gdata->map_info->rawmap = NULL;
	gdata->map_info->map = NULL;
	gdata->map_info->map_width = 0;
	gdata->map_info->map_height = 0;
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

void	init_player_position(t_game *gdata)
{
	int	i;
	int	j;

	i = 0;
	while (gdata->map[i])
	{
		j = 0;
		while (gdata->map[i][j])
		{
			if (gdata->map[i][j] == 'N' || gdata->map[i][j] == 'S' || gdata->map[i][j] == 'E' || gdata->map[i][j] == 'W')
			{
				gdata->player.x = j;
				gdata->player.y = i;
			}
			j++;
		}
		i++;
	}
}
void	init_player_orientation(t_game *gdata)
{
	int	i;
	int	j;

	i = 0;
	while (gdata->map[i])
	{
		j = 0;
		while (gdata->map[i][j])
		{
			if (gdata->map[i][j] == 'N')
			{
				gdata->player.orientation = NORTH;
				break;
			}
			if (gdata->map[i][j] == 'S')
			{
				gdata->player.orientation = SOUTH;
				break;
			}
			if (gdata->map[i][j] == 'E')
			{
				gdata->player.orientation = EAST;
				break;
			}
			if (gdata->map[i][j] == 'W')
			{
				gdata->player.orientation = WEST;
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
		free_raw_and_map(gdata);
		return (0);
	}
	return (1);
}
