/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/25 19:39:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_player (t_game *gdata, t_player player, double x, double y, int color)
{
	double x_limit;
	double y_limit;
	double draw_x;
	double draw_y;

	draw_y = -player.radius; // asi tengo el inicio del circulo en y
	y_limit = player.radius; // asi tengo el limite final del circulo en y
    while (draw_y <= y_limit)
	{
		draw_x = -player.radius;
		x_limit = player.radius;
		while (draw_x <= x_limit)
		{
            if (draw_x * draw_x + draw_y * draw_y <= player.radius * player.radius) // implementación directa de la definición de un círculo en coordenadas cartesianas
                mlx_put_pixel(gdata->mlx.mini_image, x + draw_x, y + draw_y, color); // al dibujar en la posicion draw relativa al centro del circulo, aseguramos que siempre se dibujara dentro del circulo.

            draw_x++;
		}
		draw_y++;
	}	
}


void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color)
{
    double init_x = x;
    double init_y = y;
    double ray_dir_x = -cos(vision_angle);
    double ray_dir_y = -sin(vision_angle); // Negativo para ajustar coordenadas
    int thickness = 4;  // Grosor del rayo
printf ("vision angle: |%f|\n", vision_angle * (180 / M_PI));
    while (1)
    {
        // **Avanzamos en X**
        double next_x = init_x + ray_dir_x;
        int map_x = (int)(next_x / gdata->minimap.px_in_cell_width);
        int map_y = (int)(init_y / gdata->minimap.px_in_cell_height);

        // **Verificar colisión en X**
        if (map_x < 0 || map_x >= gdata->map.cells_width || map_y < 0 || map_y >= gdata->map.cells_height)
            break; // Fuera del mapa

        if (gdata->map.matrix[map_y][map_x] == '1')
            break; // Colisión en X

        init_x = next_x; // Actualizamos la posición en X

        // **Avanzamos en Y**
        double next_y = init_y + ray_dir_y;
        map_x = (int)(init_x / gdata->minimap.px_in_cell_width);
        map_y = (int)(next_y / gdata->minimap.px_in_cell_height);

        // **Verificar colisión en Y**
        if (map_y < 0 || map_y >= gdata->map.cells_height || gdata->map.matrix[map_y][map_x] == '1')
            break; // Colisión en Y

        init_y = next_y; // Actualizamos la posición en Y

        // **Dibujar la línea con grosor usando while**
        double j = -thickness / 2;
        while (j <= thickness / 2)
        {
            int offset_x = (int)(j * cos(vision_angle + M_PI_2));  
            int offset_y = -(int)(j * sin(vision_angle + M_PI_2));

            int pixel_x = (int)(init_x + offset_x);
            int pixel_y = (int)(init_y + offset_y);

            int pixel_map_x = pixel_x / gdata->minimap.px_in_cell_width;
            int pixel_map_y = pixel_y / gdata->minimap.px_in_cell_height;

            // **Verificar límites antes de dibujar**
            if (pixel_map_x >= 0 && pixel_map_x < gdata->map.cells_width &&
                pixel_map_y >= 0 && pixel_map_y < gdata->map.cells_height &&
                gdata->map.matrix[pixel_map_y][pixel_map_x] != '1')
            {
                mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, color);
            }

            j += 0.1;  // Incremento pequeño para evitar huecos en la línea
        }
    }
}



void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color) 
{
    (void)vision_angle;
    int i = 0;
    

  //   while (i < vision.FOV.num_rays) 
  //   {
  //      printf ("colision en y: %f\n", vision.FOV.rays[i].px_collision_y);
  //      i++;
  //   }
  // i = 0;

    while (i < vision.FOV.num_rays) 
    {
        //printf ("\nRAY %d\n", i);
        t_ray *ray = &vision.FOV.rays[i];
        
        // Coordenadas de inicio (posición del jugador)
        double draw_ray_x = x;
        double draw_ray_y = y;
        
        // Algoritmo DDA para dibujar la línea del rayo
        double x_distance = ray->px_collision_x - x; //Cuantos pixeles avanza el rayo en el eje x hasta colisionar
        double y_distance = ray->px_collision_y - y; //Cuantos pixeles avanza el rayo en el eje y hasta colisionar
        double steps = fmax(fabs(x_distance), fabs(y_distance)); //Selecciona el valor mayor entre x_distance y y_distance. Porque queremos asegurarnos de recorrer toda la línea sin saltos. Si dx es mayor, significa que la línea se mueve más en X que en Y, así que debemos dividir el movimiento en suficientes pasos para cubrir todos los píxeles en X. Lo mismo ocurre si dy es mayor. Esto se hace para recorrer el rayo sin perder precision
        // printf ("steps = %f\n", steps);
        // printf ("ray->px_collision_y = %f\n", ray->px_collision_y);

        // Evitar división por cero
        if (steps < 1e-6) // Si steps es casi cero, significa que el rayo es muy corto o que end_ray_x == draw_ray_x y end_ray_y == draw_ray_y. En este caso, se omite este rayo y se pasa al siguiente (continue).
        {
            i++;
            continue;
        }
        
        //El valor de steps nos ayuda a calcular cuánto debemos movernos en X e Y en cada paso.
        double x_inc = x_distance / steps; //Cuánto avanzamos en X por cada paso
        double y_inc = y_distance / steps; //Cuánto avanzamos en Y por cada paso
        // Esto permite que el rayo se dibuje de manera uniforme sin saltos o distorsiones, asegurando que cada pixel del rayo esté correctamente alineado con su dirección real
        // Sin este cálculo, el rayo no se trazaría correctamente, saltaría píxeles o se vería cortado.

        int current_step = 0;
        printf ("llego\n");
        // Dibujar el rayo paso a paso
        while (current_step < (int)steps) 
        {
            int px_x = (int)draw_ray_x; //Se convierten draw_ray_x y draw_ray_y a enteros (px_x, px_y) para representar píxeles en pantalla. Esto se hace porque la función mlx_put_pixel() espera coordenadas de píxeles enteras
            int px_y = (int)draw_ray_y;
            
            // Verificar límites del minimapa
            if (px_x >= 0 && px_x < gdata->minimap.px_width && 
                px_y >= 0 && px_y < gdata->minimap.px_height) 
            {
                // Verificar si hemos llegado al punto de colisión
                if (current_step == (int)(steps - 1))
                    mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, 0xFF0000FF); // Punto rojo en la colisión
                else
                {
                    printf ("***************\n");
                    mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, color);
                }
            }
            
            draw_ray_x += x_inc;
            draw_ray_y += y_inc;
            current_step++;
            
            // Verificar si hemos salido del mapa
            int map_x = (int)(draw_ray_x / gdata->minimap.px_in_cell_width);
            int map_y = (int)(draw_ray_y / gdata->minimap.px_in_cell_height);
            
            if (map_x < 0 || map_x >= gdata->map.cells_width ||
                map_y < 0 || map_y >= gdata->map.cells_height)
            {
                break;
            }
        }
        i++;
    }
}







