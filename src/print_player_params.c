/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/08 12:11:00 by mfontser         ###   ########.fr       */
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
                mlx_put_pixel(gdata->mlx.image, x + draw_x, y + draw_y, color); // al dibujar en la posicion draw relativa al centro del circulo, aseguramos que siempre se dibujara dentro del circulo.
            draw_x++;
		}
		draw_y++;
	}	
}

//VERSION 1
// void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color) //REVISAR RAYO PASA POR LA ESQUINA
// {              
//     double init_x; //Posición inicial del rayo, que empieza en x, y, (el centro de las coordenadas del player)    
//     double init_y;       
//     double ray_dir_x; // Dirección del rayo, calculada con el coseno y seno del ángulo de visión.      
//     double ray_dir_y; 
//     int 	thickness;      
//     int 	offset_x; 
//     int 	offset_y; // Para gestionar el grosor de la linea

//     printf("vision_angle antes de pintar rayo: %f\n", vision_angle);

//     init_x = x;
//     init_y = y;

//     ray_dir_x = - cos(vision_angle);
//     ray_dir_y = - sin(vision_angle); // en negativo porque si va hacia arriba debe ser negativo, al reves de las coordenadas cartesianas normales, por eso tenemos que ajustarlo
//     thickness = 4;

//      // Mientras no colisionemos con una pared ('1' en el mapa)
//     while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     {
//         // **Verificar colisión para cada punto del grosor**
//         double j = -thickness / 2;
//         while (j <= thickness / 2) 
//         {
//         	// Recalculamos el desplazamiento en X e Y para el grosor
//             offset_x = (int)(j * cos(vision_angle + M_PI_2));  // M_PI_2 nos da la perpendicular, para dibujar el grosor perpendicularmente a la direccion del rayo
//             offset_y = -(int)(j * sin(vision_angle + M_PI_2));  

//             // Verificar si la posición ajustada colisiona con una pared antes de dibujar
//             if (gdata->map.matrix[(int)((init_y + offset_y) / gdata->minimap.cell_width)][(int)((init_x + offset_x) / gdata->minimap.cell_height)] != '1')
//                 mlx_put_pixel(gdata->mlx.image, (int)(init_x + offset_x), (int)(init_y + offset_y), color);

//             j += 0.1;  // Dibujamos el píxel desplazado por el grosor en la imagen del juego. // Se avanza en pasos pequeños para un grosor más uniforme. En lugar de hacer j++, avanzamos de 0.2 en 0.2. Esto ayuda a evitar espacios vacíos entre píxeles y suaviza la línea.
//         }

//         // **Avanzar el rayo en X e Y segun el angulo**
//         init_x = init_x + ray_dir_x; // Después de dibujar el grosor en la posición actual, avanzamos en la dirección del rayo.
//         init_y = init_y + ray_dir_y;
//     }
// }

//VERSION 2 // SIGUE TRAVESANDO ESQUINAS
// void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color)
// {              
//     double init_x = x;
//     double init_y = y;
//     double ray_dir_x = -cos(vision_angle);
//     double ray_dir_y = -sin(vision_angle); // Negativo para ajustar coordenadas
//     int thickness = 4;  // Grosor del rayo

//     while (1)
//     {
//         int map_x = (int)(init_x / gdata->minimap.cell_width);
//         int map_y = (int)(init_y / gdata->minimap.cell_height);

//         // **Verificar que estamos dentro del mapa antes de acceder a matrix**
//         if (map_x < 0 || map_x >= gdata->map.width || map_y < 0 || map_y >= gdata->map.height)
//             break;

//         // **Si choca con una pared, detenemos el rayo**
//         if (gdata->map.matrix[map_y][map_x] == '1')
//             break;

//         // **Dibujar la línea con grosor usando while**
//         double j = -thickness / 2;
//         while (j <= thickness / 2)
//         {
//             int offset_x = (int)(j * cos(vision_angle + M_PI_2));  
//             int offset_y = -(int)(j * sin(vision_angle + M_PI_2));

//             int pixel_x = (int)(init_x + offset_x);
//             int pixel_y = (int)(init_y + offset_y);

//             int pixel_map_x = pixel_x / gdata->minimap.cell_width;
//             int pixel_map_y = pixel_y / gdata->minimap.cell_height;

//             // **Verificar límites antes de dibujar**
//             if (pixel_map_x >= 0 && pixel_map_x < gdata->map.width &&
//                 pixel_map_y >= 0 && pixel_map_y < gdata->map.height &&
//                 gdata->map.matrix[pixel_map_y][pixel_map_x] != '1')
//             {
//                 mlx_put_pixel(gdata->mlx.image, pixel_x, pixel_y, color);
//             }

//             j += 0.1;  // Incremento pequeño para evitar huecos en la línea
//         }

//         // **Avanzamos en X y luego en Y**
//         init_x += ray_dir_x;
//         init_y += ray_dir_y;
//     }
// }

//VERSION 3 // SIGUE TRAVESANDO ESQUINAS PERO SIN SEGFAULT
void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color)
{
    double init_x = x;
    double init_y = y;
    double ray_dir_x = cos(vision_angle);
    double ray_dir_y = -sin(vision_angle); // Negativo para ajustar coordenadas
    int thickness = 4;  // Grosor del rayo
printf ("vision angle: |%f|\n", vision_angle * (180 / M_PI));
    while (1)
    {
        // **Avanzamos en X**
        double next_x = init_x + ray_dir_x;
        int map_x = (int)(next_x / gdata->minimap.cell_width);
        int map_y = (int)(init_y / gdata->minimap.cell_height);

        // **Verificar colisión en X**
        if (map_x < 0 || map_x >= gdata->map.width || map_y < 0 || map_y >= gdata->map.height)
            break; // Fuera del mapa

        if (gdata->map.matrix[map_y][map_x] == '1')
            break; // Colisión en X

        init_x = next_x; // Actualizamos la posición en X

        // **Avanzamos en Y**
        double next_y = init_y + ray_dir_y;
        map_x = (int)(init_x / gdata->minimap.cell_width);
        map_y = (int)(next_y / gdata->minimap.cell_height);

        // **Verificar colisión en Y**
        if (map_y < 0 || map_y >= gdata->map.height || gdata->map.matrix[map_y][map_x] == '1')
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

            int pixel_map_x = pixel_x / gdata->minimap.cell_width;
            int pixel_map_y = pixel_y / gdata->minimap.cell_height;

            // **Verificar límites antes de dibujar**
            if (pixel_map_x >= 0 && pixel_map_x < gdata->map.width &&
                pixel_map_y >= 0 && pixel_map_y < gdata->map.height &&
                gdata->map.matrix[pixel_map_y][pixel_map_x] != '1')
            {
                mlx_put_pixel(gdata->mlx.image, pixel_x, pixel_y, color);
            }

            j += 0.1;  // Incremento pequeño para evitar huecos en la línea
        }
    }
}



// void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color) //REVISAR RAYO PASA POR LA ESQUINA
// {              
//     double init_x; //Posición inicial del rayo, que empieza en x, y, (el centro de las coordenadas del player)    
//     double init_y;       
//     double ray_dir_x; // Dirección del rayo, calculada con el coseno y seno del ángulo de visión.      
//     double ray_dir_y; 
//     int 	thickness;      
//     int 	offset_x; 
//     int 	offset_y; // Para gestionar el grosor de la linea

//     printf("vision_angle antes de pintar rayo: %f\n", vision_angle);

//     init_x = x;
//     init_y = y;

//     ray_dir_x = - cos(vision_angle); // en negativo porque si va hacia arriba debe ser negativo, al reves de las coordenadas cartesianas normales, por eso tenemos que ajustarlo
//     ray_dir_y = - sin(vision_angle); // en negativo porque si va hacia arriba debe ser negativo, al reves de las coordenadas cartesianas normales, por eso tenemos que ajustarlo
//     thickness = 4;

//      // Mientras no colisionemos con una pared ('1' en el mapa)
//     while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     {
//         // **Verificar colisión para cada punto del grosor**
//         double j = -thickness / 2;
//         while (j <= thickness / 2) 
//         {
//         	// Recalculamos el desplazamiento en X e Y para el grosor
//             offset_x = (int)(j * cos(vision_angle + M_PI_2));  // M_PI_2 nos da la perpendicular, para dibujar el grosor perpendicularmente a la direccion del rayo
//             offset_y = -(int)(j * sin(vision_angle + M_PI_2));  

//             // **Comprobamos primero en X**
//             double next_x = init_x + ray_dir_x;
//             int check_x_in_map = (int)((next_x + offset_x)/ gdata->minimap.cell_width);
//             int check_y_in_map = (int)(init_y / gdata->minimap.cell_height);

//             // **Si choca con una pared en X, detenemos el rayo**
//             if (check_x_in_map < 0 || check_x_in_map >= gdata->map.width || gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
//                 break;
//             init_x = next_x; // Solo avanzamos si no hay colisión

//             // **Comprobamos en Y**
//             double next_y = init_y + ray_dir_y;
//             check_x_in_map = (int)(init_x + offset_y/ gdata->minimap.cell_width);
//             check_y_in_map = (int)(next_y / gdata->minimap.cell_height);

//             // **Si choca con una pared en Y, detenemos el rayo**
//             if (check_y_in_map < 0 || check_y_in_map >= gdata->map.height || gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
//                 break;
//             init_y = next_y; // Solo avanzamos si no hay colisión

//             // **Si seguimos aquí, es seguro pintar**
//             mlx_put_pixel(gdata->mlx.image, (int)init_x, (int)init_y, color);

//             j += 0.1;  // Dibujamos el píxel desplazado por el grosor en la imagen del juego. // Se avanza en pasos pequeños para un grosor más uniforme. En lugar de hacer j++, avanzamos de 0.2 en 0.2. Esto ayuda a evitar espacios vacíos entre píxeles y suaviza la línea.
//         }
//     }
// }

// void print_FOV(t_game *gdata, t_player player, double x, double y, double vision_angle, int color) //REVISAR RAYO PASA POR LA ESQUINA
// {
// 	double 	start_angle;
//     double 	end_angle;
//     double 	angle_between_rays;
//     double 	ray_angle;
//     int 	ray_index;
//     double init_x, init_y;
//     double ray_dir_x; // Dirección del rayo, calculada con el coseno y seno del ángulo de visión.      
//     double ray_dir_y; 
//     double distance;


//     start_angle = vision_angle - (player.ray.FOV / 2);  // Mitad del FOV a la izquierda
//     end_angle = vision_angle + (player.ray.FOV / 2);    // Mitad del FOV a la derecha

// // **Un rayo por cada píxel horizontal en el FOV**
//     angle_between_rays =  player.ray.FOV / (double)gdata->minimap.width; //cuánto debemos movernos entre cada rayo para repartirlos uniformemente dentro del FOV. En este caso calculamos un rayo por cada pixel hasta end angle
//     ray_angle = start_angle; // el angulo que se ira moviendo. Empieza en start y para en end.
//     ray_index = 0;

//     while (ray_angle <= end_angle)
//     {

//     	init_x = x;
//         init_y = y;
//         ray_dir_x = - cos(ray_angle);
//         ray_dir_y = - sin(ray_angle);
//         distance = 0;
//     	while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     	{
//             mlx_put_pixel(gdata->mlx.image, (int)init_x, (int)init_y, color);
//             init_x = init_x + ray_dir_x; // avanzamos en la dirección del rayo.
//         	init_y = init_y + ray_dir_y;
//             distance += sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
//         }
//         ray_angle += angle_between_rays; // **Incrementamos dinámicamente el ángulo**
//         ray_index++; // Siguiente rayo
//     }

// }



//BUENO // SIGUE TRAVESANDO ESQUINAS
// void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color)
// {

