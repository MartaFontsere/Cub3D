/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/08 22:44:00 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sempre acabo sentint que he de lidiar amb situacions de merda de gelos i inseguretats 
//i no faig mes perque no estic segura de sentir... i 

//en cada rayo te quedas con la distancia mas corta 
//si al transformar a coordenadas algna es negativa, la desecho y me quedo con la otra distancia como la corta
// hit x y hit y puntos de choque en pixeles
// una vez tienes las dos
// if angulo es uno de los rectos, se que en 90 y 180 la vertical nunca va a existir y al reves. en esos angulos tienes que calcular la interseccion y quedarte con la cntraria
//  incrementos por cuadrantes (positivo y negativo segun si el rayo va a derecha o izquierda, arriba o abajo. sacas el incremento y fuerzas el signo que te interesa. La tangente para calcular el incremento de x e y en ambas intersecciones. Fuerzas luego segun el cuadrante si el incremento sera positivo en un eje o negativo)

//para 

//hit x, hit y vertical, hit x, hit y horizontal, a que corresponde ese choque 



#include "cub3D.h"

static void calculate_ray(t_game *gdata, t_ray *ray, double ray_angle, double x, double y)
{
   // Inicializar dirección del rayo
    ray->dir_x = -cos(ray_angle);
    ray->dir_y = -sin(ray_angle);
   
    int check_x_in_map = (int)(x / gdata->minimap.cell_width); // Representa la celda en la cuadrícula donde está el rayo(índices de la matriz del mapa). Empieza en la casilla del player
    int check_y_in_map = (int)(y / gdata->minimap.cell_height);// Representa la celda en la cuadrícula donde está el rayo  (índices de la matriz del mapa). Empieza en la casilla del player
    double cell_player_x =  x / gdata->minimap.cell_width; //posición en casillas del player
    double cell_player_y = y / gdata->minimap.cell_height;
    
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
            ray->first_dist_x = (cell_player_x - check_x_in_map) * ray->other_dist_x; //Tenia el problema de que estaba obteniendo esto en pixeles y el other dist en casillas, y por eso daba numeros raros
        } 
        else 
        {
            ray->x_sign = 1; //el rayo va a la derecha
            ray->first_dist_x = ((check_x_in_map + 1) - cell_player_x) * ray->other_dist_x;
        }
    }

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
            ray->first_dist_y = (cell_player_y - check_y_in_map) * ray->other_dist_y;
        } 
        else 
        {
            ray->y_sign = 1; //el rayo va abajo
            ray->first_dist_y = ((check_y_in_map + 1) - cell_player_y) * ray->other_dist_y;
        }
    }
    //printf ("ray dir x: |%f|\n", ray->dir_x);


    
    int wall_hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).


     // Algoritmo DDA
    while (wall_hit == 0) 
    {
        if (ray->first_dist_x < ray->first_dist_y)  // El rayo toca antes una línea vertical → Avanza en x
        {
            ray->first_dist_x += ray->other_dist_x; // Como acabamos de cruzar una línea vertical, nos preparamos para el siguiente cruce. Sumamos other_dist_x porque nos dice cuánto hay que avanzar en X para llegar a la siguiente línea vertical
            check_x_in_map += ray->x_sign; // check_x_in_map es la celda en la cuadrícula donde está el rayo. x_sign vale +1 si el rayo va a la derecha o -1 si va a la izquierda. Esto actualiza check_x_in_map para reflejar que hemos cambiado de celda en la cuadrícula.
            ray->line_crossing = 0; // Indica que hemos chocado contra una linea vertical dde la celda (linea en X)
        } 
        else // El rayo toca antes una línea horizontal → Avanza en y
        {
            ray->first_dist_y += ray->other_dist_y;
            check_y_in_map += ray->y_sign;
            ray->line_crossing = 1;
        }

        // Verificar colisión con paredes
        if (check_x_in_map < 0 || check_x_in_map >= gdata->map.width || check_y_in_map < 0 || check_y_in_map >= gdata->map.height) 
            break; //Si el rayo sale del mapa, se detiene.
        if (gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
        {
            wall_hit = 1; //Si el rayo encuentra una celda con 1 (pared), se detiene (hit = 1).
        }
    }

    // Calcular distancia final y coordenadas de colisión
    if (ray->line_crossing == 0) 
    {
        ray->cell_collision_x = check_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = check_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
       
        if (ray->x_sign > 0) // Rayo venía de la izquierda → borde izquierdo de la celda
        {
            ray->px_collision_x = check_x_in_map * gdata->minimap.cell_width;
        }
        else if (ray->x_sign == -1) // Rayo venía de la derecha → borde derecho de la celda
        {
            ray->px_collision_x = (check_x_in_map + 1) * gdata->minimap.cell_width;
        }
        ray->diagonal_distance = (check_x_in_map - cell_player_x + (1 - ray->x_sign) / 2) / ray->dir_x;
        ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.cell_height) * ray->dir_y;
        
    } 


    else 
    {
        ray->cell_collision_x = check_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
        ray->cell_collision_y = check_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
        if (ray->y_sign > 0) // Rayo venía de arriba → borde superior de la celda
        {
            ray->px_collision_y = check_y_in_map * gdata->minimap.cell_height;
        }
        else if (ray->y_sign == -1) // Rayo venía de abajo → borde inferior de la celda
        {
            ray->px_collision_y = (check_y_in_map + 1) * gdata->minimap.cell_height;
        }
        ray->diagonal_distance = (check_y_in_map - cell_player_y + (1 - ray->y_sign) / 2) / ray->dir_y;
        
       // ray->cell_collision_x = check_x_in_map;
        // La coordenada X se obtiene usando la ecuación de la recta del rayo
        ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.cell_width) * ray->dir_x;

    }
    ray->perpendicular_distance = ray->diagonal_distance * cos(ray_angle - gdata->vision.vision_angle);
    // ray->line_crossing = line_crossing;
}


//fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo



// Calcula TODOS los rayos del FOV y los almacena en t_fov
void calculate_fov(t_game *gdata, double x, double y) //Mandar las coordenadas del player (actuales y anteriores)
{
    double start_angle = gdata->vision.vision_angle + (gdata->vision.FOV.fov_rad / 2);
    double end_angle = gdata->vision.vision_angle - (gdata->vision.FOV.fov_rad / 2);
    double angle_step = (end_angle - start_angle) / gdata->vision.FOV.num_rays; // = FOV/ancho pantalla

   
    int i = 0; //indice de cada rayo
    gdata->vision.FOV.rays[i].current_angle = start_angle;
    while (i < gdata->vision.FOV.num_rays) 
    {
        calculate_ray(gdata, &gdata->vision.FOV.rays[i], gdata->vision.FOV.rays[i].current_angle, x, y); 
        gdata->vision.FOV.rays[i+1].current_angle = gdata->vision.FOV.rays[i].current_angle + angle_step;//current_angle = start_angle + (angle_step * i); // lo mismo que current angle = current angle + angle step
        i++;
    }
}


//CON APUNTES Y PRINTFS

// // Calcula un solo rayo usando DDA (almacena datos en t_ray)
// static void calculate_ray(t_game *gdata, t_ray *ray, double ray_angle, double x, double y, int i)// borrar i 
// {
//     (void)i; //BORRAR
//    // Inicializar dirección del rayo
//     ray->dir_x = cos(ray_angle);
//     ray->dir_y = -sin(ray_angle);
//     printf("Rayo %d - Dir: (%.2f, %.2f) - ray angle: |%.2f|\n", i, ray->dir_x, ray->dir_y, ray_angle * (180 / M_PI));

