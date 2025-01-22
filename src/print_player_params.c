/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/22 17:08:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_player (t_game *gdata, t_player player, int x, int y, int color)
{
	int x_limit;
	int y_limit;
	int draw_x;
	int draw_y;

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


print_point_of_view