// //la cantidad de rayos siempre va a ser el ancho de la ventana en pixeles, es la cantidad de rayos que vamos a ver. Dependiendo del fov, esos rayos van a estar mas o menos espaciados, pero se tienen que repartir.Cada rayo tendra un angulo dentro del FOV, y proporcionara una informacion que es lo que se vera en pantalla. Cuando vayamos moviendo el fov la informacion se actualizara, pero dentro de ese fov 
// //cada rayo representa un píxel en la imagen final, por eso es el ancho de la ventana.
// //A mayor FOV, más amplia la visión. La densidad de rayos (por grado) depende del ancho de pantalla

//     double start_angle = vision_angle - (vision.FOV.fov_rad / 2);
//     double end_angle = vision_angle + (vision.FOV.fov_rad / 2);
//     double ray_angle_increment = vision.FOV.fov_rad / (double)gdata->minimap.width;
//     double ray_angle = start_angle;

//     while (ray_angle <= end_angle)
//     {
//         double init_x = x;
//         double init_y = y;
//         double ray_dir_x = - cos(ray_angle);
//         double ray_dir_y = - sin(ray_angle);

//         while (1) // Bucle infinito que se romperá manualmente
//         {
//             // **Comprobamos primero en X**
//             double next_x = init_x + ray_dir_x;
//             int check_x_in_map = (int)(next_x / gdata->minimap.cell_width);
//             int check_y_in_map = (int)(init_y / gdata->minimap.cell_height);

//             // **Si choca con una pared en X, detenemos el rayo**
//             if (check_x_in_map < 0 || check_x_in_map >= gdata->map.width || gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
//                 break;
//             init_x = next_x; // Solo avanzamos si no hay colisión

//             // **Comprobamos en Y**
//             double next_y = init_y + ray_dir_y;
//             check_x_in_map = (int)(init_x / gdata->minimap.cell_width);
//             check_y_in_map = (int)(next_y / gdata->minimap.cell_height);

//             // **Si choca con una pared en Y, detenemos el rayo**
//             if (check_y_in_map < 0 || check_y_in_map >= gdata->map.height || gdata->map.matrix[check_y_in_map][check_x_in_map] == '1')
//                 break;
//             init_y = next_y; // Solo avanzamos si no hay colisión

//             // **Si seguimos aquí, es seguro pintar**
//             mlx_put_pixel(gdata->mlx.image, (int)init_x, (int)init_y, color);
//         }

//         ray_angle += ray_angle_increment; // **Siguiente rayo**
//     }
// }

//VERSION 1 CON DDA

// void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color) 
// {
//     (void)vision_angle; // Si no se usa pero el parámetro está en la firma
//     int i = 0;

//     while (i < vision.FOV.num_rays) 
//     {
//         t_ray *ray = &vision.FOV.rays[i];
//         // Convertir coordenadas de colisión a píxeles del minimapa
//         double end_ray_x = ray->px_collision_x;
//         double end_ray_y = ray->px_collision_y;

//         // Coordenadas de inicio (posición del jugador ya en píxeles)de pintar el rayo, esta posicion la iremos avanzando segun el angulo de cada rayo
//         double draw_ray_x = x; //double start_ray_x = x;
//         double draw_ray_y = y; //double start_ray_y = y;
        
//         // Algoritmo DDA para dibujar línea
//         double dx = end_ray_x - draw_ray_x;
//         double dy = end_ray_y - draw_ray_y;
//         double steps = fmax(fabs(dx), fabs(dy));
//         double x_inc = dx / steps;
//         double y_inc = dy / steps;
        
//         int current_step = 0;
//         //printf ("steps |%f|\n", steps);
//         while (current_step++ < steps) 
//         {
//             int px_x = (int)draw_ray_x;
//             int px_y = (int)draw_ray_y;
            
//             // Dibujar el píxel si está dentro del minimapa
//             if (px_x >= 0 && px_x < gdata->minimap.width && 
//                 px_y >= 0 && px_y < gdata->minimap.height) 
//             //printf ("whileee\n");
//             {
//             	//printf ("imprimooooooooooooo\n");
//                 mlx_put_pixel(gdata->mlx.image, px_x, px_y, color);
//             }
            
