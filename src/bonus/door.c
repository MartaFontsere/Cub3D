/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray (copy).c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/19 16:15:14 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// double get_distance_to_door(t_game *gdata, int door_x, int door_y) 
// {
//     double player_x = gdata->player.x / gdata->minimap.px_in_cell_width;
//     double player_y = gdata->player.y / gdata->minimap.px_in_cell_height;
    
//     return sqrt(pow(door_x - player_x, 2) + pow(door_y - player_y, 2));
// }

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
                {
                    gdata->map.matrix[door_y][door_x] = 'd'; // ✅ Estado intermedio
                }
            }
            else if (gdata->map.matrix[door_y][door_x] == 'd') // Puerta abriéndose
            {
                distance = get_distance_to_door(gdata, door_x, door_y);
                if (distance <= DOOR_END_OPEN_DISTANCE) // Más cerca = puerta abierta
                {
                    gdata->map.matrix[door_y][door_x] = '0'; // ✅ Ahora sí se abre
                }
            }
            door_x++;
        }
        door_y++;
    }
}

// double get_distance_to_door(t_game *gdata, int door_x, int door_y) 
// {
//     double door_center_x = (door_x + 0.5) * gdata->minimap.px_in_cell_width;
//     double door_center_y = (door_y + 0.5) * gdata->minimap.px_in_cell_height;

//     // Vector dirección normalizado del jugador
//     double dir_x = cos(gdata->vision.vision_angle);
//     double dir_y = -sin(gdata->vision.vision_angle);

//     // Punto de "entrada visual" de la puerta → un poco desplazado desde el centro hacia el lado visible
//     double offset = gdata->minimap.px_in_cell_width * 0.5;
//     double visible_door_x = door_center_x - dir_x * offset;
//     double visible_door_y = door_center_y - dir_y * offset;

//     // Distancia real desde el jugador a ese punto visible
//     double dx = visible_door_x - gdata->player.x;
//     double dy = visible_door_y - gdata->player.y;
//     double distance_px = sqrt(dx * dx + dy * dy);

//     return distance_px / gdata->minimap.px_in_cell_width;
// }
