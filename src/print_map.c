/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/13 22:57:39 by mfontser         ###   ########.fr       */
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
    if (tex_x < 0 || (uint32_t)tex_x >= texture->xpm->texture.width ||
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
        double wall_height = map.px_height / ray->perpendicular_distance; // altura total de la pantalla / distancia del jugador a la pared perpendiclarmente (para evitar ojo de pez). A menor distancia, la pared será más alta; a mayor distancia, la pared será más baja
// printf ("map.px_height %d\n", map.px_height);
// printf ("ray->perpendicular_distance %f\n", ray->perpendicular_distance);

         // Calcular los límites verticales de la pared
        int draw_wall_start = (map.px_height / 2) - (wall_height / 2);
        int draw_wall_end = (map.px_height / 2) + (wall_height / 2);

        //Limitar un valor dentro de un rango permitido
        //Si wall_height es muy grande, draw_wall_start podría volverse negativo, y draw_wall_end podría ser mayor que map.px_height, lo que haría que mlx_put_pixel() intentara acceder a píxeles fuera del rango de la imagen, causando el segfault
        //Aseguramos que draw_wall_start nunca sea menor que 0 y que draw_wall_end nunca sea mayor que map.px_height - 1
        if (draw_wall_start < 0) 
        {
        	draw_wall_start = 0;
        }

		if (draw_wall_end >= map.px_height) 
		{
			draw_wall_end = map.px_height - 1;
		}

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
        t_image *texture = get_wall_texture(ray, gdata);  // Obtener la textura correcta segun si el rayo impacta en una pared norte, sur, este u oeste, ya que la textura debe ser diferente.
        
        // Calcular la coordenada horizontal en la textura (tex_x)
        double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
        if (ray->line_crossing == 0)  // Pared vertical
        {
            wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_height;  // Usar la coordenada Y del punto de impacto. Osea miro en que pixel colisiona del eje Y y luego lo divido por el tamaño en pixeles de una casilla en el minimapa (representacion 2d) para saber en que parte de esa casilla esta colisionando. Ej: si colisiona en la casilla 4,75, significa que dentro de la casilla 4 choca en el 75% de esa casilla (entendiendo una casilla como el 100%). Nos quedamos solo con ese 75, porque indica que parte de la textura debemos pintar, me da igual el numero de la casilla
        	//printf ("casilla de colision para textura |%f|\n", wall_x);
        }
        else  // Pared horizontal
        {
            wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;  // Usar la coordenada X del punto de impacto. esa coordenada corresponde a la columna en el eje x de la textura que debera pintarse
        	//printf ("casilla de colision para textura |%f|\n", wall_x);
        }
        
        wall_x = wall_x - floor(wall_x);  // Parte fraccional de la posición dentro de la casilla --> Elimina la parte entera de wall_x y se queda solo con la fracción decimal. Queremos saber dentro de la casilla en qué punto impacta el rayo. Por ejemplo, si wall_x = 4.75, significa que el rayo impactó en la casilla 4, pero dentro de esa casilla impactó en el 75% de su ancho. Nos quedamos solo con 0.75

        //Convertir la coordenada de wall_x en una coordenada en píxeles dentro de la textura --> Las texturas tienen un ancho fijo, por lo que si wall_x = 0.75 y la textura tiene 64 píxeles de ancho, entonces el rayo impactó en el píxel 48 de la textura.
        int tex_x = (int)(wall_x * texture->xpm->texture.width);  // Coordenada horizontal en la textura
        
        // Asegurar que tex_x esté dentro de los límites --> Si tex_x es menor que 0 o mayor que texture->width, intentar acceder a esos valores podría causar un segfault. Esto podria pasar por errores de redondeo y precision, y si pasa como mucho se repetira la primera o la ultima columna de la textura. Cuando estás muy cerca de la pared, el control de tex_x prácticamente nunca será un problema, porque solo estarás viendo una pequeña porción de la textura, y esa porción siempre estará dentro de los límites de la textura
        if (tex_x < 0) 
        	tex_x = 0;
        if ((uint32_t)tex_x >= texture->xpm->texture.width) 
        {
        	tex_x = texture->xpm->texture.width - 1;
        }

        // Calcular cuánto de la textura debería saltarse si la pared es más grande que la pantalla --> Si la pared proyectada (wall_height) es más alta que la ventana (map.px_height), entonces parte de la textura debería "recortarse" para que solo se muestre el fragmento visible
		double tex_start_offset = 0; // tex_start_offset calcula cuántos píxeles de la textura hay que saltarse para centrar correctamente la imagen en pantalla.
		if (wall_height > map.px_height)
		{
		    tex_start_offset = ((wall_height - map.px_height) / 2.0) * ((double)texture->xpm->texture.height / wall_height);
		}

        // Dibujar la pared con textura correctamente alineada
        double tex_y_ratio = (double)texture->xpm->texture.height / wall_height;
        while (y <= draw_wall_end)
        {
            // Calcular la coordenada vertical en la textura (tex_y) ajustando el punto de inicio
            int tex_y = (int)((y - draw_wall_start) * tex_y_ratio + tex_start_offset);

            // Asegurar que tex_y esté dentro de los límites de la textura (Clamping de tex_y)
            if (tex_y < 0) 
            	tex_y = 0;
            if ((uint32_t)tex_y >= texture->xpm->texture.height) 
            	tex_y = texture->xpm->texture.height - 1;

            // Obtener el color del píxel de la textura
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