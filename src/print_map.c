/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/09 23:20:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


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

        // Dibujar la pared
        while (y <= draw_wall_end)
        {
            //Determinar el color de la pared en función de la orientación
            int wall_color;
            if (ray->line_crossing == 0)
            {
                if (ray->x_sign == 1)
                    wall_color = NORTH_WALL_COLOR;
                else
                    wall_color = SOUTH_WALL_COLOR;
            }
            else
            {
                if (ray->y_sign == 1)
                    wall_color = EAST_WALL_COLOR;
                else
                    wall_color = WEST_WALL_COLOR;
            }
            mlx_put_pixel(mlx.image, x, y, wall_color);
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

// void print_map (t_mlx mlx, t_map map)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	printf ("MAP width %d\n", map.px_width);
// 	printf ("MAP height %d\n", map.px_height);
	
// 	while (x < px_width)
// 	{
// 		y = 0;
// 		while (y < map.px_height)
// 		{
// 			while ()
// 		}

// 	}


// 	while (y < map.px_height)
// 	{
// 		x = 0;
// 		while (x < map.px_width)
// 		{
			

// 			mlx_put_pixel(mlx.image, x, y, BLUE1);
// 			x++;
// 		}
// 		y++;
// 	}
// }