//     int check_x_in_map = (int)(x / gdata->minimap.cell_width); // Representa la celda en la cuadrícula donde está el rayo(índices de la matriz del mapa). Empieza en la casilla del player
//     printf("   check_x_in_map inicial: (%d)\n", check_x_in_map);
//     printf ("  x: %f\n", x);
//     printf ("  gdata->minimap.cell_width: %f\n", gdata->minimap.cell_width);
//     int check_y_in_map = (int)(y / gdata->minimap.cell_height);// Representa la celda en la cuadrícula donde está el rayo  (índices de la matriz del mapa). Empieza en la casilla del player
//     printf("   check_y_in_map inicial: (%d)\n", check_y_in_map);
//     printf ("  y: %f\n", y);
//     printf ("  gdata->minimap.cell_width: %f\n", gdata->minimap.cell_height);
//     double cell_player_x =  x / gdata->minimap.cell_width; //posición en casillas del player
//     double cell_player_y = y / gdata->minimap.cell_height;
    
//     if (fabs(ray->dir_x) < 1e-6) // Evita divisiones por valores casi 0
//     {
//         ray->other_dist_x = 1e6; // Para evitar división por 0
//         ray->first_dist_x = 1e6;  // Evita valores negativos absurdos
//         ray->x_sign = 0;  // No avanza en X
//     }
//     else
//     {
//         ray->other_dist_x = fabs(1 / ray->dir_x); // (en casillas) Cuánto hay que moverse en X para pasar a la siguiente línea vertical de la celda de la cuadrícula. 
//         // Determinar x_sign y first_dist_x
//         if (ray->dir_x < 0) 
//         {
//             ray->x_sign = -1;//el rayo va a la izquierda
//             ray->first_dist_x = (cell_player_x - check_x_in_map) * ray->other_dist_x; //Tenia el problema de que estaba obteniendo esto en pixeles y el other dist en casillas, y por eso daba numeros raros
//         } 
//         else 
//         {
//             ray->x_sign = 1; //el rayo va a la derecha
//             ray->first_dist_x = ((check_x_in_map + 1) - cell_player_x) * ray->other_dist_x;
//         }
//     }
//     //PIXELES SON INTEGERS, NO PUEDEN SER DECIMALES, ES LA MINIMA UNIDAD.


//     printf ("   --distancia constante en el eje x :|%f|\n", ray->other_dist_x);
    
//     // Evitar divisiones por valores cercanos a 0
//     if (fabs(ray->dir_y) < 1e-6) 
//     {
//         ray->other_dist_y = 1e6;  // Para evitar valores enormes
//         ray->first_dist_y = 1e6;   // Nunca cruzará una pared horizontal
//         ray->y_sign = 0;          // No se mueve en Y
//     } 
//     else 
//     {
//         ray->other_dist_y = fabs(1 / ray->dir_y); //(en casillas) Cuánto hay que moverse en Y para pasar a la siguiente línea horizontal de la celda de la cuadrícula.
//         // Determinar y_sign y first_dist_y
//         if (ray->dir_y < 0) 
//         {
//             ray->y_sign = -1; //el rayo va arriba
//             ray->first_dist_y = (cell_player_y - check_y_in_map) * ray->other_dist_y;
//         } 
//         else 
//         {
//             ray->y_sign = 1; //el rayo va abajo
//             ray->first_dist_y = ((check_y_in_map + 1) - cell_player_y) * ray->other_dist_y;
//         }
//     }
//     printf ("   --distancia constante en el eje y :|%f|\n", ray->other_dist_y);
//     //printf ("ray dir x: |%f|\n", ray->dir_x);


    
//     int wall_hit = 0; // Es una flag que indica si el rayo ha chocado con una pared. El while se ejecutara hasta que hit == 1 (cuando encuentra una pared).


//      // Algoritmo DDA
//     while (wall_hit == 0) 
//     {
//         if (ray->first_dist_x < ray->first_dist_y)  // El rayo toca antes una línea vertical → Avanza en x
//         {
//             printf("       ...first_dist_x: (%f)\n", ray->first_dist_x);
//             printf("       ...first_dist_y: (%f)\n", ray->first_dist_y);
//             printf("                  ... other_dist_x: (%f)\n", ray->other_dist_x);
//             printf("                  ... other_dist_y: (%f)\n", ray->other_dist_y);
//             ray->first_dist_x += ray->other_dist_x; // Como acabamos de cruzar una línea vertical, nos preparamos para el siguiente cruce. Sumamos other_dist_x porque nos dice cuánto hay que avanzar en X para llegar a la siguiente línea vertical
//             check_x_in_map += ray->x_sign; // check_x_in_map es la celda en la cuadrícula donde está el rayo. x_sign vale +1 si el rayo va a la derecha o -1 si va a la izquierda. Esto actualiza check_x_in_map para reflejar que hemos cambiado de celda en la cuadrícula.
//             printf("       ...progreso eje x: (%d)\n", check_x_in_map);
//             ray->line_crossing = 0; // Indica que hemos chocado contra una linea vertical dde la celda (linea en X)
//         } 
//         else // El rayo toca antes una línea horizontal → Avanza en y
//         {
//             printf("          ^*^* first_dist_x: (%f)\n", ray->first_dist_x);
//             printf("          ^*^* first_dist_y: (%f)\n", ray->first_dist_y);
//             printf("                  ^*^* other_dist_x: (%f)\n", ray->other_dist_x);
//             printf("                  ^*^* other_dist_y: (%f)\n", ray->other_dist_y);
//             ray->first_dist_y += ray->other_dist_y;
//             check_y_in_map += ray->y_sign;
//             printf("       ...progreso eje y: (%d)\n", check_y_in_map);
//             ray->line_crossing = 1;
//         }

//         // Verificar colisión con paredes
//         if (check_x_in_map < 0 || check_x_in_map >= gdata->map.width || check_y_in_map < 0 || check_y_in_map >= gdata->map.height) 
//             break; //Si el rayo sale del mapa, se detiene.
//         if (gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
//         {
//             wall_hit = 1; //Si el rayo encuentra una celda con 1 (pared), se detiene (hit = 1).
//             printf("    #check_x_in_map: (%d)\n", check_x_in_map);
//             printf("    #check_y_in_map: (%d)\n", check_y_in_map);

//         }
//     }

//     // Calcular distancia final y coordenadas de colisión
//     if (ray->line_crossing == 0) 
//     {
//         ray->cell_collision_x = check_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
//         ray->cell_collision_y = check_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
       
//         if (ray->x_sign > 0) // Rayo venía de la izquierda → borde izquierdo de la celda
//         {
//             ray->px_collision_x = check_x_in_map * gdata->minimap.cell_width;
//         }
//         else if (ray->x_sign == -1) // Rayo venía de la derecha → borde derecho de la celda
//         {
//             ray->px_collision_x = (check_x_in_map + 1) * gdata->minimap.cell_width;
//         }
//         ray->diagonal_distance = (check_x_in_map - cell_player_x + (1 - ray->x_sign) / 2) / ray->dir_x;
//         printf("       DIAGONAL WALL DISTANCE in pixels: (%f)\n", ray->diagonal_distance * gdata->minimap.cell_height);
//         printf("       DIAGONAL WALL DISTANCE: (%f)\n", ray->diagonal_distance);
//         printf("Calculando distancia: px_collision_x = %f, px_collision_y = %f\n", ray->px_collision_x, ray->px_collision_y);
//         //ray->cell_collision_y = check_y_in_map;
//         // La coordenada Y se obtiene usando la ecuación de la recta del rayo
//         ray->px_collision_y = y + (ray->diagonal_distance * gdata->minimap.cell_height) * ray->dir_y;
        
//     } 


