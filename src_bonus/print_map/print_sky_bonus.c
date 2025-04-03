/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sky_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:54:17 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 11:47:15 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void print_sky_texture (t_game *gdata, t_ray *ray, int *row, int column)
{
	t_mlx mlx;

	mlx = gdata->mlx;
	// Obtener la textura del cielo --> el movimiento del cielo debe estar alineado con la dirección de la cámara del jugador, no con los ejes absolutos del mundo

	t_image *sky_texture = &gdata->texture.sky_img;
	// Obtener dimensiones de la textura
	int sky_tex_width = sky_texture->xpm->texture.width;
	int sky_tex_height = sky_texture->xpm->texture.height;

	// Calcular el desplazamiento horizontal del cielo (tex_x) basado solo en el ángulo de rotación
	double sky_offset_x = ray->current_angle / (2 * M_PI);  // Normalizar el ángulo a un valor entre 0 y 1
	sky_offset_x -= floor(sky_offset_x);  // Mantener solo la parte decimal --> Esto elimina la parte entera de sky_offset_x, asegurando que el valor siempre esté entre 0 y 1, sin importar cuántas vueltas haya dado el jugador
	// asi, hemos calculado el desplazamiento del cielo en función de la dirección y la posición del jugador


	// Ajustar el desplazamiento horizontal en función del movimiento lateral (gdata->player.x)
	double lateral_offset = gdata->player.x * 0.0005; // Ajuste pequeño en el eje X
	sky_offset_x += lateral_offset;
	sky_offset_x -= floor(sky_offset_x);  // Mantenerlo entre 0 y 1


	// Calcular posición inicial en la textura (tex_x)
	int tex_x_start = (int)(sky_offset_x * sky_tex_width);

	// Calcular el desplazamiento vertical del cielo (tex_y) basado solo en la posición vertical del jugador
	double vertical_offset = gdata->player.y * 0.0005;  // Ajuste pequeño en el eje Y

	*row = 0;
	while (*row < gdata->print_map.draw_wall_start)
	{
	    // Aplicar corrección de perspectiva con un pequeño ajuste por el movimiento en Y
	    double screen_y_ratio = (double)(*row - (mlx.window_height / 4)) / (mlx.window_height / 4);

	    // Calcular tex_y basado en la posición vertical y el desplazamiento vertical
	    int tex_y = (int)((0.5 + screen_y_ratio * 0.5 + vertical_offset) * sky_tex_height);

	    // Restringir tex_y a los límites de la textura (0 a sky_tex_height - 1)
	    if (tex_y < 0) 
	        tex_y = 0;  // No dejar que sea menor que 0
	    if (tex_y >= sky_tex_height) 
	        tex_y = sky_tex_height - 1;  // No dejar que supere el alto de la textura

	    // Obtener la parte correcta de la textura del cielo (tex_x)
	    int tex_x = (tex_x_start + column) % sky_tex_width;  // Hacer que la textura sea infinita

	    // Obtener el color de la textura y colocar el pixel en la imagen
	    int color = get_texture_pixel(sky_texture, tex_x, tex_y);
	    mlx_put_pixel(mlx.image, column, *row, color);
	    (*row)++;
	}
}

void print_sky_color (t_game *gdata, int *row, int column)
{
	t_mlx mlx;

	mlx = gdata->mlx;
	gdata->texture.C_hex_color = rgb_to_hex(gdata->texture.path.C.R,
			gdata->texture.path.C.G, gdata->texture.path.C.B);
	while (*row < gdata->print_map.draw_wall_start)
	{
		mlx_put_pixel(mlx.image, column, *row, gdata->texture.C_hex_color);
		(*row)++;
	}
}

void	print_sky(t_game *gdata, t_ray *ray, int *row, int column)
{

	if (!gdata->texture.path.F.is_path)
		print_sky_color (gdata, row, column);
	else
		print_sky_texture (gdata, ray, row, column);
}
