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

double get_distance_to_door(t_game *gdata, int door_x, int door_y) 
{
    double player_x = gdata->player.x / gdata->minimap.px_in_cell_width;
    double player_y = gdata->player.y / gdata->minimap.px_in_cell_height;
    
    return sqrt(pow(door_x - player_x, 2) + pow(door_y - player_y, 2));
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
                if (distance < DOOR_DISTANCE)
                {
                    gdata->map.matrix[door_y][door_x] = 'd'; // ✅ Estado intermedio
                }
            }
            else if (gdata->map.matrix[door_y][door_x] == 'd') // Puerta abriéndose
            {
                distance = get_distance_to_door(gdata, door_x, door_y);
                if (distance < DOOR_DISTANCE / 2) // Más cerca = puerta abierta
                {
                    gdata->map.matrix[door_y][door_x] = '0'; // ✅ Ahora sí se abre
                }
            }
            door_x++;
        }
        door_y++;
    }
}