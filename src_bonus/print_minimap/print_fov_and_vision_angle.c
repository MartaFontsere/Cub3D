/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fov_and_vision_angle.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 05:05:58 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int can_draw_pixel(t_game *gdata, int px, int py, int offset_x, int offset_y)
{
    int pixel_map_x = (int)((gdata->player.x + offset_x) / gdata->minimap.px_in_cell_width);
    int pixel_map_y = (int)((gdata->player.y + offset_y) / gdata->minimap.px_in_cell_height);

    if (px < 0 || px >= gdata->minimap.px_width || py < 0 || py >= gdata->minimap.px_height)
        return 0;

    if (pixel_map_x < 0 || pixel_map_x >= gdata->map.c_width ||
        pixel_map_y < 0 || pixel_map_y >= gdata->map.c_height)
        return 0;

    char cell = gdata->map.matrix[pixel_map_y][pixel_map_x];
    if (cell == '1' || cell == 'D' || cell == 'd')
        return 0;

    return 1;
}

void draw_thick_ray_segment(t_game *gdata, double x, double y, double angle, int color)
{
    double minimap_x = gdata->minimap.center_x + (x - gdata->player.x);
    double minimap_y = gdata->minimap.center_y + (y - gdata->player.y);
    double j = -2; // thickness = 4 → grosor/2 = 2

    while (j <= 2)
    {
        int offset_x = (int)(j * cos(angle + M_PI_2));
        int offset_y = -(int)(j * sin(angle + M_PI_2));

        int pixel_x = (int)(minimap_x + offset_x);
        int pixel_y = (int)(minimap_y + offset_y);

        if (can_draw_pixel(gdata, pixel_x, pixel_y, offset_x, offset_y))
            mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, color);

        j += 0.1;
    }
}

int check_collision_in_y(t_game *gdata, double current_x, double next_y)
{
    int map_x = (int)(current_x / gdata->minimap.px_in_cell_width);
    int map_y = (int)(next_y / gdata->minimap.px_in_cell_height);

    if (map_y < 0 || map_y >= gdata->map.c_height)
        return 1;

    if (gdata->map.matrix[map_y][map_x] == '1' || gdata->map.matrix[map_y][map_x] == 'D' || gdata->map.matrix[map_y][map_x] == 'd')
        return 1;

    return 0;
}

int check_collision_in_x(t_game *gdata, double next_x, double current_y)
{
    int map_x = (int)(next_x / gdata->minimap.px_in_cell_width);
    int map_y = (int)(current_y / gdata->minimap.px_in_cell_height);

    if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
        return 1;

    if (gdata->map.matrix[map_y][map_x] == '1' || gdata->map.matrix[map_y][map_x] == 'D' || gdata->map.matrix[map_y][map_x] == 'd')
        return 1;

    return 0;
}

void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color)
{
    double current_x = x;
    double current_y = y;
    double dir_x = cos(vision_angle);
    double dir_y = -sin(vision_angle);

    while (1)
    {
        if (check_collision_in_x(gdata, current_x + dir_x, current_y))
            break;
        current_x += dir_x;

        if (check_collision_in_y(gdata, current_x, current_y + dir_y))
            break;
        current_y += dir_y;

        draw_thick_ray_segment(gdata, current_x, current_y, vision_angle, color);
    }
}



// void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color)
// {
//     double init_x = x;
//     double init_y = y;
//     double ray_dir_x = cos(vision_angle);
//     double ray_dir_y = -sin(vision_angle); 
//     int thickness = 4;  // Grosor del rayo

   
//     while (1)
//     {
//         // **Avanzamos en X**
//         double next_x = init_x + ray_dir_x;
//         int map_x = (int)(next_x / gdata->minimap.px_in_cell_width);
//         int map_y = (int)(init_y / gdata->minimap.px_in_cell_height);

//         // **Verificar colisión en X**
//         if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
//             break; // Fuera del mapa

//         if (gdata->map.matrix[map_y][map_x] == '1')
//             break; // Colisión en X

//         init_x = next_x; // Actualizamos la posición en X

//         // **Avanzamos en Y**
//         double next_y = init_y + ray_dir_y;
//         map_x = (int)(init_x / gdata->minimap.px_in_cell_width);
//         map_y = (int)(next_y / gdata->minimap.px_in_cell_height);

