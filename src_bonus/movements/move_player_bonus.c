/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 04:51:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	prepare_next_position(t_game *gdata, t_vision vision, double *move_x,
		double *move_y)
{
	if (gdata->player.mov_up == 1)
	{
		*move_x -= MOVE_SPEED * -cos(vision.vision_angle);
		*move_y -= MOVE_SPEED * sin(vision.vision_angle);
	}
	if (gdata->player.mov_down == 1)
	{
		*move_x += MOVE_SPEED * -cos(vision.vision_angle);
		*move_y += MOVE_SPEED * sin(vision.vision_angle);
	}
	if (gdata->player.mov_right == 1)
	{
		*move_x += MOVE_SPEED * cos(vision.vision_angle - M_PI_2);
		*move_y += MOVE_SPEED * -sin(vision.vision_angle - M_PI_2);
	}
	if (gdata->player.mov_left == 1)
	{
		*move_x += MOVE_SPEED * cos(vision.vision_angle + M_PI_2);
		*move_y += MOVE_SPEED * -sin(vision.vision_angle + M_PI_2);
	}
}

void	move_player(t_game *gdata, t_vision vision, double *target_x,
		double *target_y)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	prepare_next_position(gdata, vision, &move_x, &move_y);
	if (check_collision_x(gdata, *target_x + move_x)) {
        *target_x += move_x;  // Actualizar X si no hay colisión
    }
    if (check_collision_y(gdata, *target_y + move_y)) {
        *target_y += move_y;  // Actualizar Y si no hay colisión
    }
}
