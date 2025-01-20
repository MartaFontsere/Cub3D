/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/20 20:41:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	do_walking_animation(t_game *gdata, int target_y, int target_x)
{
	if (gdata->player.orientation == ORIENT_RIGHT)
		walking_right(gdata, animation_speed, target_y, target_x);
	if (gdata->player.orientation == ORIENT_LEFT)
		walking_left(gdata, animation_speed, target_y, target_x);
	if (gdata->player.orientation == ORIENT_UP)
		walking_up(gdata, animation_speed, target_y, target_x);
	if (gdata->player.orientation == ORIENT_DOWN)
		walking_down(gdata, animation_speed, target_y, target_x);
}
