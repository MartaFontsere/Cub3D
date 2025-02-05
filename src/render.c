/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/05 08:45:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_game (void *param) // todo lo que se tenga que checkear a cada vuelta de renderizado
{
	t_game	*gdata;
	double		target_x;
	double		target_y;

	gdata = param;
	target_x = gdata->player.x;
	target_y = gdata->player.y;
	gdata->vision.last_vision_angle = gdata->vision.vision_angle; // lo actualizo siempre, porque si solo lo actualizo al rotar, cuando solo se mueve no se actualiza el angulo anterior, que debe ser el mismoo que el actual
 	if (there_is_a_key_pressed(gdata))
	{
		printf ("hay una tecla apretada\n");
		printf ("la posicion del player es: |%f||%f|\n",gdata->player.x, gdata->player.y);
		if (gdata->player.rotate_right == 1 || gdata->player.rotate_left == 1)
		{
			printf ("entro\n");
			rotate_player (&gdata->player, &gdata->vision);
		}
		if (gdata->player.mov_right == 1 || gdata->player.mov_left == 1 || gdata->player.mov_up == 1 || gdata->player.mov_down == 1)
			prepare_movement(gdata, gdata->vision, &target_x, &target_y);
		printf ("el target a donde se va a mover es: |%f||%f|\n",target_x, target_y);
		print_player_FOV_in_motion(gdata, gdata->player, target_x, target_y);
		print_player_view_in_motion (gdata, gdata->player, target_x, target_y); // incluir tanto el fov como el point of view
		print_player_move(gdata, gdata->player, target_x, target_y);
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