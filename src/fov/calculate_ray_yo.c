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


void find_wall_ray_distance_and_collision_point(t_ray *ray, t_game *gdata, double x, double y)
{
    // Calcular distancia final y coordenadas de colisión

    //CREO QUE ray->cell_collision_x NO LO USO
    if (ray->line_crossing == 0) 
    {
        ray->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        if (gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'D' || gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'd')
        {
            if (ray->x_sign > 0)
                ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width) + (gdata->minimap.px_in_cell_width / 2);
            else
                ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width) - (gdata->minimap.px_in_cell_width / 2); 
        }
        else 
            ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);

        ray->diagonal_distance = ((ray->px_collision_x / gdata->minimap.px_in_cell_width) - gdata->player.cell_player_x) / ray->dir_x;
        ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  

    } 

    else 
    {
        ray->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        if (gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'D' || gdata->map.matrix[ray->check_ray_y_in_map][ray->check_ray_x_in_map] == 'd')
        {
            if (ray->y_sign > 0)
                ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height) + (gdata->minimap.px_in_cell_height / 2);
            else
                ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height) - (gdata->minimap.px_in_cell_height / 2);
        }
        else
            ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);

        ray->diagonal_distance = ((ray->px_collision_y / gdata->minimap.px_in_cell_height) - gdata->player.cell_player_y) / ray->dir_y;
        ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;


    }
    ray->perpendicular_distance = ray->diagonal_distance * cos(ray->current_angle - gdata->vision.vision_angle);
     

    // ray->line_crossing = line_crossing;
}

int should_block_ray(t_ray *ray, t_game *gdata, int map_x, int map_y)
{
    //Calcular distancia jugador-puerta

    double distance = get_distance_to_door(gdata, map_x, map_y);

    double adjusted_distance = fmax(0.0, distance - DOOR_END_OPEN_DISTANCE);
    double max_open_range = DOOR_START_OPEN_DISTANCE - DOOR_END_OPEN_DISTANCE;
    double open_ratio = 1.0 - fmin(adjusted_distance / max_open_range, 1.0);

    if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
        return 0; // Permitir paso (no bloquear), para evitar segfault

    //Calcular wall_x (posición de colisión dentro de la celda)
    double wall_x;
    if (ray->line_crossing == 0)
    {
        ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);
        ray->diagonal_distance = ((ray->px_collision_x / gdata->minimap.px_in_cell_width) - gdata->player.cell_player_x) / ray->dir_x;
        ray->px_collision_y = gdata->player.y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;
        wall_x = fmod(ray->px_collision_y, gdata->minimap.px_in_cell_height) / gdata->minimap.px_in_cell_height;
    
        // Invertimos solo si mira al ESTE
        if (ray->x_sign > 0)
            wall_x = 1.0 - wall_x;
    }
    else
    {
        ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);
        ray->diagonal_distance = ((ray->px_collision_y / gdata->minimap.px_in_cell_height) - gdata->player.cell_player_y) / ray->dir_y;
        ray->px_collision_x = gdata->player.x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x; 
         wall_x = fmod(ray->px_collision_x, gdata->minimap.px_in_cell_width) / gdata->minimap.px_in_cell_width;
    
        // Invertir solo si mira al NORTE
        if (ray->y_sign < 0)
            wall_x = 1.0 - wall_x;
    }

    //Convertir a coordenada de textura
    int tex_width = gdata->texture.door_img.xpm->texture.width;
    int tex_x = (int)(wall_x * tex_width);


if (tex_x < 0) tex_x = 0;
if (tex_x >= tex_width) tex_x = tex_width - 1;

    //Simular apertura deslizante de derecha a izquierda
    int shift = (int)(open_ratio * tex_width);
    

    int shifted_tex_x;
        shifted_tex_x = tex_x - shift;
    //Si shifted_tex_x >= 0 → todavía hay puerta visible ahí → BLOQUEAMOS el rayo
    //Si shifted_tex_x < 0 → esa parte ya está "abierta" → dejamos pasar el rayo
    return (shifted_tex_x >= 0);
}






