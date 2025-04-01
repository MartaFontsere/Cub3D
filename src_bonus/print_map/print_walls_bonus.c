/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 05:04:06 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:57:39 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	get_wall_column(t_game *gdata, t_ray *ray, double *wall_x)
{
	if (ray->line_crossing == 0)
		*wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_width;
	else
		*wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;
	*wall_x = *wall_x - floor(*wall_x);
}

void	get_texture_column(t_image *texture, double *wall_x, int *tex_x)
{
	*tex_x = (int)(*wall_x * texture->xpm->texture.width);
	if (*tex_x < 0)
		*tex_x = 0;
	if ((uint32_t) * tex_x >= texture->xpm->texture.width)
		*tex_x = texture->xpm->texture.width - 1;
}

void	get_texture_row(t_game *gdata, t_image *texture,
		double *tex_start_offset)
{
	*tex_start_offset = 0;
	if (gdata->print_map.wall_height > gdata->map.px_height)
		*tex_start_offset = ((gdata->print_map.wall_height
					- gdata->map.px_height) / 2.0)
			* ((double)texture->xpm->texture.height
				/ gdata->print_map.wall_height);
}

void	print_wall_column(t_game *gdata, int *row, int *column,
		t_image *texture)
{
	double	tex_y_ratio;
	int		tex_y;
	int		tex_x;

	tex_y_ratio = (double)texture->xpm->texture.height
		/ gdata->print_map.wall_height;
	tex_x = gdata->print_map.tex_x;
	while (*row <= gdata->print_map.draw_wall_end)
	{
		tex_y = (int)((*row - gdata->print_map.draw_wall_start) * tex_y_ratio
				+ gdata->print_map.tex_start_offset);
		if (tex_y < 0)
			tex_y = 0;
		if ((uint32_t)tex_y >= texture->xpm->texture.height)
			tex_y = texture->xpm->texture.height - 1;
		gdata->print_map.color = get_texture_pixel(texture, tex_x, tex_y);
		mlx_put_pixel(gdata->mlx.image, *column, *row, gdata->print_map.color);
		(*row)++;
	}
}

void print_door_column(t_game *gdata, int *row, int *column, t_image *texture, int tex_x, double tex_start_offset, double door_distance)
{
     double tex_y_ratio;
     int tex_y;
     int door_height;
     int draw_start;
     int draw_end;
 
     // 📌 La altura de la puerta debe calcularse con su propia distancia, no la de la pared
     door_height = gdata->map.px_height / door_distance;
 
     // 📌 Ajustar el punto donde empieza y termina la puerta en pantalla
     draw_start = (gdata->map.px_height / 2) - (door_height / 2);
     draw_end = (gdata->map.px_height / 2) + (door_height / 2);
 
     // 📌 Limitar valores dentro de la pantalla
     if (draw_start < 0)
         draw_start = 0;
     if (draw_end >= gdata->map.px_height)
         draw_end = gdata->map.px_height - 1;

     tex_y_ratio = (double)texture->xpm->texture.height / door_height;
 
     // 📌 Ajustamos `row` para comenzar en el punto correcto
     *row = draw_start;

      while (*row <= draw_end)
     {
         tex_y = (int)((*row - draw_start) * tex_y_ratio + tex_start_offset);
 
         if (tex_y < 0)
             tex_y = 0;
         if ((uint32_t)tex_y >= texture->xpm->texture.height)
             tex_y = texture->xpm->texture.height - 1;
 
         // 📌 Obtener el color de la textura de la puerta
         gdata->print_map.color = get_texture_pixel(texture, tex_x, tex_y);
 
         // 📌 Dibujar el píxel de la puerta con la altura correcta
         mlx_put_pixel(gdata->mlx.image, *column, *row, gdata->print_map.color);
         (*row)++;
    }

}

void print_door (t_game *gdata, t_ray *ray, int *row, int *column)
{
    double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
    int tex_x;

    double tex_start_offset;
    t_image *texture;
    double door_distance;  // 📌 Se necesita la distancia de la puerta
    // double door_perp_dist;
    // int door_height, door_draw_start, door_draw_end;
    // double door_recess;

// double distance = get_distance_to_door(gdata, ray->cell_collision_x, ray->cell_collision_y);
//     // 📌 Ratio de apertura (0 = cerrada, 1 = abierta completamente)
// double adjusted_distance = fmax(0.0, distance - DOOR_END_OPEN_DISTANCE); // No empieza a abrir hasta que estás a menos de 1.0
// double max_open_range = DOOR_START_OPEN_DISTANCE - DOOR_END_OPEN_DISTANCE;
//     double open_ratio = 1.0 - fmin(adjusted_distance /max_open_range, 1.0); // Completamente abierta cuando estás a 0.5 o menos





   // Usar la textura de la puerta
    texture = &gdata->texture.door_img;
    door_distance = ray->perpendicular_distance;
    // Calcular la posición exacta de impacto en la casilla (wall_x)
    get_wall_column(gdata, ray, &wall_x);
    // Convertir wall_x a coordenada en la textura
    get_texture_column(texture, &wall_x, &tex_x);
    // Calcular el offset vertical en la textura para centrar la imagen
    get_texture_row(gdata, texture, &tex_start_offset);
    // Imprimir la columna de la puerta (la altura será la misma que la pared)
    print_door_column(gdata, row, column, texture, tex_x, tex_start_offset, door_distance/*, open_ratio*/);
     
}

void	print_texture_walls(t_game *gdata, t_ray *ray, int *row, int *column)
{
	double	wall_x;
	t_image	*texture;

	if (gdata->map.matrix[ray->cell_collision_y][ray->cell_collision_x] == 'D' || gdata->map.matrix[ray->cell_collision_y][ray->cell_collision_x] == 'd')
        print_door (gdata, ray, row, column);
	
	texture = get_wall_texture(ray, gdata);
	get_wall_column(gdata, ray, &wall_x);
	get_texture_column(texture, &wall_x, &gdata->print_map.tex_x);
	get_texture_row(gdata, texture, &gdata->print_map.tex_start_offset);
	print_wall_column(gdata, row, column, texture);
}
