/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 01:42:50 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	release_key(mlx_key_data_t keydata, t_game *gdata)
{
	if (keydata.key == MLX_KEY_RIGHT)
		gdata->player.mov_right = 0;
	else if (keydata.key == MLX_KEY_LEFT)
		gdata->player.mov_left = 0;
	else if (keydata.key == MLX_KEY_UP)
		gdata->player.mov_up = 0;
	else if (keydata.key == MLX_KEY_DOWN)
		gdata->player.mov_down = 0;
}


void	reset_mov_params(t_game *gdata)
{
	gdata->player.mov_right = 0;
	gdata->player.mov_left = 0;
	gdata->player.mov_up = 0;
	gdata->player.mov_down = 0;
}

void	set_mov_params(t_game *gdata, int *move_direction)
{
	reset_mov_params(gdata);
	*move_direction = 1;
	//gdata->player.orientation = orient;
}


void	press_key(mlx_key_data_t keydata, void *param)
{
	t_game	*gdata;

	gdata = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		close_window(gdata);
		return ;
	}
	if (gdata->finish_game == 0 && keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_RIGHT)
			set_mov_params(gdata, &gdata->player.mov_right);
		else if (keydata.key == MLX_KEY_LEFT)
			set_mov_params(gdata, &gdata->player.mov_left);
		else if (keydata.key == MLX_KEY_UP)
			set_mov_params(gdata, &gdata->player.mov_up);
		else if (keydata.key == MLX_KEY_DOWN)
			set_mov_params(gdata, &gdata->player.mov_down);
	}
	if (gdata->finish_game == 0 && keydata.action == MLX_RELEASE)
		release_key(keydata, gdata);
}

int	there_is_a_key_pressed(t_game *gdata)
{
	if (gdata->player.mov_right == 1)
		return (1);
	if (gdata->player.mov_left == 1)
		return (1);
	if (gdata->player.mov_up == 1)
		return (1);
	if (gdata->player.mov_down == 1)
		return (1);
	return (0);
}