//             draw_ray_x += x_inc;
//             draw_ray_y += y_inc;
            
//             // Romper si el rayo sale del mapa antes de chocar
//             if ((int)(draw_ray_x / gdata->minimap.cell_width) >= gdata->map.width ||
//                 (int)(draw_ray_y / gdata->minimap.cell_height) >= gdata->map.height) 
//             {
//                 break;
//             }
//         }
//             // printf ("i |%d|\n", i);
//             // double angle_step = (vision.FOV.fov_rad / vision.FOV.num_rays);
//             // printf("Rayo %d - Angulo: %f\n", i, angle_step);
//             // printf("Rayo %d - Colisión en (%.2f, %.2f)\n", i, ray->collision_x, ray->collision_y);
//         i++;
//     }
// }

//VERSION 2 CON DDA

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
        
        // Dibujar el rayo paso a paso
        while (current_step < (int)steps) 
        {
            int px_x = (int)draw_ray_x; //Se convierten draw_ray_x y draw_ray_y a enteros (px_x, px_y) para representar píxeles en pantalla. Esto se hace porque la función mlx_put_pixel() espera coordenadas de píxeles enteras
            int px_y = (int)draw_ray_y;
            
            // Verificar límites del minimapa
            if (px_x >= 0 && px_x < gdata->minimap.width && 
                px_y >= 0 && px_y < gdata->minimap.height) 
            {
                // Verificar si hemos llegado al punto de colisión
                if (current_step == (int)(steps - 1))
                    mlx_put_pixel(gdata->mlx.image, px_x, px_y, 0xFF0000FF); // Punto rojo en la colisión
                else
                {
                    mlx_put_pixel(gdata->mlx.image, px_x, px_y, color);
                }
            }
            
            draw_ray_x += x_inc;
            draw_ray_y += y_inc;
            current_step++;
            
            // Verificar si hemos salido del mapa
            int map_x = (int)(draw_ray_x / gdata->minimap.cell_width);
            int map_y = (int)(draw_ray_y / gdata->minimap.cell_height);
            
            if (map_x < 0 || map_x >= gdata->map.width ||
                map_y < 0 || map_y >= gdata->map.height)
            {
                break;
            }
        }
        i++;
    }
}












// / **Guardar la información del rayo en la estructura**
//         player->rays[ray_index].angle = ray_angle;
//         player->rays[ray_index].hit_x = init_x;
//         player->rays[ray_index].hit_y = init_y;
//         player->rays[ray_index].distance = distance;





// void print_FOV(t_game *gdata, t_player player, double x, double y, double vision_angle, int color)
// {
//     double start_angle = vision_angle - (player.ray.FOV / 2);
//     double end_angle = vision_angle + (player.ray.FOV / 2);
//     double angle_between_rays = player.ray.FOV / (double)gdata->minimap.width;
//     double ray_angle = start_angle;

//     while (ray_angle <= end_angle)
//     {
//         double init_x = x;
//         double init_y = y;
//         double ray_dir_x = -cos(ray_angle);
//         double ray_dir_y = -sin(ray_angle);

//         while (1)
//         {
//             double next_x = init_x + ray_dir_x * 0.5;
//             double next_y = init_y + ray_dir_y * 0.5;
//             int map_x = (int)(next_x / gdata->minimap.cell_width);
//             int map_y = (int)(next_y / gdata->minimap.cell_height);

//             // **Si salimos del mapa, detenemos el rayo**
//             if (map_x < 0 || map_x >= gdata->map.width || map_y < 0 || map_y >= gdata->map.height)
//                 break;

//             // **Si el siguiente punto choca con una pared, detenemos el rayo**
//             if (gdata->map.matrix[map_y][(int)(init_x / gdata->minimap.cell_width)] == '1' || 
//                 gdata->map.matrix[(int)(init_y / gdata->minimap.cell_height)][map_x] == '1')
//                 break;

