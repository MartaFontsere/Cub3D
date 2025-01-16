/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 14:15:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	prepare_movement(t_game *gdata, int *target_x, int *target_y)
{
	static int	count = 0;

	if (gdata->player.mov_right == 1 && can_i_move_to(gdata, *target_x
			+ gdata->player.speed, *target_y))
		prepare_right_target(gdata, target_x, &count);
	else if (gdata->player.mov_left == 1 && can_i_move_to(gdata, *target_x
			- gdata->player.speed, *target_y))
		prepare_left_target(gdata, target_x, &count);
	else if (gdata->player.mov_up == 1 && can_i_move_to(gdata, *target_x,
			*target_y - gdata->player.speed))
		prepare_up_target(gdata, target_y, &count);
	else if (gdata->player.mov_down == 1 && can_i_move_to(gdata, *target_x,
			*target_y + gdata->player.speed))
		prepare_down_target(gdata, target_y, &count);
}

void render_game (void *param) // todo lo que se tenga que checkear a cada vuelta de renderizado
{
	t_game	*gdata;
	int		target_x;
	int		target_y;

	gdata = param;
	gdata->player.speed = 2;
	target_x = gdata->minimap.player_x;
	target_y = gdata->minimap.player_y;
 	if (there_is_a_key_pressed(gdata))
	{
		prepare_movement(gdata, &target_x, &target_y);
		gdata->minimap.player_x = target_x;
		gdata->minimap.player_y = target_y;
	}
}

void render_game (void *param)
{
	t_game	*gdata;

	gdata = param;
 	printf ("hola %d\n", gdata->minimap.width);
}