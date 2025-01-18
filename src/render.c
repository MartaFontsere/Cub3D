/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/18 16:33:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//DESPRES AIXO EM SERVEIX PER QUAN PUGUI ROTAR I ES QUEDI EN QUALSEVOL POSICIO????
void	prepare_movement(t_game *gdata, int *target_x, int *target_y)
{
	if (gdata->player.mov_right == 1 && can_i_move_to(gdata, *target_x
			+ gdata->player.speed, *target_y))
		*target_x = (*target_x + gdata->player.speed);
	else if (gdata->player.mov_left == 1 && can_i_move_to(gdata, *target_x
			- gdata->player.speed, *target_y))
		*target_x = (*target_x - gdata->player.speed);
	else if (gdata->player.mov_up == 1 && can_i_move_to(gdata, *target_x,
			*target_y - gdata->player.speed))
		*target_y = (*target_y - gdata->player.speed);
	else if (gdata->player.mov_down == 1 && can_i_move_to(gdata, *target_x,
			*target_y + gdata->player.speed))
		*target_y = (*target_y + gdata->player.speed);
}

void render_game (void *param) // todo lo que se tenga que checkear a cada vuelta de renderizado
{
	t_game	*gdata;
	int		target_x;
	int		target_y;

	gdata = param;
	gdata->player.speed = 2; // cuantos pixeles se mueve cada vez
	target_x = gdata->player.x;
	target_y = gdata->player.y;
 	if (there_is_a_key_pressed(gdata))
	{
		prepare_movement(gdata, &target_x, &target_y);
		gdata->player.x = target_x;
		gdata->player.y = target_y;
	}
}

// void render_game (void *param)
// {
// 	t_game	*gdata;

// 	gdata = param;
//  	printf ("hola %d\n", gdata->minimap.width);
// }