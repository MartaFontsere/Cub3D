/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/26 22:24:36 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

// Calcula TODOS los rayos del FOV y los almacena en t_fov
void calculate_fov(t_game *gdata, double x, double y) //Mandar las coordenadas del player (actuales)
{
    double start_angle = gdata->vision.vision_angle - (gdata->vision.FOV.fov_rad / 2);
    double end_angle = gdata->vision.vision_angle + (gdata->vision.FOV.fov_rad / 2);
    double angle_step = (end_angle - start_angle) / gdata->vision.FOV.num_rays; // = FOV/ancho pantalla
    
    gdata->player.cell_player_x =  x / gdata->minimap.px_in_cell_width; //posición en casillas del player
    gdata->player.cell_player_y =  y / gdata->minimap.px_in_cell_height;
   
    int i = 0; //indice de cada rayo
    gdata->vision.FOV.rays[i].current_angle = start_angle;
    while (i < gdata->vision.FOV.num_rays) 
    {
        calculate_ray(gdata, &gdata->vision.FOV.rays[i], x, y);
        gdata->vision.FOV.rays[i+1].current_angle = gdata->vision.FOV.rays[i].current_angle + angle_step;//current_angle = start_angle + (angle_step * i); // lo mismo que current angle = current angle + angle step
        i++;
    }
}
