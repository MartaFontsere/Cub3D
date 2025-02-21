/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/21 14:27:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "cub3D.h"

//calcula el punto del suelo en el minimapa 2D usando la distancia del rayo y el ángulo de visión. Importante para la perspectiva

//ray es el rayo actual
void calculate_floor_point(t_ray ray, t_game *gdata)
{

    // Usar la información del choque con la pared ya calculada en calculate_ray.
    // Determinar el suelo visible entre la posición del jugador y ese punto de choque con la pared.
    // Para cada pixel de la columna de la pantalla (debajo del punto de colisión de la pared), calcular su posición en el mundo y su profundidad correcta.

    int check_x_in_map = ray->cell_collision_x; // Usamos la posición de la celda de colisión del rayo con la pared. Estas celdas nos sirven como punto de partida para buscar el suelo
    int check_y_in_map = ray->cell_collision_y;

    // Cálculo del punto de colisión en el suelo
    int floor_hit = 0; //se utilizará para saber cuándo hemos encontrado el suelo

    // Algoritmo DDA para detectar el punto de colisión con el suelo
    while (floor_hit == 0) 
    {
        prinf ("entro\n");// PEROOO.. si estoy cara la pared, no saldra nunca FALTA PROTEGER
        if (ray->first_dist_x < ray->first_dist_y) 
        { // Rayo colisiona primero en X
            ray->first_dist_x += ray->other_dist_x;
            check_x_in_map += ray->x_sign;
            ray->line_crossing = 0; // Colisión con una línea vertical (suelo)
        } else { // Rayo colisiona primero en Y
            ray->first_dist_y += ray->other_dist_y;
            check_y_in_map += ray->y_sign;
            ray->line_crossing = 1;
        }

        // Verificación de que el rayo está dentro del mapa
        if (check_x_in_map < 0 || check_x_in_map >= gdata->map.cells_width || check_y_in_map < 0 || check_y_in_map >= gdata->map.cells_height) {
            break; // Salir si el rayo sale del mapa
        }

        // Aquí verificamos si encontramos el suelo (por ejemplo, representado como '2')
        if (gdata->map.matrix[check_y_in_map][check_x_in_map] == '0') {
            floor_hit = 1; // Si encontramos el suelo, terminamos
        }
    }

    // Una vez que encontramos el suelo, calculamos el punto de colisión
    if (ray->line_crossing == 0) {
        ray->px_collision_x = check_x_in_map * gdata->minimap.px_in_cell_width; // Colisión en X
        ray->px_collision_y = check_y_in_map * gdata->minimap.px_in_cell_height; // Colisión en Y
    } else {
        ray->px_collision_x = (check_x_in_map + 1) * gdata->minimap.px_in_cell_width;
        ray->px_collision_y = (check_y_in_map + 1) * gdata->minimap.px_in_cell_height;
    }

    // Calcular la distancia perpendicular al suelo (esto se hace similar a la corrección de distorsión)
    ray->perpendicular_distance = ray->diagonal_distance * cos(ray->angle - gdata->vision.vision_angle);
}
