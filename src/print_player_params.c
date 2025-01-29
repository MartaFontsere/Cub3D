/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/24 04:07:32 by mfontser         ###   ########.fr       */
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

void print_vision_angle(t_game *gdata, t_player player, double x, double y, int color, int thickness)
{
    int i;               
    double init_x;       
    double init_y;       
    double step_x;       
    double step_y;       
    int offset_x, offset_y; 

    printf("vision_angle antes de pintar rayo: %f\n", player.ray.vision_angle);

    init_x = x;
    init_y = y;

    step_x = cos(player.ray.vision_angle);
    step_y = sin(player.ray.vision_angle);

    i = 0;

    while (1)  
    {
        // **Verificar colisión para cada punto del grosor**
        double j = -thickness / 2;
        while (j <= thickness / 2) 
        {
            offset_x = (int)(j * cos(player.ray.vision_angle + M_PI_2));  
            offset_y = (int)(j * sin(player.ray.vision_angle + M_PI_2));  

            int check_x = (int)(init_x + offset_x);
            int check_y = (int)(init_y + offset_y);

            // **Si cualquier punto toca una pared, detener el rayo**
            if (gdata->map.matrix[(int)(check_y / gdata->minimap.cell_width)][(int)(check_x / gdata->minimap.cell_height)] == '1')
                return;

            mlx_put_pixel(gdata->mlx.image, check_x, check_y, color);
            j += 0.2;  
        }

        // **Avanzar el rayo**
        init_x += step_x;
        init_y += step_y;
        i++;
    }
}


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