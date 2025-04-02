/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_or_release_key_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/02 16:46:39 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	cursor_rotation(double rotation_speed, t_game *gdata, int flag)
{
	if (flag == 0)
	{
		gdata->vision.vision_angle -= rotation_speed;
		if (gdata->vision.vision_angle > 2 * M_PI)
			gdata->vision.vision_angle -= 2 * M_PI;
	}
	else if (flag == 1)
	{
		gdata->vision.vision_angle += rotation_speed;
		if (gdata->vision.vision_angle < 0)
			gdata->vision.vision_angle += 2 * M_PI;
	}
}

void	cursor_handle(double xpos, double ypos, void *param)
{
	double	rotation_speed;
	t_game	*gdata;

	(void)ypos;
	gdata = param;
 	if (gdata->player.cursor_on == 1)//si el cursor esta activado
	{
		if (gdata->player.last_xpos == -1)
			gdata->player.last_xpos = xpos;
		else
		{
			rotation_speed = 0.007;
			gdata->player.new_xpos = xpos;
			if (gdata->player.last_xpos < gdata->player.new_xpos)//si la anterior pos es < que la nueva, 0 porque esta yendo a la derecha
				cursor_rotation(rotation_speed, gdata, 0);
			else if (gdata->player.last_xpos > gdata->player.new_xpos)//si last > que la nueva, 1 porque va a la izquierda
				cursor_rotation(rotation_speed, gdata, 1);
			gdata->player.last_xpos = xpos;
		}
		if (xpos < 720.0f || xpos > 1600.0f)//rango  en el que quiero que se mueva el raton. Si es mayor, vuelve al centro
			mlx_set_mouse_pos(gdata->mlx.init, MAP_PX_WIDTH / 2, 500);
		mlx_set_cursor_mode(gdata->mlx.init, MLX_MOUSE_HIDDEN);//oculta el raton
	}	
	else
		gdata->player.last_xpos = -1;//para que el valor de last pos se asigne con la pos actual desde donde se ha activado el cursor
}

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
		else if (keydata.key == MLX_KEY_M && gdata->player.cursor_on == 0)//AQUI_CURSOR
			gdata->player.cursor_on = 1;
		else if (keydata.key == MLX_KEY_M && gdata->player.cursor_on == 1)//AQUI_CURSOR
			gdata->player.cursor_on = 0;
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
	if (gdata->player.cursor_on == 1)
		return (1);
	return (0);
}
