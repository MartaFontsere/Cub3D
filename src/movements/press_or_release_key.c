/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_or_release_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/26 23:46:06 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	release_key(mlx_key_data_t keydata, t_game *gdata)
{

	if (keydata.key == MLX_KEY_D)
	{
		printf("suelto D\n");
		gdata->player.mov_right = 0;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		printf("suelto A\n");
		gdata->player.mov_left = 0;
	}
	else if (keydata.key == MLX_KEY_W)
	{
		printf("suelto W\n");
		gdata->player.mov_up = 0;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		printf("suelto S\n");
		gdata->player.mov_down = 0;
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		gdata->player.rotate_right = 0;
		printf("suelto ->\n");
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		gdata->player.rotate_left = 0;
		printf("suelto <-\n");
	}
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
	if (/*gdata->finish_game == 0 && */keydata.action == MLX_PRESS)
	{
		printf ("*****entro\n");
		if (keydata.key == MLX_KEY_D)
		{
			gdata->player.mov_right = 1;
			printf("D\n");
		}
		else if (keydata.key == MLX_KEY_A)
		{
			gdata->player.mov_left = 1;
			printf("A\n");
		}
		else if (keydata.key == MLX_KEY_W)
		{
			gdata->player.mov_up = 1;
			printf("W\n");
		}
		else if (keydata.key == MLX_KEY_S)
		{
			gdata->player.mov_down = 1;
			printf("S\n");
		}
		else if (keydata.key == MLX_KEY_RIGHT)
		{
			gdata->player.rotate_right = 1;
			printf("->\n");
		}
		else if (keydata.key == MLX_KEY_LEFT)
		{
			gdata->player.rotate_left = 1;
			printf("<-\n");
		}
	}
	if (keydata.action == MLX_RELEASE)
		release_key(keydata, gdata);
}

//MLX_KEY_RIGHT

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