//         // **Verificar colisión en Y**
//         if (map_y < 0 || map_y >= gdata->map.c_height || gdata->map.matrix[map_y][map_x] == '1')
//             break; // Colisión en Y

//         init_y = next_y; // Actualizamos la posición en Y

//         // **Dibujar la línea con grosor usando while**
//         double minimap_x = gdata->minimap.center_x + (init_x - gdata->player.x);
// double minimap_y = gdata->minimap.center_y + (init_y - gdata->player.y);
// double j = -thickness / 2;
// while (j <= thickness / 2)
// {
//     int offset_x = (int)(j * cos(vision_angle + M_PI_2));  
//     int offset_y = -(int)(j * sin(vision_angle + M_PI_2));

//     int pixel_x = (int)(minimap_x + offset_x);
//     int pixel_y = (int)(minimap_y + offset_y);

//     // Corregir el cálculo para verificar la colisión en el mapa
//     int pixel_map_x = (int)((gdata->player.x + offset_x) / gdata->minimap.px_in_cell_width);
//     int pixel_map_y = (int)((gdata->player.y + offset_y) / gdata->minimap.px_in_cell_height);

//     // **Verificar límites antes de dibujar**
//     if (pixel_x >= 0 && pixel_x < gdata->minimap.px_width && pixel_y >= 0 && pixel_y < gdata->minimap.px_height)
//     {
//         if (pixel_map_x >= 0 && pixel_map_x < gdata->map.c_width &&
//             pixel_map_y >= 0 && pixel_map_y < gdata->map.c_height &&
//             gdata->map.matrix[pixel_map_y][pixel_map_x] != '1' && gdata->map.matrix[pixel_map_y][pixel_map_x] != 'D' && gdata->map.matrix[pixel_map_y][pixel_map_x] != 'd')
//         {
//             mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, color);
//         }
//     }

//     j += 0.1;  // Incremento pequeño para evitar huecos en la línea
// }
//     }
// }



// void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color) 
// {
//     (void)vision_angle;
//     int i = 0;
    

//     while (i < vision.FOV.num_rays) 
//     {
//         //printf ("\nRAY %d\n", i);
//         t_ray *ray = &vision.FOV.rays[i];
        
//         // Coordenadas de inicio (posición del jugador en el centro del minimapa)
//         double draw_ray_x = x;
//         double draw_ray_y = y;
        
//         // Algoritmo DDA para dibujar la línea del rayo
//         double x_distance = (ray->px_collision_x - gdata->player.x) ; //Cuantos pixeles avanza el rayo en el eje x hasta colisionar
//         double y_distance = (ray->px_collision_y - gdata->player.y) ; //Cuantos pixeles avanza el rayo en el eje y hasta colisionar
//         double steps = fmax(fabs(x_distance), fabs(y_distance)); //Selecciona el valor mayor entre x_distance y y_distance. Porque queremos asegurarnos de recorrer toda la línea sin saltos. Si dx es mayor, significa que la línea se mueve más en X que en Y, así que debemos dividir el movimiento en suficientes pasos para cubrir todos los píxeles en X. Lo mismo ocurre si dy es mayor. Esto se hace para recorrer el rayo sin perder precision
//         // printf ("steps = %f\n", steps);
//         // printf ("ray->px_collision_y = %f\n", ray->px_collision_y);

//         // Evitar división por cero
//         if (steps < 1e-6) // Si steps es casi cero, significa que el rayo es muy corto o que end_ray_x == draw_ray_x y end_ray_y == draw_ray_y. En este caso, se omite este rayo y se pasa al siguiente (continue).
//         {
//             i++;
//             continue;
//         }
        
//         //El valor de steps nos ayuda a calcular cuánto debemos movernos en X e Y en cada paso.
//         double x_inc = x_distance / steps; //Cuánto avanzamos en X por cada paso
//         double y_inc = y_distance / steps; //Cuánto avanzamos en Y por cada paso
//         // Esto permite que el rayo se dibuje de manera uniforme sin saltos o distorsiones, asegurando que cada pixel del rayo esté correctamente alineado con su dirección real
//         // Sin este cálculo, el rayo no se trazaría correctamente, saltaría píxeles o se vería cortado.

