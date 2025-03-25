/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/25 19:11:05 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double get_distance_to_door(t_game *gdata, int door_x, int door_y) 
{
    // Centro de la puerta en píxeles
    double door_center_x = (door_x + 0.5) * gdata->minimap.px_in_cell_width;
    double door_center_y = (door_y + 0.5) * gdata->minimap.px_in_cell_height;

    // Posición del jugador ya está en píxeles
    double dx = door_center_x - gdata->player.x;
    double dy = door_center_y - gdata->player.y;

    double distance_px = sqrt(dx * dx + dy * dy);

    // Convertimos a casillas
    return distance_px / gdata->minimap.px_in_cell_width;
}

void update_doors(t_game *gdata)
{
    int door_x = 0;
    int door_y = 0;
    double distance;

    while (door_y < gdata->map.c_height) // Recorre las filas
    {
        door_x = 0;
        while (door_x < gdata->map.c_width) // Recorre las columnas
        {
            if (gdata->map.matrix[door_y][door_x] == 'D') // Puerta cerrada
            {
                distance = get_distance_to_door(gdata, door_x, door_y);
                if (distance < DOOR_START_OPEN_DISTANCE)
                    gdata->map.matrix[door_y][door_x] = 'd'; // ✅ Estado intermedio
            }
            else if (gdata->map.matrix[door_y][door_x] == 'd') // Puerta abriéndose
            {
                distance = get_distance_to_door(gdata, door_x, door_y);
                if (distance <= DOOR_END_OPEN_DISTANCE) // Más cerca = puerta abierta
                    gdata->map.matrix[door_y][door_x] = '0'; // ✅ Ahora sí se abre
            }
            door_x++;
        }
        door_y++;
    }
}
