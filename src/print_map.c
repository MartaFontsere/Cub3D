/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/13 04:35:05 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image *get_wall_texture(t_ray *ray, t_game *gdata)
{
    if (ray->line_crossing == 0)  // Pared vertical
    {
        if (ray->x_sign == 1)
            return &gdata->texture.north_wall_img;  // Norte
        else
            return &gdata->texture.south_wall_img;  // Sur
    }
    else  // Pared horizontal
    {
        if (ray->y_sign == 1)
            return &gdata->texture.east_wall_img;  // Este
        else
            return &gdata->texture.west_wall_img;  // Oeste
    }
}

int get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	 // Verificar si las coordenadas están fuera de los límites
    if (tex_x < 0 ||  (uint32_t)tex_x >= texture->xpm->texture.width ||
        tex_y < 0 || (uint32_t)tex_y >= texture->xpm->texture.height)
        return 0x000000;  // Negro si está fuera de los límites

    // Calcular el índice del píxel en la textura
    int index = (tex_y * texture->xpm->texture.width + tex_x) * 4;  // 4 bytes por píxel (RGBA)
    uint8_t *pixel = &texture->xpm->texture.pixels[index];

    // Obtener el color del píxel
    int color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
    return color;
}

void print_map (t_game *gdata, t_mlx mlx, t_map map)
{
	// int map.px_width = gdata->mlx.image->width;
    // int map.px_height = gdata->mlx.image->height;

 
    int x = 0; 
	while (x < gdata->vision.FOV.num_rays)
    {
    	// Obtener el rayo precalculado
        t_ray *ray = &gdata->vision.FOV.rays[x];

        // Calcular la altura de la pared en píxeles
        double wall_height = map.px_height / ray->perpendicular_distance;
// printf ("map.px_height %d\n", map.px_height);
// printf ("ray->perpendicular_distance %f\n", ray->perpendicular_distance);
         // Calcular los límites verticales de la pared
        int draw_wall_start = (map.px_height / 2) - (wall_height / 2);
        int draw_wall_end = (map.px_height / 2) + (wall_height / 2);

        //Limitar un valor dentro de un rango permitido
        //Si wall_height es muy grande, draw_wall_start podría volverse negativo, y draw_wall_end podría ser mayor que map.px_height, lo que haría que mlx_put_pixel() intentara acceder a píxeles fuera del rango de la imagen, causando el segfault
        //Aseguramos que draw_wall_start nunca sea menor que 0 y que draw_wall_end nunca sea mayor que map.px_height - 1
        if (draw_wall_start < 0) draw_wall_start = 0;
		if (draw_wall_end >= map.px_height) draw_wall_end = map.px_height - 1;

        // Dibujar el cielo
        int y = 0;
        while (y < draw_wall_start)
        {
            mlx_put_pixel(mlx.image, x, y, SKY_COLOR);
            y++;
        }

        // // Dibujar la pared
        // while (y <= draw_wall_end)
        // {
        //     //Determinar el color de la pared en función de la orientación
        //     int wall_color;
        //     if (ray->line_crossing == 0)
        //     {
        //         if (ray->x_sign == 1)
        //             wall_color = NORTH_WALL_COLOR;
        //         else
        //             wall_color = SOUTH_WALL_COLOR;
        //     }
        //     else
        //     {
        //         if (ray->y_sign == 1)
        //             wall_color = EAST_WALL_COLOR;
        //         else
        //             wall_color = WEST_WALL_COLOR;
        //     }
        //     mlx_put_pixel(mlx.image, x, y, wall_color);
        //     y++;
        // }


        
// Texturizar la pared
        t_image *texture = get_wall_texture(ray, gdata);  // Obtener la textura correcta
        texture->xpm->texture.width = 512;// HARDCODEADO
		texture->xpm->texture.height= 512;// HARDCODEADO
        // Calcular la coordenada horizontal en la textura (tex_x)
        double wall_x;  // Posición exacta donde el rayo golpea la pared
        if (ray->line_crossing == 0)  // Pared vertical
        {
            wall_x = ray->px_collision_y;  // Usar la coordenada y del punto de impacto
        }
        else  // Pared horizontal
        {
            wall_x = ray->px_collision_x;  // Usar la coordenada x del punto de impacto
        }
        wall_x -= floor(wall_x);  // Parte fraccional de la posición

        int tex_x = (int)(wall_x * texture->xpm->texture.width);  // Coordenada horizontal en la textura
        if (tex_x < 0) tex_x = 0;
        if ((uint32_t)tex_x >= texture->xpm->texture.width) tex_x = texture->xpm->texture.width - 1;

        // Dibujar la pared con textura
        double tex_y_ratio = (double)texture->xpm->texture.height / wall_height;
        while (y <= draw_wall_end)
        {
            // Calcular la coordenada vertical en la textura (tex_y)
            int tex_y = (int)((y - draw_wall_start) * tex_y_ratio);

            // Asegurar que tex_y esté dentro de los límites de la textura
            if (tex_y < 0) tex_y = 0;
            if ((uint32_t)tex_y >= texture->xpm->texture.height) tex_y = texture->xpm->texture.height - 1;

            // Obtener el color de la textura
            int color = get_texture_pixel(texture, tex_x, tex_y);

            // Dibujar el píxel en la pantalla
            mlx_put_pixel(mlx.image, x, y, color);
            y++;
        }


      

 

 

        // Dibujar el suelo
        while (y < map.px_height)
        {
            mlx_put_pixel(mlx.image, x, y, FLOOR_COLOR);
            y++;
        }

        x++;
    }



}