/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 01:09:20 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_ray_direction (t_ray *ray, t_game *gdata, int check_ray_x_in_map,  int check_ray_y_in_map)
{
    //IDEA, PASARME GDATA Y VOLVER A INICIALIZAR LAS VARIABLES AQUI EN LOCAL
    // Inicializar dirección del rayo
    ray->dir_x = cos(ray->current_angle);
    ray->dir_y = -sin(ray->current_angle);
    //  printf ("ray->dir_x %f\n", ray->dir_x * (180 / M_PI));
    // printf ("ray->dir_y %f\n", ray->dir_y * (180 / M_PI));

    controll_x_limit_case (ray, check_ray_x_in_map, gdata->player.cell_player_x);
    controll_y_limit_case (ray, check_ray_y_in_map, gdata->player.cell_player_y);
    
}

void traverse_ray_until_hit(t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map)
{
    int wall_hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).

     // Algoritmo DDA
    while (wall_hit == 0) 
    {
        if (ray->first_dist_x < ray->first_dist_y)  // El rayo toca antes una línea vertical → Avanza en x
        {
            ray->first_dist_x += ray->other_dist_x; // Como acabamos de cruzar una línea vertical, nos preparamos para el siguiente cruce. Sumamos other_dist_x porque nos dice cuánto hay que avanzar en X para llegar a la siguiente línea vertical
            *check_ray_x_in_map += ray->x_sign; // check_ray_x_in_map es la celda en la cuadrícula donde está el rayo. x_sign vale +1 si el rayo va a la derecha o -1 si va a la izquierda. Esto actualiza check_ray_x_in_map para reflejar que hemos cambiado de celda en la cuadrícula.
            ray->line_crossing = 0; // Indica que hemos chocado contra una linea vertical dde la celda (linea en X)
        } 
        else // El rayo toca antes una línea horizontal → Avanza en y
        {
            ray->first_dist_y += ray->other_dist_y;
            *check_ray_y_in_map += ray->y_sign;
            ray->line_crossing = 1;
        }

        // Verificar colisión con paredes
        if (*check_ray_x_in_map < 0 || *check_ray_x_in_map >= gdata->map.c_width || *check_ray_y_in_map < 0 || *check_ray_y_in_map >= gdata->map.c_height) 
            break; //Si el rayo sale del mapa, se detiene.
        if (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == '1')
        {
            wall_hit = 1; //Si el rayo encuentra una celda con 1 (pared), se detiene (hit = 1).
        }
    }
}

void find_ray_distance_and_collision_point(t_ray *ray, t_game *gdata, double x, double y)
{
    // Calcular distancia final y coordenadas de colisión
    if (ray->line_crossing == 0) 
    {
        ray->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);
        ray->diagonal_distance = (ray->check_ray_x_in_map - gdata->player.cell_player_x + (1 - ray->x_sign) / 2) / ray->dir_x;
        ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  
    } 

    else 
    {
        ray->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);
        ray->diagonal_distance = (ray->check_ray_y_in_map - gdata->player.cell_player_y + (1 - ray->y_sign) / 2) / ray->dir_y;
        ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;

    }
    ray->perpendicular_distance = ray->diagonal_distance * cos(ray->current_angle - gdata->vision.vision_angle);
    // ray->line_crossing = line_crossing;
}

void calculate_ray(t_game *gdata, t_ray *ray, double x, double y)
{
   //IDEA, CONVERTIRLO EN UNA ESTRUCTURA Y ACCEDER A ELLA EN VEZ DE INICIALIZARLO EN CADA RAYO


   ray->check_ray_x_in_map = (int)(x / gdata->minimap.px_in_cell_width); // Representa la celda en la cuadrícula donde está el rayo(índices de la matriz del mapa). Empieza en la casilla del player
   ray->check_ray_y_in_map = (int)(y / gdata->minimap.px_in_cell_height);// Representa la celda en la cuadrícula donde está el rayo  (índices de la matriz del mapa). Empieza en la casilla del player
    
    init_ray_direction (ray, gdata, ray->check_ray_x_in_map, ray->check_ray_y_in_map);
    traverse_ray_until_hit(ray, gdata, &ray->check_ray_x_in_map, &ray->check_ray_y_in_map);
    find_ray_distance_and_collision_point (ray, gdata, x, y);  
}


//fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo
