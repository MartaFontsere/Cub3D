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
        printf ("* vertical ray->cell_collision_x %d\n", ray->cell_collision_x);
        printf ("* vertical ray->cell_collision_y %d\n", ray->cell_collision_y);
        ray->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width);
         printf ("* vertical ray->px_collision_x %f\n", ray->px_collision_x);
        ray->diagonal_distance = (ray->check_ray_x_in_map - gdata->player.cell_player_x + (1 - ray->x_sign) / 2) / ray->dir_x;
        ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y;  
        printf ("* vertical ray->px_collision_y %f\n\n", ray->px_collision_y);
    } 

    else 
    {
        ray->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        printf ("* horizontal ray->cell_collision_x %d\n", ray->cell_collision_x);
        printf ("* horizontal ray->cell_collision_y %d\n", ray->cell_collision_y);
        ray->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height);
         printf ("* ray->px_collision_y %f\n", ray->px_collision_y);
        ray->diagonal_distance = (ray->check_ray_y_in_map - gdata->player.cell_player_y + (1 - ray->y_sign) / 2) / ray->dir_y;
        ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x;
        printf ("* ray->px_collision_x %f\n\n", ray->px_collision_x);

    }
    ray->perpendicular_distance = ray->diagonal_distance * cos(ray->current_angle - gdata->vision.vision_angle);
    // ray->line_crossing = line_crossing;
}


void add_new_node (t_ray *ray, t_door *new_door)
{
    t_door *temp;

    if (!ray->door_list) // Si es la primera puerta, se convierte en la cabeza de la lista
        ray->door_list = new_door;
    else
        
    {
        temp = ray->door_list;
        while (temp->next) // Ir al último nodo
            temp = temp->next;
        temp->next = new_door; // Conectar el nuevo nodo
    }
}

int create_new_node (t_door **new_door)
{
    *new_door = malloc(sizeof(t_door));
    if (!*new_door)
    {
        //MENSAJE DE ERROR!!!!!!!
        printf ("ERROR\n");
        return (0);
    }
    (*new_door)->next = NULL; // Inicialmente apunta a NULL
    return (1);
}

int find_door_ray_distance_and_collision_point(t_ray *ray, t_game *gdata, double x, double y)
{
    t_door *new_door;

    new_door = NULL;
    if (create_new_node (&new_door) == 0)
        return (0);

    // Calcular distancia final y coordenadas de colisión
    if (ray->line_crossing == 0) // Puerta en pared vertical 
    {
        
        new_door->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        new_door->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        printf ("  vertical new_door->cell_collision_x %d\n", new_door->cell_collision_x);
        printf ("  vertical new_door->cell_collision_y %d\n", new_door->cell_collision_y);
        new_door->px_collision_x = compute_collision_coordinate(ray->check_ray_x_in_map, ray->x_sign, gdata->minimap.px_in_cell_width) + (gdata->minimap.px_in_cell_width / 2);
         printf ("  vertical new_door->px_collision_x %f\n", new_door->px_collision_x);
        double door_offset = (gdata->minimap.px_in_cell_height / 2) * ray->y_sign; 
        new_door->diagonal_distance = (ray->check_ray_x_in_map - gdata->player.cell_player_x + (1 - ray->x_sign) / 2) / ray->dir_x + (door_offset / gdata->minimap.px_in_cell_height) * ray->dir_y;
        new_door->px_collision_y = y + (new_door->diagonal_distance * gdata->minimap.px_in_cell_height) * ray->dir_y + door_offset; // Suma la mitad de la celda en la dirección del rayo
        printf ("  vertical new_door->px_collision_y %f\n", new_door->px_collision_y);


        new_door->hit_x = (new_door->px_collision_y - (new_door->cell_collision_y * gdata->minimap.px_in_cell_height)) / gdata->minimap.px_in_cell_height;
    } 

    else // Puerta en pared horizontal 
    {
        new_door->cell_collision_x = ray->check_ray_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        new_door->cell_collision_y = ray->check_ray_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        printf ("  horizontal new_door->cell_collision_x %d\n", new_door->cell_collision_x);
        printf ("  horizontal new_door->cell_collision_y %d\n", new_door->cell_collision_y);
        new_door->px_collision_y = compute_collision_coordinate(ray->check_ray_y_in_map, ray->y_sign, gdata->minimap.px_in_cell_height) + (gdata->minimap.px_in_cell_height / 2);
       printf ("  horizontal new_door->px_collision_y %f\n", new_door->px_collision_y);
        double door_offset = (gdata->minimap.px_in_cell_width / 2) * ray->x_sign;
        new_door->diagonal_distance = (ray->check_ray_y_in_map - gdata->player.cell_player_y + (1 - ray->y_sign) / 2) / ray->dir_y + (door_offset / gdata->minimap.px_in_cell_width) * ray->dir_x;
        new_door->px_collision_x = x + (new_door->diagonal_distance * gdata->minimap.px_in_cell_width) * ray->dir_x + door_offset; // Suma la mitad de la celda en la dirección del rayo
        printf ("  horizontal new_door->px_collision_x %f\n\n", new_door->px_collision_x);
        // 📌 Calcular hit_x basado en la posición de impacto dentro de la celda
        new_door->hit_x = (new_door->px_collision_x - (new_door->cell_collision_x * gdata->minimap.px_in_cell_width)) / gdata->minimap.px_in_cell_width;
    // printf ("new_door->px_collision_y %f\n", new_door->px_collision_y);
    // printf ("new_door->px_collision_x %f\n\n", new_door->px_collision_x);
    // printf ("new_door->diagonal_distance %f\n\n", new_door->diagonal_distance);
    }
    
    ray->perpendicular_distance = new_door->diagonal_distance * cos(ray->current_angle - gdata->vision.vision_angle);
//Desplazo donde se pinta la puerta, pero el rayo seguira avanzando desde donde estaba sin modificar hasta la pared, por lo que ese rayo tendra tambien la info de la pared de al lado

    add_new_node(ray, new_door);
    return (1);
}


int traverse_ray_until_hit(t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map, double x, double y)
{
    int wall_hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).

    ray->hit_door = 0;
    ray->door_list = NULL; // Asegurar que la lista comienza vacía
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
        if (gdata->map.matrix[*check_ray_y_in_map][*check_ray_x_in_map] == 'D')
        {
            ray->hit_door ++; 
            if (find_door_ray_distance_and_collision_point (ray, gdata, x, y) == 0)
                return (0);
        }
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
    if (traverse_ray_until_hit(ray, gdata, &ray->check_ray_x_in_map, &ray->check_ray_y_in_map, x, y) == 0)
    {
        //FREE DATA
        return (0);
    }
    find_wall_ray_distance_and_collision_point (ray, gdata, x, y);  
    return (1);
}


//fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo
