/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ray_opened_door.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:42:21 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/27 23:13:14 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double prepare_opened_door_params (t_game *gdata, int map_x, int map_y)
{
	double distance_to_door;
	double adjusted_distance;
	double max_open_range;
	double open_ratio;

	distance_to_door = get_distance_to_door(gdata, map_x, map_y);
    adjusted_distance = fmax(0.0, distance_to_door - DOOR_END_OPEN_DISTANCE);
    max_open_range = DOOR_START_OPEN_DISTANCE - DOOR_END_OPEN_DISTANCE;
   	open_ratio = 1.0 - fmin(adjusted_distance / max_open_range, 1.0);
   	return (open_ratio);
}

double take_hit_door_position (t_ray *ray, t_game *gdata)
{
	double wall_x;

    if (ray->line_crossing == 0)
    {
        vertical_coords_convert (ray, gdata);
        wall_x = fmod(ray->px_collision_y, gdata->minimap.px_in_cell_height) / gdata->minimap.px_in_cell_height;
    
        // Invertimos solo si mira al ESTE
        if (ray->x_sign > 0)
            wall_x = 1.0 - wall_x;
    }
    else
    {
        horizontal_coords_convert (ray, gdata);
        wall_x = fmod(ray->px_collision_x, gdata->minimap.px_in_cell_width) / gdata->minimap.px_in_cell_width;
    
        // Invertir solo si mira al NORTE
        if (ray->y_sign < 0)
            wall_x = 1.0 - wall_x;
    }
    return (wall_x);
}


int convert_hit_position_to_text_coord (t_game *gdata, double wall_x, double open_ratio)
{
	int tex_width;
	int tex_x;
	int shift;
	int shifted_tex_x;

//Convertir a coordenada de textura
    tex_width = gdata->texture.door_img.xpm->texture.width;
    tex_x = (int)(wall_x * tex_width);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex_width) tex_x = tex_width - 1;
    //Simular apertura deslizante de derecha a izquierda
    shift = (int)(open_ratio * tex_width);
    shifted_tex_x = tex_x - shift;
    return (shifted_tex_x);
}


int should_block_ray(t_ray *ray, t_game *gdata, int map_x, int map_y)
{
	double open_ratio;
	double wall_x;
    int shifted_tex_x;

    //Calcular distancia jugador-puerta
    open_ratio = prepare_opened_door_params (gdata, map_x, map_y);

    // if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
    //     return 0; // Permitir paso (no bloquear), para evitar segfault CREO QUE NO HACE FALTA

    //Calcular wall_x (posición de colisión dentro de la celda)
    wall_x = take_hit_door_position (ray, gdata);
    
    shifted_tex_x = convert_hit_position_to_text_coord (gdata, wall_x, open_ratio);
    
    //Si shifted_tex_x >= 0 → todavía hay puerta visible ahí → BLOQUEAMOS el rayo
    //Si shifted_tex_x < 0 → esa parte ya está "abierta" → dejamos pasar el rayo
    return (shifted_tex_x >= 0);
}
