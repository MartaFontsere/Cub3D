/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 19:58:37 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



void print_empty_space (t_mlx mlx, t_minimap minimap, t_map map) //REVISAR EXPLICACION
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
				pixels_y = y * (minimap.px_height / map.c_height);
				pixels_count1 = 0;
				while (pixels_count1 < minimap.px_height / map.c_height)
				{
					pixels_x = x * minimap.px_width / map.c_width;
					pixels_count2 = 0;
					while (pixels_count2 < minimap.px_width / map.c_width)
					{
						color_flag = ((pixels_x / 7 + pixels_y / 7) % 2); // Al dividir entre 7 hago que se mantenga el mismo color 7 pixeles
						if (color_flag == 0)
                           	mlx_put_pixel(mlx.mini_image, pixels_x, pixels_y, BLACK);
                        else
                            mlx_put_pixel(mlx.mini_image, pixels_x, pixels_y, MEDIUM_GREY);

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

void print_walls (t_mlx mlx, t_minimap minimap, t_map map)
{
	int x;
	int y;
	double i;
	double j;
	double count1;
	double count2;

	printf ("px_in_cell_height = %d\n", minimap.px_in_cell_height);
	y = 0;
	while (map.matrix[y])
	{
		x = 0;
		while (map.matrix[y][x])
		{
			if (map.matrix[y][x] == '1')
			{
				i = y * minimap.px_in_cell_height;
				count1 = 0;
				while (count1 < minimap.px_in_cell_height)
				{
					j = x * minimap.px_in_cell_width;
					count2 = 0;
					while (count2 < minimap.px_in_cell_width)
					{
						mlx_put_pixel(mlx.mini_image, j, i, SOFT_GREY);
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
	printf ("image %p, mini %p\n",mlx.image, mlx.mini_image);
}

void print_background (t_mlx mlx, t_minimap minimap)
{

	int	x;
	int	y;

	y = 0;
	while (y < minimap.px_height)
	{
		x = 0;
		while (x < minimap.px_width)
		{
			mlx_put_pixel(mlx.mini_image, x, y, DARK_GREY);
			x++;
		}
		y++;
	}

}

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


void	print_minimap(t_game *gdata)
{
	print_background (gdata->mlx, gdata->minimap); //CONFIRMAR si yo me paso esta info asi, no estoy mandando el puntero, por lo que si modifico algo en la estructura no se mantiene el cambio. aunque gdata sea puntero, lo que mando es algo nuevo, si quiero que sea puntero tendre que indicarlo concretamente para esa variable, aunque forme parte de gdata. 
	print_walls (gdata->mlx, gdata->minimap, gdata->map);
	print_empty_space (gdata->mlx, gdata->minimap, gdata->map);
		//Estas dos se pueden fusionar, REVISAR
	calculate_and_print_fov_and_vision_angle (gdata); //meter dentro de printminimap, y luego en print player fov in motion llamar a print tablero o algo asi	
	print_player (gdata, gdata->player, gdata->player.x, gdata->player.y, RED1);
}