//     else 
//     {
//         ray->cell_collision_x = check_x_in_map;  // Guarda el punto exacto donde choca el rayo (collision_x)
//         ray->cell_collision_y = check_y_in_map; // Guarda el punto exacto donde choca el rayo (collision_y)
//         if (ray->y_sign > 0) // Rayo venía de arriba → borde superior de la celda
//         {
//             ray->px_collision_y = check_y_in_map * gdata->minimap.cell_height;
//         }
//         else if (ray->y_sign == -1) // Rayo venía de abajo → borde inferior de la celda
//         {
//             ray->px_collision_y = (check_y_in_map + 1) * gdata->minimap.cell_height;
//         }
//         ray->diagonal_distance = (check_y_in_map - cell_player_y + (1 - ray->y_sign) / 2) / ray->dir_y;
//         printf("Calculando distancia: px_collision_x = %f, px_collision_y = %f\n", ray->px_collision_x, ray->px_collision_y);
//         printf("       DIAGONAL WALL DISTANCE: (%f)\n", ray->diagonal_distance);
        
//        // ray->cell_collision_x = check_x_in_map;
//         // La coordenada X se obtiene usando la ecuación de la recta del rayo
//         ray->px_collision_x = x + (ray->diagonal_distance * gdata->minimap.cell_width) * ray->dir_x;

//     }
//     ray->perpendicular_distance = ray->diagonal_distance * cos(ray_angle - gdata->vision.vision_angle);
//     // ray->line_crossing = line_crossing;
//     printf("       DIAGONAL WALL DISTANCE in pixels: (%f)\n", ray->diagonal_distance * gdata->minimap.cell_width);
//     printf("       PERPENDICULAR WALL DISTANCE: (%f)\n", ray->perpendicular_distance);
//     printf("Ray %d -> CASILLA Collision at: (%f, %f)\n\n", i, ray->cell_collision_x, ray->cell_collision_y);
//     printf("Ray %d -> PIXELS Collision at: (%f, %f)\n\n", i, ray->px_collision_x, ray->px_collision_y);
// }


// //fabs es una función matemática que calcula el valor absoluto de un número de punto flotante (como double o float). Si el número es positivo, lo devuelve sin cambios. Si el número es negativo, lo convierte a positivo



// // Calcula TODOS los rayos del FOV y los almacena en t_fov
// void calculate_fov(t_game *gdata, double x, double y) //Mandar las coordenadas del player (actuales y anteriores)
// {
//     double start_angle = gdata->vision.vision_angle + (gdata->vision.FOV.fov_rad / 2);
//     double end_angle = gdata->vision.vision_angle - (gdata->vision.FOV.fov_rad / 2);
//     double angle_step = (end_angle - start_angle) / gdata->vision.FOV.num_rays; // = FOV/ancho pantalla

//     printf ("vision.vision_angle: |%f|\n", gdata->vision.vision_angle * (180 / M_PI));
//     printf ("start angle: |%f| end angle: |%f|\n", start_angle * (180 / M_PI), end_angle * (180 / M_PI));
//     printf ("angle_step: |%f|\n", angle_step * (180 / M_PI));

//     int i = 0; //indice de cada rayo
//     printf ("start angle: |%f|\n", start_angle * (180 / M_PI));
//     printf ("num rays |%d|\n\n", gdata->vision.FOV.num_rays);
//     gdata->vision.FOV.rays[i].current_angle = start_angle;
//     while (i < gdata->vision.FOV.num_rays) 
//     {
//         //printf ("current angle: |%f|\n", current_angle);
//         printf ("**********current angle: |%f|\n", gdata->vision.FOV.rays[i].current_angle * (180 / M_PI));
//         calculate_ray(gdata, &gdata->vision.FOV.rays[i], gdata->vision.FOV.rays[i].current_angle, x, y, i); // borrar i
//         gdata->vision.FOV.rays[i+1].current_angle = gdata->vision.FOV.rays[i].current_angle + angle_step;//current_angle = start_angle + (angle_step * i); // lo mismo que current angle = current angle + angle step
//         i++;
//     }
// }
// //si resto la diferencia entre current angles y eso lo mltiplico por los 1500 de ancho de la pantalla, me tendria que dar 60 grados, que es el espacio entre el que se reparten