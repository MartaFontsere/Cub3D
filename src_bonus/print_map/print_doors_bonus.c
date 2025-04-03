/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:39:56 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/02 20:50:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
    
    texture = &gdata->texture.door_img;
    door_distance = ray->perpendicular_distance;
    // Calcular la posición exacta de impacto en la casilla (wall_x)
    get_column(gdata, ray, &wall_x);
    // Convertir wall_x a coordenada en la textura
    get_texture_column(texture, &wall_x, &tex_x);
    // Calcular el offset vertical en la textura para centrar la imagen
    get_texture_row(gdata, texture, &tex_start_offset);
    // Imprimir la columna de la puerta (la altura será la misma que la pared)
    print_door_column(gdata, row, column, texture, tex_x, tex_start_offset, door_distance/*, open_ratio*/);
     
}