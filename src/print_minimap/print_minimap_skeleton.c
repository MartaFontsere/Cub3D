/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_skeleton.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/11 20:21:31 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



// void print_empty_space (t_mlx mlx, t_minimap minimap, t_map map) //REVISAR EXPLICACION
// {
// 	int x;
// 	int y;
// 	int pixels_y;
// 	int pixels_x; //j
// 	int pixels_count1;
// 	int pixels_count2;
// 	int color_flag;

// 	y = 0;
// 	while (map.matrix[y])
// 	{
// 		x = 0;
// 		while (map.matrix[y][x])
// 		{
// 			if (map.matrix[y][x] == ' ')
// 			{
// 				pixels_y = y * (minimap.px_height / map.c_height);
// 				pixels_count1 = 0;
// 				while (pixels_count1 < minimap.px_height / map.c_height)
// 				{
// 					pixels_x = x * minimap.px_width / map.c_width;
// 					pixels_count2 = 0;
// 					while (pixels_count2 < minimap.px_width / map.c_width)
// 					{
// 						color_flag = ((pixels_x / 7 + pixels_y / 7) % 2); // Al dividir entre 7 hago que se mantenga el mismo color 7 pixeles
// 						if (color_flag == 0)
//                            	mlx_put_pixel(mlx.mini_image, pixels_x, pixels_y, BLACK);
//                         else
//                             mlx_put_pixel(mlx.mini_image, pixels_x, pixels_y, MEDIUM_GREY);

// 						pixels_x++;
// 						pixels_count2++;
// 					}
// 					pixels_y++;
// 					pixels_count1++;
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void print_walls (t_mlx mlx, t_minimap minimap, t_map map)
// {
// 	int x;
// 	int y;
// 	double i;
// 	double j;
// 	double count1;
// 	double count2;

// 	printf ("px_in_cell_height = %d\n", minimap.px_in_cell_height);
// 	y = 0;
// 	while (map.matrix[y])
// 	{
// 		x = 0;
// 		while (map.matrix[y][x])
// 		{
// 			if (map.matrix[y][x] == '1')
// 			{
// 				i = y * minimap.px_in_cell_height;
// 				count1 = 0;
// 				while (count1 < minimap.px_in_cell_height)
// 				{
// 					j = x * minimap.px_in_cell_width;
// 					count2 = 0;
// 					while (count2 < minimap.px_in_cell_width)
// 					{
// 						mlx_put_pixel(mlx.mini_image, j, i, SOFT_GREY);
// 						j++;
// 						count2++;
// 					}
// 					i++;
// 					count1++;
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	printf ("image %p, mini %p\n",mlx.image, mlx.mini_image);
// }

// void print_background (t_mlx mlx, t_minimap minimap)
// {

// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < minimap.px_height)
// 	{
// 		x = 0;
// 		while (x < minimap.px_width)
// 		{
// 			mlx_put_pixel(mlx.mini_image, x, y, DARK_GREY);
// 			x++;
// 		}
// 		y++;
// 	}

// }

// void print_player (t_game *gdata, t_player player, double x, double y, int color)
// {
// 	double x_limit;
// 	double y_limit;
// 	double draw_x;
// 	double draw_y;

// 	draw_y = -player.radius; // asi tengo el inicio del circulo en y
// 	y_limit = player.radius; // asi tengo el limite final del circulo en y
//     while (draw_y <= y_limit)
// 	{
// 		draw_x = -player.radius;
// 		x_limit = player.radius;
// 		while (draw_x <= x_limit)
// 		{
//             if (draw_x * draw_x + draw_y * draw_y <= player.radius * player.radius) // implementación directa de la definición de un círculo en coordenadas cartesianas
//                 mlx_put_pixel(gdata->mlx.mini_image, x + draw_x, y + draw_y, color); // al dibujar en la posicion draw relativa al centro del circulo, aseguramos que siempre se dibujara dentro del circulo.

//             draw_x++;
// 		}
// 		draw_y++;
// 	}	
// }


void print_player(t_game *gdata, t_player player, int x, int y)
{

    int draw_x;
    int draw_y;
   	int x_limit;
    int y_limit;

    draw_y = y - player.radius;
    x_limit = x + player.radius;
    y_limit = y + player.radius;
    while (draw_y <= y_limit) {
        draw_x = x - player.radius;
        while (draw_x <= x_limit) {
            if ((draw_x - x) * (draw_x - x) + (draw_y - y) * (draw_y - y) <= player.radius * player.radius) {
                mlx_put_pixel(gdata->mlx.mini_image, (int)draw_x, (int)draw_y, RED1);  // Color del jugador en el centro
            }
            draw_x++;
        }
        draw_y++;
    }
}

void	print_minimap(t_game *gdata)
{
	// coordenadas iniciales desde donde se deberá empezar a dibujar el minimapa en la matriz del mapa
	int start_x;
	int start_y;
	int matrix_cell_x;
	int matrix_cell_y;


	start_x = gdata->player.x - gdata->minimap.center_x;   // Establece la columna de pixels inicial para dibujar del minimapa, centrado en el jugador
	start_y = gdata->player.y - gdata->minimap.center_y;   // Establece la fila de pixels inicial para dibujar del minimapa, centrado en el jugador
	
//se usan para determinar dónde dibujar en el minimapa
	int pixel_x = 0;
    int pixel_y = 0;


// Dibuja cada pixel en el minimapa
    while (pixel_y < gdata->minimap.px_height) 
    {
    	pixel_x = 0;
        while (pixel_x < gdata->minimap.px_width) 
        {
            // Determina si el pixel actual está dentro de los límites del mapa
            if (start_x + pixel_x < 0 || start_y + pixel_y < 0 || start_x + pixel_x > gdata->minimap.px_in_cell_width * gdata->map.c_width || start_y + pixel_y > gdata->minimap.px_in_cell_height * gdata->map.c_height)
            	{
	                // Dibuja el patrón de ajedrez para espacios vacíos
		            if (((pixel_x / 4) % 2 == (pixel_y / 4) % 2)) 
		            	mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, BLACK);
		            else 
		                mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, MEDIUM_GREY);
	            }
            else
            {
            	//Calcula a que casilla de la matriz corresponde ese pixel
	            matrix_cell_x = (start_x + pixel_x) / gdata->minimap.px_in_cell_width;
	            matrix_cell_y = (start_y + pixel_y) / gdata->minimap.px_in_cell_height;
            	//printf ("estoy en una celda tipo |%c|\n", gdata->map.matrix[matrix_cell_y][matrix_cell_x]);
	            if (matrix_cell_x >= 0 && matrix_cell_x < gdata->map.c_width && matrix_cell_y >= 0 && matrix_cell_y < gdata->map.c_height) 
	            {
	                if (gdata->map.matrix[matrix_cell_y][matrix_cell_x] == '1') 
	                    mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, SOFT_GREY);
	                else if (gdata->map.matrix[matrix_cell_y][matrix_cell_x] == '0' || gdata->map.matrix[matrix_cell_y][matrix_cell_x] == 'N' || gdata->map.matrix[matrix_cell_y][matrix_cell_x] == 'S' || gdata->map.matrix[matrix_cell_y][matrix_cell_x] == 'W' || gdata->map.matrix[matrix_cell_y][matrix_cell_x] == 'E')
	                    mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, DARK_GREY);
		            else 
		            {
		                // Dibuja el patrón de ajedrez para espacios vacíos
			            if (((pixel_x / 4) % 2 == (pixel_y / 4) % 2)) 
			            	mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, BLACK);
			            else 
			                mlx_put_pixel(gdata->mlx.mini_image, pixel_x, pixel_y, MEDIUM_GREY);
		            }
	            } 
	        }

            pixel_x++;
        }

        pixel_y++;
    }



	// print_background (gdata->mlx, gdata->minimap); //CONFIRMAR si yo me paso esta info asi, no estoy mandando el puntero, por lo que si modifico algo en la estructura no se mantiene el cambio. aunque gdata sea puntero, lo que mando es algo nuevo, si quiero que sea puntero tendre que indicarlo concretamente para esa variable, aunque forme parte de gdata. 
	// print_walls (gdata->mlx, gdata->minimap, gdata->map);
	// print_empty_space (gdata->mlx, gdata->minimap, gdata->map);
	// 	//Estas dos se pueden fusionar, REVISAR
	calculate_and_print_fov_and_vision_angle (gdata); //meter dentro de printminimap, y luego en print player fov in motion llamar a print tablero o algo asi	
	print_player (gdata, gdata->player, gdata->minimap.center_x, gdata->minimap.center_y);
}
