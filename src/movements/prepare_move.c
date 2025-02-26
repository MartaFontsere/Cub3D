/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 00:53:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"




void rotate_player(t_player *player, t_vision *vision)
{
    if (player->rotate_right == 1) // Rotar a la derecha (sentido horario)
    {
        printf("angulo de rotacion1 (derecha): |%f|\n", vision->vision_angle);
        vision->vision_angle += ROTATION_SPEED; // Aumentamos el ángulo (sentido horario)
        if (vision->vision_angle > 2 * M_PI) // Si el ángulo supera 2*PI, lo "reiniciamos"
            vision->vision_angle -= 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (derecha): |%f|\n", vision->vision_angle);
    }
    else if (player->rotate_left == 1) // Rotar a la izquierda (sentido antihorario)
    {
        printf("angulo de rotacion1 (izquierda): |%f|\n", vision->vision_angle);
        vision->vision_angle -= ROTATION_SPEED; // Restamos del ángulo (sentido antihorario)
        if (vision->vision_angle < 0) // Si el ángulo es menor que 0, lo "reiniciamos"
            vision->vision_angle += 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (izquierda): |%f|\n", vision->vision_angle);
    }
}


void prepare_next_position(t_game *gdata, t_vision vision, double	*move_x, double	*move_y)
{
	if (gdata->player.mov_up == 1) // Ir hacia adelante
	{
		*move_x -= MOVE_SPEED * cos(vision.vision_angle);
		*move_y -= MOVE_SPEED * sin(vision.vision_angle);
	}
	if (gdata->player.mov_down == 1) // Ir hacia atrás
	{
		*move_x += MOVE_SPEED * cos(vision.vision_angle);
		*move_y += MOVE_SPEED * sin(vision.vision_angle); 
	}
	 if (gdata->player.mov_right == 1) // Moverse a la derecha
    {
        *move_x += MOVE_SPEED * cos(vision.vision_angle - M_PI_2);
        *move_y += MOVE_SPEED * sin(vision.vision_angle - M_PI_2);
    }
    if (gdata->player.mov_left == 1) // Moverse a la izquierda
    {
        *move_x += MOVE_SPEED * cos(vision.vision_angle + M_PI_2);
        *move_y += MOVE_SPEED * sin(vision.vision_angle + M_PI_2);
    }
}

void	move_player (t_game *gdata, t_vision vision, double *target_x, double *target_y)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	
	prepare_next_position (gdata, vision, &move_x, &move_y);

	// Solo actualizamos si no hay colisión
	if (check_collision(gdata, *target_x + move_x, *target_y + move_y))
	{
		*target_x += move_x;
		*target_y += move_y;
	}
	// Verificar los movimientos
    printf("movimiento | X: %f, Y: %f\n", move_x, move_y);
}