//             // **Pintamos solo si no hay colisión**
//             mlx_put_pixel(gdata->mlx.image, (int)next_x, (int)next_y, color);

//             // **Avanzamos el rayo**
//             init_x = next_x;
//             init_y = next_y;
//         }

//         ray_angle += angle_between_rays; // **Siguiente rayo**
//     }
// }







//OPCION MAS PRECISA PARA QUE EL RAYO NO ENTRE EN LAS PAREDES. POR SI SE NECESITA
// void print_vision_angle(t_game *gdata, t_player player, double x, double y, double vision_angle, int color)
// {              
//     double init_x; //Posición inicial del rayo, que empieza en x, y, (el centro de las coordenadas del player)    
//     double init_y;       
//     double step_x; // Dirección del rayo, calculada con el coseno y seno del ángulo de visión.      
//     double step_y;
// int 	thickness;         
//     int offset_x, offset_y; // Para gestionar el grosor de la linea

//     printf("vision_angle antes de pintar rayo: %f\n", player.ray.vision_angle);

//     init_x = x;
//     init_y = y;

//     step_x = cos(vision_angle);
//     step_y = sin(vision_angle);
// 		thickness = 4;
//     while (1)  // Este bucle se ejecuta hasta que el rayo colisione con una pared (se romperá con return)
//     {
//         // **Verificar colisión para cada punto del grosor, en una dirección perpendicular al rayo**
//         double j = -thickness / 2;
//         while (j <= thickness / 2) 
//         {
// 				//Recalculamos el desplazamiento en X e Y para el grosor
//             offset_x = (int)(j * cos(vision_angle + M_PI_2));  // M_PI_2 nos da la perpendicular, para dibujar el grosor perpendicularmente a la direccion del rayo
//             offset_y = (int)(j * sin(vision_angle + M_PI_2));  
				
// 				//Convertimos init_x + offset_x y init_y + offset_y en coordenadas de la celda del mapa
//             int check_x = (int)(init_x + offset_x); 
//             int check_y = (int)(init_y + offset_y);

//             // **Si cualquier punto del grosor del rayo toca una pared, detener el rayo**
//             if (gdata->map.matrix[(int)(check_y / gdata->minimap.cell_width)][(int)(check_x / gdata->minimap.cell_height)] == '1')
//                 return;

// 				//Antes solo verificabas la colisión con init_x, init_y (el centro del rayo). Ahora verificas cada parte del grosor, por lo que el rayo no puede atravesar paredes aunque sea grueso.
// 			mlx_put_pixel(gdata->mlx.image, check_x, check_y, color);
//             j += 0.1;  // Dibujamos el píxel desplazado por el grosor en la imagen del juego. // Se avanza en pasos pequeños para un grosor más uniforme. En lugar de hacer j++, avanzamos de 0.2 en 0.2. Esto ayuda a evitar espacios vacíos entre píxeles y suaviza la línea.
//         }

//          // **Avanzar el rayo en X e Y segun el angulo**
//         init_x += step_x; // Después de dibujar el grosor en la posición actual, avanzamos en la dirección del rayo.
//         init_y += step_y;
//     }
// }


// void print_vision_angle(t_game *gdata, t_player player, double x, double y, int color, int thickness) // Grosor de la línea
// {
//     int i;               // Controla la longitud de la línea
//     double init_x;       // Coordenada inicial X para dibujar
//     double init_y;       // Coordenada inicial Y para dibujar
//     double step_x;       // Desplazamiento en X según el ángulo
//     double step_y;       // Desplazamiento en Y según el ángulo
//     int offset_x, offset_y; // Desplazamientos en X e Y para el grosor

//     printf("vision_angle antes de pintar rayo: %f\n", player.ray.vision_angle);

//     // La línea comienza en la posición del jugador
//     init_x = x;
//     init_y = y;

//     // Determinamos el paso en cada iteración según el ángulo de visión
//     step_x = cos(player.ray.vision_angle);  // Desplazamiento en X según el ángulo
//     step_y = sin(player.ray.vision_angle); 

//     i = 0;

//     // Mientras no colisionemos con una pared ('1' en el mapa)
//     while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     {
//         // Dibujamos una línea de "grosor" alrededor del ángulo
//         double j = -thickness / 2;
//         while (j <= thickness / 2) 
//         {
//             // Recalculamos el desplazamiento en X e Y para el grosor
//             offset_x = (int)(j * cos(player.ray.vision_angle + M_PI_2));  
//             offset_y = (int)(j * sin(player.ray.vision_angle + M_PI_2));  

//             // Dibujamos el píxel en la posición ajustada para el grosor
//             mlx_put_pixel(gdata->mlx.image, (int)(init_x + offset_x), (int)(init_y + offset_y), color);

//             j += 0.2;  // Se avanza en pasos pequeños para un grosor más uniforme
//         }

//         // Movemos la posición en X y Y según el ángulo
//         init_x += step_x;
//         init_y += step_y;

//         i++;
//     }

//     printf("punto de colision |%d||%d|\n", (int)(init_x / gdata->minimap.cell_height), (int)(init_y / gdata->minimap.cell_width));
// }



// void print_vision_angle(t_game *gdata, t_player player, double x, double y, int color)
// {
//     double init_x = x;
//     double init_y = y;
//     double step_x, step_y;
//     double delta_x, delta_y;
//     double error_x = 0.0, error_y = 0.0;
//     double offset_x, offset_y;
//     double j;
//     int thickness = 2; // Grosor de la línea
//     double abs_delta_x, abs_delta_y, max_delta;

//     printf("vision_angle antes de pintar rayo: %f\n", player.ray.vision_angle);

//     // Determinamos el desplazamiento en cada iteración según el ángulo de visión
//     delta_x = cos(player.ray.vision_angle);
//     delta_y = sin(player.ray.vision_angle);

//     // Cálculo del valor absoluto de delta_x y delta_y sin usar fabs()
//     if (delta_x < 0)
//         abs_delta_x = -delta_x;
//     else
//         abs_delta_x = delta_x;

//     if (delta_y < 0)
//         abs_delta_y = -delta_y;
//     else
//         abs_delta_y = delta_y;

//     // Cálculo de max_delta sin fmax()
//     if (abs_delta_x > abs_delta_y)
//         max_delta = abs_delta_x;
//     else
//         max_delta = abs_delta_y;

//     // Normalización de los pasos
//     step_x = delta_x / max_delta;
//     step_y = delta_y / max_delta;

//     // Mientras no colisionemos con una pared ('1' en el mapa)
//     while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     {
//         // Inicializar j para dibujar el grosor
//         j = -thickness / 2;
//         while (j <= thickness / 2)
//         {
//             // Calculamos el offset perpendicular a la dirección del rayo
//             offset_x = j * cos(player.ray.vision_angle + M_PI_2);
//             offset_y = j * sin(player.ray.vision_angle + M_PI_2);

//             // Dibujamos el píxel con grosor
//             mlx_put_pixel(gdata->mlx.image, (int)(init_x + offset_x), (int)(init_y + offset_y), color);

//             j += 1.0;
//         }

//         // DDA Step: Ajustar el error y los pasos sin fabs()
//         if (step_x < 0)
//             error_x -= step_x;
//         else
//             error_x += step_x;

//         if (step_y < 0)
//             error_y -= step_y;
//         else
//             error_y += step_y;

//         if (error_x >= 0.5)
//         {
//             init_x += step_x;
//             error_x -= 1.0;
//         }
//         if (error_y >= 0.5)
//         {
//             init_y += step_y;
//             error_y -= 1.0;
//         }
//     }

//     printf("punto de colision |%d||%d|\n", (int)(init_x / gdata->minimap.cell_height), (int)(init_y / gdata->minimap.cell_width));
// }




    
// void print_vision_angle(t_game *gdata, t_player player, double x, double y, int color)
// {
//     int i;               // Controla la longitud de la línea
//     double init_x;       // Coordenada inicial X para dibujar
//     double init_y;       // Coordenada inicial Y para dibujar
//     int thickness;       // Controla el grosor de la línea
//     double step_x;       // Desplazamiento en X según el ángulo
//     double step_y;       // Desplazamiento en Y según el ángulo

//     printf("point of view es: |%f|\n", player.ray.vision_angle);

//     // La línea comienza en la posición del jugador
//     init_x = x;
//     init_y = y;

//     // Determinamos el paso en cada iteración según el ángulo de visión
//     step_x = cos(player.ray.vision_angle) * 2; // Paso en X
//     step_y = sin(player.ray.vision_angle) * 2; // Paso en Y

//     i = 0;

//     // Mientras no colisionemos con una pared ('1' en el mapa)
//     while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
//     {
//         // Dibujamos una línea de "grosor" 2 alrededor del ángulo
//         init_x += step_x; // Ajustamos la posición en X
//         init_y += step_y; // Ajustamos la posición en Y

//         thickness = 0; // Reset del grosor en cada paso
//         while (thickness < 2)
//         {
//             mlx_put_pixel(gdata->mlx.image, init_x + thickness, init_y, color);
//             thickness++;
//         }
//         i++;
//     }

//     // Mostramos dónde se detuvo la línea al chocar
//     printf("punto de colision |%d||%d|\n", (int)(init_x / gdata->minimap.cell_height), (int)(init_y / gdata->minimap.cell_width));
// }









// void print_vision_angle (t_game *gdata, t_player player, double x, double y, int color) //TOTALMENTE HARDCODEADO
// {
// 	int i; // Controla la longitud de la línea
// 	double init_x; // Coordenada inicial X para dibujar
// 	double init_y; // Coordenada inicial Y para dibujar
// 	int thickness; // Controla el grosor de la línea


// 	printf ("point of view es: |%f|\n", player.ray.vision_angle);
// 	i = 0;
	
// 	if (player.ray.vision_angle == NORTH)
// 	{
// 		init_x = x;
// 		init_y = y - player.radius; // Coordenada inicial (parte superior del círculo del jugador)
// 		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
// 		{
// 			init_x = x - 1; // Comienza desde el centro menos la mitad del grosor
// 			thickness = 0; // se reinicia en cada iteración del bucle externo
// 			while (thickness < 2)
// 			{
// 				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
// 				thickness++;
// 				init_x++;
// 			}
// 			init_y--;
// 			i++;
// 		}
// 		printf ("punto de colision|%d||%d|\n", (int)(init_x / gdata->minimap.cell_height), (int)(init_y / gdata->minimap.cell_width));

// 	}

// 	else if (player.ray.vision_angle == SOUTH)
// 	{
// 		init_x = x;
// 		init_y = y + player.radius;
// 		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
// 		{
// 			init_x = x - 1; // Comienza desde el centro menos la mitad del grosor
// 			thickness = 0; // se reinicia en cada iteración del bucle externo
// 			while (thickness < 2)
// 			{
// 				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
// 				thickness++;
// 				init_x++;
// 			}
// 			init_y++;
// 			i++;
// 		}
// 	}

// 	else if (player.ray.vision_angle == EAST)
// 	{
// 		init_x = x + player.radius;
// 		init_y = y;
// 		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
// 		{
// 			init_y = y -1; // Comienza desde el centro menos la mitad del grosor
// 			thickness = 0; // se reinicia en cada iteración del bucle externo
// 			while (thickness < 2)
// 			{
// 				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
// 				thickness++;
// 				init_y++;
// 			}
// 			init_x++;
// 			i++;
// 		}
// 	}

// 	else if (player.ray.vision_angle == WEST)
// 	{
// 		init_x = x - player.radius;
// 		init_y = y;
// 		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
// 		{
// 			init_y = y +1; // Comienza desde el centro menos la mitad del grosor
// 			thickness = 0; // se reinicia en cada iteración del bucle externo
// 			while (thickness < 2)
// 			{
// 				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
// 				thickness++;
// 				init_y++;
// 			}
// 			init_x--;
// 			i++;
// 		}
// 	}
// }