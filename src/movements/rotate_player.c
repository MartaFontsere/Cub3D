/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:57:05 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 01:08:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void rotate_player(t_player *player, t_vision *vision)
{
    if (player->rotate_right == 1) // Rotar a la derecha (sentido horario)
    {
        printf("angulo de rotacion1 (derecha): |%f|\n", vision->vision_angle);
        vision->vision_angle -= ROTATION_SPEED; // Aumentamos el ángulo (sentido horario)
        if (vision->vision_angle > 2 * M_PI) // Si el ángulo supera 2*PI, lo "reiniciamos"
            vision->vision_angle -= 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (derecha): |%f|\n", vision->vision_angle);
    }
    else if (player->rotate_left == 1) // Rotar a la izquierda (sentido antihorario)
    {
        printf("angulo de rotacion1 (izquierda): |%f|\n", vision->vision_angle);
        vision->vision_angle += ROTATION_SPEED; // Restamos del ángulo (sentido antihorario)
        if (vision->vision_angle < 0) // Si el ángulo es menor que 0, lo "reiniciamos"
            vision->vision_angle += 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (izquierda): |%f|\n", vision->vision_angle);
    }
}
