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

	player.midle_x = x + (gdata->minimap.cell_width / 2);
	player.midle_y = y + (gdata->minimap.cell_height / 2);
	draw_y = -player.radius; // asi tengo el inicio del circulo en y
	y_limit = player.radius; // asi tengo el limite final del circulo en y
	
	while (draw_y <= y_limit)
	{
		draw_x = -player.radius;
		x_limit = player.radius;
		while (draw_x <= x_limit)
		{
            if (draw_x * draw_x + draw_y * draw_y <= player.radius * player.radius) // implementación directa de la definición de un círculo en coordenadas cartesianas
                mlx_put_pixel(gdata->mlx.image, player.midle_x + draw_x, player.midle_y + draw_y, color); // al dibujar en la posicion draw relativa al centro del circulo, aseguramos que siempre se dibujara dentro del circulo.
            draw_x++;
		}
		draw_y++;
	}	
}


void print_vision_angle (t_game *gdata, t_player player, double x, double y, int color) //TOTALMENTE HARDCODEADO
{
	int i; // Controla la longitud de la línea
	double init_x; // Coordenada inicial X para dibujar
	double init_y; // Coordenada inicial Y para dibujar
	int thickness; // Controla el grosor de la línea


	printf ("point of view es: |%f|\n", player.ray.vision_angle);
	i = 0;
	player.midle_x = x + (gdata->minimap.cell_width / 2);
	player.midle_y = y + (gdata->minimap.cell_height / 2);
	if (player.ray.vision_angle == NORTH)
	{
		init_x = player.midle_x;
		init_y = player.midle_y - player.radius; // Coordenada inicial (parte superior del círculo del jugador)
		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
		{
			init_x = player.midle_x - 1; // Comienza desde el centro menos la mitad del grosor
			thickness = 0; // se reinicia en cada iteración del bucle externo
			while (thickness < 2)
			{
				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
				thickness++;
				init_x++;
			}
			init_y--;
			i++;
		}
		printf ("punto de colision|%d||%d|\n", (int)(init_x / gdata->minimap.cell_height), (int)(init_y / gdata->minimap.cell_width));

	}

	else if (player.ray.vision_angle == SOUTH)
	{
		init_x = player.midle_x;
		init_y = player.midle_y + player.radius;
		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
		{
			init_x = player.midle_x - 1; // Comienza desde el centro menos la mitad del grosor
			thickness = 0; // se reinicia en cada iteración del bucle externo
			while (thickness < 2)
			{
				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
				thickness++;
				init_x++;
			}
			init_y++;
			i++;
		}
	}

	else if (player.ray.vision_angle == EAST)
	{
		init_x = player.midle_x + player.radius;
		init_y = player.midle_y;
		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
		{
			init_y = player.midle_y -1; // Comienza desde el centro menos la mitad del grosor
			thickness = 0; // se reinicia en cada iteración del bucle externo
			while (thickness < 2)
			{
				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
				thickness++;
				init_y++;
			}
			init_x++;
			i++;
		}
	}

	else if (player.ray.vision_angle == WEST)
	{
		init_x = player.midle_x - player.radius;
		init_y = player.midle_y;
		while (gdata->map.matrix[(int)(init_y / gdata->minimap.cell_width)][(int)(init_x / gdata->minimap.cell_height)] != '1')
		{
			init_y = player.midle_y +1;; // Comienza desde el centro menos la mitad del grosor
			thickness = 0; // se reinicia en cada iteración del bucle externo
			while (thickness < 2)
			{
				mlx_put_pixel(gdata->mlx.image, init_x, init_y, color);
				thickness++;
				init_y++;
			}
			init_x--;
			i++;
		}
	}
}