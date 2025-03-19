/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calculate_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:02 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/19 02:05:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Calcula la posición de colisión en un eje genérico (X o Y) ---
double compute_collision_coordinate(int check_ray_coord, int ray_sign, double px_in_cell_size)
{
    if (ray_sign > 0) // Rayo venía desde el lado negativo (izquierda o arriba) → colisión en el inicio de la celda
        return check_ray_coord * px_in_cell_size;
    else // Rayo venía desde el lado positivo (derecha o abajo)→ colisión en el final de la celda
        return (check_ray_coord + 1) * px_in_cell_size;
        
}


//implementacion el algoritmo DDA (Digital Differential Analyzer) para calcular la trayectoria de un rayo en un mapa de celdas. Se usa en el motor gráfico para detectar colisiones con paredes y calcular distancias para la proyección 3D

void controll_y_limit_case (t_ray *ray, int check_ray_y_in_map, double cell_player_y)
{
    // Evitar divisiones por valores cercanos a 0
    if (fabs(ray->dir_y) < 1e-6) 
    {
        ray->other_dist_y = 1e6;  // Para evitar valores enormes
        ray->first_dist_y = 1e6;   // Nunca cruzará una pared horizontal
        ray->y_sign = 0;          // No se mueve en Y
    } 
    else 
    {
        ray->other_dist_y = fabs(1 / ray->dir_y); //(en casillas) Cuánto hay que moverse en Y para pasar a la siguiente línea horizontal de la celda de la cuadrícula.
        // Determinar y_sign y first_dist_y
        if (ray->dir_y < 0) 
        {
            ray->y_sign = -1; //el rayo va arriba
            ray->first_dist_y = (cell_player_y - check_ray_y_in_map) * ray->other_dist_y;
        } 
        else 
        {
            ray->y_sign = 1; //el rayo va abajo
            ray->first_dist_y = ((check_ray_y_in_map + 1) - cell_player_y) * ray->other_dist_y;
        }
    }
    //printf ("ray dir x: |%f|\n", ray->dir_x);
}

void controll_x_limit_case (t_ray *ray, int check_ray_x_in_map, double cell_player_x)
{
    if (fabs(ray->dir_x) < 1e-6) // Evita divisiones por valores casi 0
    {
        ray->other_dist_x = 1e6; // Para evitar división por 0
        ray->first_dist_x = 1e6;  // Evita valores negativos absurdos
        ray->x_sign = 0;  // No avanza en X
    }
    else
    {
        ray->other_dist_x = fabs(1 / ray->dir_x); // (en casillas) Cuánto hay que moverse en X para pasar a la siguiente línea vertical de la celda de la cuadrícula. 
        // Determinar x_sign y first_dist_x
        if (ray->dir_x < 0) 
        {
            ray->x_sign = -1;//el rayo va a la izquierda
            ray->first_dist_x = (cell_player_x - check_ray_x_in_map) * ray->other_dist_x; //Tenia el problema de que estaba obteniendo esto en pixeles y el other dist en casillas, y por eso daba numeros raros
        } 
        else 
        {
            ray->x_sign = 1; //el rayo va a la derecha
            ray->first_dist_x = ((check_ray_x_in_map + 1) - cell_player_x) * ray->other_dist_x;
        }
    }
}