int traverse_ray_until_hit(t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map)
{
    int wall_hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).


    int line_crossing_tmp;
    int  check_ray_x_in_map_tmp;
    int  check_ray_y_in_map_tmp;
    double first_dist_x_tmp = 0;
    double first_dist_y_tmp = 0;
    double door_midpoint = 0; 

    ray->hit_door = 0; // Resetear por si quedó de un rayo anterior

     // Algoritmo DDA
    while (wall_hit == 0) 
    {

        if (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == 'D' || (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == 'd'&& should_block_ray(ray, gdata, *check_ray_x_in_map, *check_ray_y_in_map)))
        {

            line_crossing_tmp = ray->line_crossing;
            check_ray_y_in_map_tmp = *check_ray_y_in_map;
            check_ray_x_in_map_tmp = *check_ray_x_in_map;
            first_dist_x_tmp = ray->first_dist_x;
            first_dist_y_tmp = ray->first_dist_y;

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


            if (line_crossing_tmp == 1 && ray->line_crossing == 1)
            {
                ray->first_dist_y = first_dist_y_tmp;
                *check_ray_y_in_map = check_ray_y_in_map_tmp;
            }
            else if (line_crossing_tmp == 0 && ray->line_crossing == 0)
            {
                ray->first_dist_x = first_dist_x_tmp;
                *check_ray_x_in_map = check_ray_x_in_map_tmp;
            }
            else if (line_crossing_tmp == 1)
            {
                
                ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);
                ray->diagonal_distance = ((ray->px_collision_x / gdata->minimap.px_in_cell_width) - gdata->player.cell_player_x) / ray->dir_x;
                ray->px_collision_y = gdata->player.y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  
                if (ray->y_sign > 0)
                {
                    door_midpoint = (*check_ray_y_in_map + 0.5) * gdata->minimap.px_in_cell_height;
                    if (ray->px_collision_y > door_midpoint)
                    {
                        ray->first_dist_x = first_dist_x_tmp;
                        *check_ray_x_in_map = check_ray_x_in_map_tmp;
                        ray->line_crossing = 1;
                    }

                }
                
                else if (ray->y_sign < 0)
                {
                    door_midpoint = (*check_ray_y_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_height;
                    if (ray->px_collision_y < door_midpoint)
                    {
                        ray->first_dist_x = first_dist_x_tmp;
                        *check_ray_x_in_map = check_ray_x_in_map_tmp;
                        ray->line_crossing = 1;
                    }
                }
            }
            else if (line_crossing_tmp == 0)
            {
                
                ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);
                ray->diagonal_distance = ((ray->px_collision_y / gdata->minimap.px_in_cell_height) - gdata->player.cell_player_y) / ray->dir_y;
                ray->px_collision_x = gdata->player.x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;
                if (ray->x_sign > 0)
                {
                    door_midpoint = (*check_ray_x_in_map + 0.5) * gdata->minimap.px_in_cell_width;
                    if (ray->px_collision_x > door_midpoint)
                    {
                        ray->first_dist_y = first_dist_y_tmp;
                        *check_ray_y_in_map = check_ray_y_in_map_tmp;
                        ray->line_crossing = 0;
                    }

                }
                
                else if (ray->x_sign < 0)
                {
                    door_midpoint = (*check_ray_x_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_width;
                    if (ray->px_collision_x < door_midpoint)
                    {
                        ray->first_dist_y = first_dist_y_tmp;
                        *check_ray_y_in_map = check_ray_y_in_map_tmp;
                        ray->line_crossing = 0;
                    }
                }  
            }
            break;
        }


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

    return (1);
}



int calculate_ray(t_game *gdata, t_ray *ray, double x, double y)
{
   //IDEA, CONVERTIRLO EN UNA ESTRUCTURA Y ACCEDER A ELLA EN VEZ DE INICIALIZARLO EN CADA RAYO


   ray->check_ray_x_in_map = (int)(x / gdata->minimap.px_in_cell_width); // Representa la celda en la cuadrícula donde está el rayo(índices de la matriz del mapa). Empieza en la casilla del player
   ray->check_ray_y_in_map = (int)(y / gdata->minimap.px_in_cell_height);// Representa la celda en la cuadrícula donde está el rayo  (índices de la matriz del mapa). Empieza en la casilla del player
    
    init_ray_direction (ray, gdata, ray->check_ray_x_in_map, ray->check_ray_y_in_map);
    if (traverse_ray_until_hit(ray, gdata, &ray->check_ray_x_in_map, &ray->check_ray_y_in_map) == 0)
    {
        //FREE DATA
        return (0);
    }
    find_wall_ray_distance_and_collision_point (ray, gdata, x, y);  
    return (1);
}


//fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo
