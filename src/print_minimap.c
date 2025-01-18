/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/18 00:01:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_player (t_minimap minimap, t_player player)
{
	int x_limit;
	int y_limit;
	int draw_x;
	int draw_y;

	draw_y = -minimap.player_radius; // asi tengo el inicio del circulo en y
	y_limit = minimap.player_radius; // asi tengo el limite final del circulo en y
	
	while (draw_y <= y_limit)
	{
		draw_x = -minimap.player_radius;
		x_limit = minimap.player_radius;
		while (draw_x <= x_limit)
		{
            if (draw_x * draw_x + draw_y * draw_y <= minimap.player_radius * minimap.player_radius) // mplementación directa de la definición de un círculo en coordenadas cartesianas
                mlx_put_pixel(minimap.background_img, player.x + draw_x, player.y + draw_y, RED1); // al dibujar en la posicion draw relativa al centro del circulo, aseguramos que siempre se dibujara dentro del circulo.
            draw_x++;
		}
		draw_y++;
	}	
}


void print_empty_space (t_minimap minimap, t_map map) //REVISAR EXPLICACION
{
	int x;
	int y;
	int pixels_y;
	int pixels_x; //j
	int pixels_count1;
	int pixels_count2;
	int color_flag;

	y = 0;
	while (map.matrix[y])
	{
		x = 0;
		while (map.matrix[y][x])
		{
			if (map.matrix[y][x] == ' ')
			{
				printf ("he encontrado un 1\n");
				pixels_y = y * (minimap.height / map.height);
				pixels_count1 = 0;
				while (pixels_count1 < minimap.height / map.height)
				{
					pixels_x = x * minimap.width / map.width;
					pixels_count2 = 0;
					while (pixels_count2 < minimap.width / map.width)
					{
						color_flag = ((pixels_x / 7 + pixels_y / 7) % 2); // Al dividir entre 7 hago que se mantenga el mismo color 7 pixeles
						if (color_flag == 0)
                           	mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, BLACK);
                        else
                            mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, MEDIUM_GREY);

						pixels_x++;
						pixels_count2++;
					}
					pixels_y++;
					pixels_count1++;
				}
			}
			x++;
		}
		y++;
	}
}


//INTENTO DE DIAGONALES
// void print_empty_space (t_minimap minimap, t_map map) //ARREGLAR
// {
// 	int x;
// 	int y;
// 	int pixels_y;
// 	int pixels_x;
// 	int pixels_count1;
// 	int pixels_count2;


// 	int k;
// 	int color_flag;

	
// 	y = 0;
// 	while (map.matrix[y])
// 	{
// 		x = 0;
// 		while (map.matrix[y][x])
// 		{
// 			if (map.matrix[y][x] == ' ')
// 			{
// 				printf ("he encontrado un 1\n");
// 				pixels_y = y * (minimap.height / map.height);
// 				pixels_count1 = 0;
// 				//color_flag = 1;
// 				while (pixels_count1 < minimap.height / map.height)
// 				{
// 					pixels_x = x * minimap.width / map.width;
// 					pixels_count2 = 0;
// 					//color_flag++;
// 					while (pixels_count2 < minimap.width / map.width)
// 					{
// 						k = 0;

// 						while (pixels_count2 < minimap.width / map.width && k < 15)
// 						{
// 							//if (color_flag % 2 == 0)
// 								mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, MEDIUM_GREY2);
// 							//else
// 							//	mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, MEDIUM_GREY1);
// 							pixels_x++;
// 							pixels_count2++;
// 							k++;
// 						}
// 						while (pixels_count2 < minimap.width / map.width && k < 60)
// 						{
// 							//if (color_flag % 2 == 0)
// 								mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, MEDIUM_GREY1);
// 							//else
// 							//	mlx_put_pixel(minimap.background_img, pixels_x, pixels_y, MEDIUM_GREY2);
// 							pixels_x++;
// 							pixels_count2++;
// 							k++;
// 						}
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

void print_walls (t_minimap minimap, t_map map)
{
	int x;
	int y;
	int i;
	int j;
	int count1;
	int count2;

	printf ("entro 2\n");
	y = 0;
	while (map.matrix[y])
	{
		x = 0;
		while (map.matrix[y][x])
		{
			if (map.matrix[y][x] == '1')
			{
				printf ("he encontrado un 1\n");
				i = y * (minimap.height / map.height);
				count1 = 0;
				while (count1 < minimap.height / map.height)
				{
					j = x * minimap.width / map.width;
					count2 = 0;
					while (count2 < minimap.width / map.width)
					{
						mlx_put_pixel(minimap.background_img, j, i, SOFT_GREY);
						j++;
						count2++;
					}
					i++;
					count1++;
				}
			}
			x++;
		}
		y++;
	}
}

void print_background (t_minimap minimap)
{
	int	x;
	int	y;
	
	printf ("entro 1\n");
	y = 0;
	while (y < minimap.height)
	{
		x = 0;
		while (x < minimap.width)
		{
			mlx_put_pixel(minimap.background_img, x, y, DARK_GREY);
			x++;
		}
		y++;
	}

}

void	print_minimap(t_game *gdata)
{
	print_background (gdata->minimap); //CONFIRMAR si yo me paso esta info asi, no estoy mandando el puntero, por lo que si modifico algo en la estructura no se mantiene el cambio. aunque gdata sea puntero, lo que mando es algo nuevo, si quiero que sea puntero tendre que indicarlo concretamente para esa variable, aunque forme parte de gdata. 
	print_walls (gdata->minimap, gdata->map);
	print_empty_space (gdata->minimap, gdata->map);
		//Estas dos se pueden fusionar, REVISAR
	print_player (gdata->minimap, gdata->player);
	mlx_image_to_window(gdata->mlx.init, gdata->minimap.background_img, 0, 0);
}