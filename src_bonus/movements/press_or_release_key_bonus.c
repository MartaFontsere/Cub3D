/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_or_release_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:57:52 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	release_key(mlx_key_data_t keydata, t_game *gdata)
{
	if (keydata.key == MLX_KEY_D)
		gdata->player.mov_right = 0;
	else if (keydata.key == MLX_KEY_A)
		gdata->player.mov_left = 0;
	else if (keydata.key == MLX_KEY_W)
		gdata->player.mov_up = 0;
	else if (keydata.key == MLX_KEY_S)
		gdata->player.mov_down = 0;
	else if (keydata.key == MLX_KEY_RIGHT)
		gdata->player.rotate_right = 0;
	else if (keydata.key == MLX_KEY_LEFT)
		gdata->player.rotate_left = 0;
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
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_D)
			gdata->player.mov_right = 1;
		else if (keydata.key == MLX_KEY_A)
			gdata->player.mov_left = 1;
		else if (keydata.key == MLX_KEY_W)
			gdata->player.mov_up = 1;
		else if (keydata.key == MLX_KEY_S)
			gdata->player.mov_down = 1;
		else if (keydata.key == MLX_KEY_RIGHT)
			gdata->player.rotate_right = 1;
		else if (keydata.key == MLX_KEY_LEFT)
			gdata->player.rotate_left = 1;
	}
	if (keydata.action == MLX_RELEASE)
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
	if (gdata->player.rotate_right == 1)
		return (1);
	if (gdata->player.rotate_left == 1)
		return (1);
	return (0);
}