//         int current_step = 0;

//         // Dibujar el rayo paso a paso

//         while (current_step < (int)steps) 
//         {
//             int px_x = (int)(draw_ray_x + 0.5); //Se convierten draw_ray_x y draw_ray_y a enteros (px_x, px_y) para representar píxeles en pantalla. Esto se hace porque la función mlx_put_pixel() espera coordenadas de píxeles enteras
//             int px_y = (int)(draw_ray_y + 0.5); // Añadir 0.5 antes de convertir a entero para redondear al entero más cercano
            
//             // Verificar límites del minimapa
//             if (px_x >= 0 && px_x < gdata->minimap.px_width && 
//                 px_y >= 0 && px_y < gdata->minimap.px_height) 
//             {
//                 // Verificar si hemos llegado al punto de colisión
//                 if (current_step == (int)(steps - 1))
//                     mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, 0xFF0000FF); // Punto rojo en la colisión
//                 else
//                     mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, color);
//             }
            
//             draw_ray_x += x_inc;
//             draw_ray_y += y_inc;
//             current_step++;
            
            
//             // Ajustar las coordenadas de colisión para reflejar la posición real en el mapa
//             int map_x = (int)((draw_ray_x - x + gdata->player.x) / gdata->minimap.px_in_cell_width);
//             int map_y = (int)((draw_ray_y - y + gdata->player.y) / gdata->minimap.px_in_cell_height);
            
//             // Verificar si hemos salido del mapa
//             if (map_x < 0 || map_x >= gdata->map.c_width ||
//                 map_y < 0 || map_y >= gdata->map.c_height)
//             {
//                 printf ("entro\n"); //BORRAR
//                 break;
//             }
//         }
//         i++;
//     }
// }





int ray_is_out_of_map(t_game *gdata, double draw_x, double draw_y, double origin_x, double origin_y)
{
    int map_x = (int)((draw_x - origin_x + gdata->player.x) / gdata->minimap.px_in_cell_width);
    int map_y = (int)((draw_y - origin_y + gdata->player.y) / gdata->minimap.px_in_cell_height);

    if (map_x < 0 || map_x >= gdata->map.c_width ||
        map_y < 0 || map_y >= gdata->map.c_height)
        return 1;
    return 0;
}

void draw_ray_pixel(t_game *gdata, double x, double y, double steps, int step, int color)
{
    int px_x = (int)(x + 0.5);
    int px_y = (int)(y + 0.5);

    if (px_x >= 0 && px_x < gdata->minimap.px_width &&
        px_y >= 0 && px_y < gdata->minimap.px_height)
    {
        if (step == (int)(steps - 1))
            mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, 0xFF0000FF);
        else
            mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, color);
    }
}

void draw_ray(t_game *gdata, t_ray *ray, double origin_x, double origin_y, int color)
{
    double x_distance = ray->px_collision_x - gdata->player.x;
    double y_distance = ray->px_collision_y - gdata->player.y;
    double steps = fmax(fabs(x_distance), fabs(y_distance));

    if (steps < 1e-6)
        return;

    double x_inc = x_distance / steps;
    double y_inc = y_distance / steps;

    double current_x = origin_x;
    double current_y = origin_y;
    int current_step = 0;

    while (current_step < (int)steps)
    {
        draw_ray_pixel(gdata, current_x, current_y, steps, current_step, color);
        current_x += x_inc;
        current_y += y_inc;
        current_step++;

        if (ray_is_out_of_map(gdata, current_x, current_y, origin_x, origin_y))
            break;
    }
}

void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color)
{
    (void)vision_angle;
    int i = 0;

    while (i < vision.FOV.num_rays)
    {
        t_ray *ray = &vision.FOV.rays[i];
        draw_ray(gdata, ray, x, y, color);
        i++;
    }
}

void    calculate_and_print_fov_and_vision_angle(t_game *gdata)
{
    calculate_fov(gdata, gdata->player.x, gdata->player.y);
    print_FOV (gdata, gdata->vision,gdata->minimap.center_x, gdata->minimap.center_y, gdata->vision.vision_angle, SOFT_YELLOW);
    print_vision_angle (gdata, gdata->player.x, gdata->player.y, gdata->vision.vision_angle, YELLOW1);
}
