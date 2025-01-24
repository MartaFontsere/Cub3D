/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/24 04:47:10 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void print_player_view (t_game *gdata, t_player player, double target_x, double target_y)
{
	print_vision_angle (gdata, player, player.x, player.y, DARK_GREY);
	print_vision_angle (gdata, player, target_x, target_y, YELLOW1);
	//falta imprimir el fov
}

void	print_player_move(t_game *gdata, t_player player, double target_x, double target_y)
{

	print_player (gdata, player, player.x, player.y, DARK_GREY);
	print_player (gdata, player, target_x, target_y, RED1);
}

void rotate_player(t_player *player) // rotate the player // importante que sea puntero para que se actualice el valor
{
	if (player->rotate_right == 1)
	{
		printf ("angulo de rotacion1: |%f|\n", player->ray.vision_angle);
		player->ray.vision_angle += ROTATION_SPEED; // rotate right
		printf ("angulo de rotacion2: |%f|\n", player->ray.vision_angle);
		if (player->ray.vision_angle > 2 * M_PI) // Si el ángulo supera este valor, significa que el jugador ha completado una rotación completa. Para evitar que el valor siga aumentando sin control, lo "reinicias" restándole 2 * π, manteniendo el ángulo en el rango válido de 0 a 2 * π.
			player->ray.vision_angle -= 2 * M_PI; // Este reset asegura que el ángulo de orientación del jugador siempre esté contenido dentro de un círculo completo y no crezca indefinidamente
	}
	else if(player->rotate_left == 1)
	{
		player->ray.vision_angle -= ROTATION_SPEED; // rotate left
		if (player->ray.vision_angle < 0)
			player->ray.vision_angle += 2 * M_PI;
	}
	printf ("angulo de rotacion: |%f|\n", player->ray.vision_angle);
}

void	prepare_movement(t_game *gdata, double *target_x, double *target_y)
{
	printf ("player speed es = |%d|\n", MOVE_SPEED);
	printf ("move up esta en %d\n", gdata->player.mov_up);
	if (gdata->player.mov_right == 1 && can_i_move_to(gdata, *target_x * cos(gdata->player.ray.vision_angle)
			+ MOVE_SPEED, *target_y * sin(gdata->player.ray.vision_angle)))
	{
		*target_x = (*target_x * cos(gdata->player.ray.vision_angle) + MOVE_SPEED);
		printf ("target = |%f|\n", *target_x);
	}
	else if (gdata->player.mov_left == 1 && can_i_move_to(gdata, *target_x * cos(gdata->player.ray.vision_angle)
			- MOVE_SPEED, *target_y * sin(gdata->player.ray.vision_angle)))
	{
		*target_x = (*target_x * cos(gdata->player.ray.vision_angle) - MOVE_SPEED);
		printf ("target = |%f|\n", *target_x);
	}
	else if (gdata->player.mov_up == 1 && can_i_move_to(gdata, *target_x * cos(gdata->player.ray.vision_angle),
			*target_y * sin(gdata->player.ray.vision_angle) - MOVE_SPEED))
	{
		*target_y = (*target_y * sin(gdata->player.ray.vision_angle) - MOVE_SPEED);
		printf ("target = |%f|\n", *target_y);
	}
	else if (gdata->player.mov_down == 1 && can_i_move_to(gdata, *target_x * cos(gdata->player.ray.vision_angle),
			*target_y * sin(gdata->player.ray.vision_angle) + MOVE_SPEED))
	{
		*target_y = (*target_y * sin(gdata->player.ray.vision_angle) + MOVE_SPEED);
		printf ("target = |%f|\n", *target_y);
	}
}


// void	move_event(t_cub *cub, float new_x, float new_y)
// {
// 	if (mlx_is_key_down(cub->mlx, WKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle);
// 		new_y += MOVE_SPEED * sin(cub->player.angle);
// 	}
// 	if (mlx_is_key_down(cub->mlx, SKEY))
// 	{
// 		new_x -= MOVE_SPEED * cos(cub->player.angle);
// 		new_y -= MOVE_SPEED * sin(cub->player.angle);
// 	}
// 	if (mlx_is_key_down(cub->mlx, AKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle - M_PI_2);
// 		new_y += MOVE_SPEED * sin(cub->player.angle - M_PI_2);
// 	}
// 	if (mlx_is_key_down(cub->mlx, DKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle + M_PI_2);
// 		new_y += MOVE_SPEED * sin(cub->player.angle + M_PI_2);
// 	}
