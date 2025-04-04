/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_rotation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:38:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 20:17:25 by mfontser         ###   ########.fr       */
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
	if (gdata->player.cursor_on == 1)
	{
		if (gdata->player.last_xpos == -1)
			gdata->player.last_xpos = xpos;
		else
		{
			rotation_speed = 0.007;
			gdata->player.new_xpos = xpos;
			if (gdata->player.last_xpos < gdata->player.new_xpos)
				cursor_rotation(rotation_speed, gdata, 0);
			else if (gdata->player.last_xpos > gdata->player.new_xpos)
				cursor_rotation(rotation_speed, gdata, 1);
			gdata->player.last_xpos = xpos;
		}
		if (xpos < 720.0f || xpos > 1600.0f)
			mlx_set_mouse_pos(gdata->mlx.init, MAP_PX_WIDTH / 2, 500);
		mlx_set_cursor_mode(gdata->mlx.init, MLX_MOUSE_HIDDEN);
	}
	else
		gdata->player.last_xpos = -1;
}
