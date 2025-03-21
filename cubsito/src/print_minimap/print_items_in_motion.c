/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:08:50 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 21:00:02 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


//PRINT MOVEMENT MINIMAPA

// void print_player_FOV_in_motion(t_game *gdata, t_player player, double target_x, double target_y)
// {
// 	printf ("hola%f\n", player.x);

// 	//calculate_fov(gdata, player.x, player.y);
// 	//print_FOV (gdata, gdata->vision, player.x, player.y, gdata->vision.last_vision_angle, DARK_GREY);
// 	print_minimap (gdata);
// 	calculate_fov(gdata, target_x, target_y);
// 	print_FOV (gdata, gdata->vision, target_x, target_y, gdata->vision.vision_angle,  SOFT_YELLOW);
// }


// void print_player_view_in_motion (t_game *gdata, t_player player, double target_x, double target_y)
// {
// 	//print_vision_angle (gdata, player.x, player.y, gdata->vision.last_vision_angle, SOFT_YELLOW);
// 	printf ("player%f", player.x); // BORRAR
// 	print_vision_angle (gdata, target_x, target_y, gdata->vision.vision_angle, YELLOW1);
// }


// Si dentro de la funcion print_player_FOV_in_motion tengo que se imprima primero en gris en la posicion que esta y que luego se repinte en amarillo en la posicion a la que se desplaza, no es lo mismo que lo de clear_screen? Es necesario? Ponme  toda el orden logico, el flujo de funciones, para saber en que orden se llaman y donde va cada parte del codigo



// void print_player_move(t_game *gdata, t_player player, double target_x, double target_y)
// {

// 	//print_player (gdata, player, player.x, player.y, DARK_GREY);
// 	print_player (gdata, player, target_x, target_y, RED1);
// }

