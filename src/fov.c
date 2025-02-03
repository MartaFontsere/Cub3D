/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/30 10:24:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sempre acabo sentint que he de lidiar amb situacions de merda de gelos i inseguretats 
//i no faig mes perque no estic segura de sentir... i 

#include "cub3D.h"

// Calcula un solo rayo usando DDA (almacena datos en t_ray)
static void calculate_ray(t_game *gdata, t_ray *ray, double ray_angle, double x, double y) 
{
   // Inicializar dirección del rayo
    ray->dir_x = -cos(ray_angle);
    ray->dir_y = -sin(ray_angle);

    // Algoritmo DDA
    double first_dist_x; // distancia desde la posición actual del player hasta la primera línea vertical de la celda de la cuadrícula
    double first_dist_y; // // distancia desde la posición actual del player hasta la primera línea horizontal de la celda de la cuadrícula
   	//Resumen: Distancia desde el inicio del rayo hasta la primera línea de la cuadrícula en cada dirección (X o Y).
    double other_dist_x = fabs(1 / ray->dir_x); // Cuánto hay que moverse en X para pasar a la siguiente línea vertical de la celda de la cuadrícula. 
    double other_dist_y = fabs(1 / ray->dir_y); //Cuánto hay que moverse en Y para pasar a la siguiente línea horizontal de la celda de la cuadrícula.
    // Resumen: Distancia constante entre cada cruce de líneas en la cuadrícula, después del primer encuentro
    int check_x_in_map = (int)(x / gdata->minimap.cell_width); // Representa la celda en la cuadrícula donde está el rayo (índices de la matriz del mapa)
    int check_y_in_map = (int)(y / gdata->minimap.cell_height);// Representa la celda en la cuadrícula donde está el rayo (índices de la matriz del mapa)
    int x_sign, y_sign; // Indican si el rayo se mueve hacia adelante o atrás en cada eje.
    //Ej: Si el rayo va a la izquierda (dir_x < 0), x_sign = -1. Si el rayo va a la derecha (dir_x > 0), x_sign = 1.
    int hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).
    int wall_position; // nos dice qué cara de una celda fue atravesada por el rayo en su último avance. Indica si el rayo choca contra una pared vertical (side = 0, osea se movió en X) o una horizontal (side = 1, osea se movió en Y).

    // Determinar x_sign y first_dist_x
    if (ray->dir_x < 0) {
        x_sign = -1;
        first_dist_x = (x - check_x_in_map) * other_dist_x;
    } 
    else 
    {
        x_sign = 1;
        first_dist_x = (check_x_in_map + 1.0 - x) * other_dist_x;
    }

    // Determinar y_sign y first_dist_y
    if (ray->dir_y < 0) {
        y_sign = -1;
        first_dist_y = (y - check_y_in_map) * other_dist_y;
    } 
    else 
    {
        y_sign = 1;
        first_dist_y = (check_y_in_map + 1.0 - y) * other_dist_y;
    }

     // Algoritmo DDA (sin operadores ternarios)
    while (hit == 0) 
    {
        if (first_dist_x < first_dist_y) 
        {
            first_dist_x += other_dist_x;
            check_x_in_map += step_x;
            wall_position = 0;
        } 
        else 
        {
            first_dist_y += other_dist_y;
            check_y_in_map += y_sign;
            wall_position = 1;
        }

        // Verificar colisión con paredes
        if (check_x_in_map < 0 || check_x_in_map >= gdata->map.width || map_y < 0 || map_y >= gdata->map.height) 
            break;
        if (gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
            hit = 1;
    }

    // Calcular distancia y coordenadas de colisión (sin `?`)
    if (wall_position == 0) 
    {
        ray->distance = (check_x_in_map - gdata->player.x + (1 - x_sign) / 2) / ray->dir_x;
        ray->collision_x = check_x_in_map;
        if (x_sign == -1) {
            ray->collision_x += 1;
        }
    } 
    else 
    {
        ray->distance = (check_y_in_map - gdata->player.y + (1 - y_sign) / 2) / ray->dir_y;
        ray->collision_y = check_y_in_map;
        if (y_sign == -1) {
            ray->collision_y += 1;
        }
    }
    ray->wall_position = wall_position;
}


//fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo



// Calcula TODOS los rayos del FOV y los almacena en t_fov
void calculate_fov(t_game *gdata, double x, double y) //Mandar las coordenadas del player (actuales y anteriores)
{
    double start_angle = gdata->vision.vision_angle - (gdata->fov.fov_rad);
    double end_angle = gdata->vision.vision_angle + (gdata->vision.fov.fov_rad);
    double angle_step = (end_angle - start_angle) / gdata->vision.fov.num_rays;

    int i = 0; //indice de cada rayo
    while (i < gdata->fov.num_rays) 
    {
        double current_angle = start_angle + (angle_step * i); // lo mismo que current angle = current angle + angle step
        calculate_ray(gdata, &gdata->fov.rays[i], current_angle, x, y);
        i++;
    }
}