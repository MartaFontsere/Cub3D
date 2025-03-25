/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray (copy).c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:22:08 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/19 16:15:14 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void check_horizontal_door(t_ray *ray, t_door door_ray, t_game *gdata);
{
	double door_midpoint;

	door_midpoint = 0;
	if (ray->line_crossing == 1)
    	update_door_horizontal_coords (door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, door_ray.line_crossing_tmp)
    else if (ray->line_crossing == 0)
    {
    	vertical_coords_convert (ray,gdata);
        if (ray->y_sign > 0)
        {

            door_midpoint = (*check_ray_y_in_map + 0.5) * gdata->minimap.px_in_cell_height;
            if (ray->px_collision_y > door_midpoint)
                update_door_vertical_coords (door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, 1);
        }
        else if (ray->y_sign < 0)
        {
            door_midpoint = (*check_ray_y_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_height;
            if (ray->px_collision_y < door_midpoint)
                 update_door_vertical_coords (door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, 1);
        }  
    }
}

void check_vertical_door(t_ray *ray, t_door door_ray, t_game *gdata);
{
	double door_midpoint;

	door_midpoint = 0;
	if (ray->line_crossing == 0)
    	update_door_vertical_coords (door_ray.first_dist_x_tmp, door_ray.check_ray_x_in_map_tmp, door_ray.line_crossing_tmp);

    else if (ray->line_crossing == 1)
    {
    	horizontal_coords_convert (ray, gdata);
    	if (ray->x_sign > 0)
        {
            door_midpoint = (*check_ray_x_in_map + 0.5) * gdata->minimap.px_in_cell_width;
            if (ray->px_collision_x > door_midpoint)
            	 update_door_horizontal_coords (door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, 0);
        }
        else if (ray->x_sign < 0)
        {
            door_midpoint = (*check_ray_x_in_map - 0.5 + 1) * gdata->minimap.px_in_cell_width;
            if (ray->px_collision_x < door_midpoint)
            	update_door_horizontal_coords (door_ray.first_dist_y_tmp, door_ray.check_ray_y_in_map_tmp, 0);
        }  
    }
}

void door_raycast (t_ray *ray, t_game *gdata,
		int *check_ray_x_in_map, int *check_ray_y_in_map)
{
	ray->door_ray.line_crossing_tmp = ray->line_crossing;
    ray->door_ray.check_ray_y_in_map_tmp = *check_ray_y_in_map;
    ray->door_ray.check_ray_x_in_map_tmp = *check_ray_x_in_map;
    ray->door_ray.first_dist_x_tmp = ray->first_dist_x;
    ray->door_ray.first_dist_y_tmp = ray->first_dist_y;
    check_matrix_lines (ray, check_ray_x_in_map, check_ray_y_in_map);
    if (line_crossing_tmp == 1)
    	check_horizontal_door(ray, ray->door_ray, gdata);
    if (line_crossing_tmp == 0)
    	check_vertical_door(ray, ray->door_ray, gdata);    
}

double prepare_opened_door_params (t_ray *ray, t_game *gdata, int map_x, int map_y)
{
	double distance_to_door;
	double adjusted_distance;
	double max_open_range;
	double open_ratio;

	distance_to_door = get_distance_to_door(gdata, map_x, map_y);
    adjusted_distance = fmax(0.0, distance - DOOR_END_OPEN_DISTANCE);
    max_open_range = DOOR_START_OPEN_DISTANCE - DOOR_END_OPEN_DISTANCE;
   	open_ratio = 1.0 - fmin(adjusted_distance / max_open_range, 1.0);
   	return (open_ratio);
}

double take_hit_door_position (t_ray *ray, t_game *gdata)
{
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
    return (shifted_tex_x)
}

int should_block_ray(t_ray *ray, t_game *gdata, int map_x, int map_y)
{
	double open_ratio;
	double wall_x;

    //Calcular distancia jugador-puerta
    open_ratio = prepare_opened_door_params (ray, gdata, map_x, map_y);

    // if (map_x < 0 || map_x >= gdata->map.c_width || map_y < 0 || map_y >= gdata->map.c_height)
    //     return 0; // Permitir paso (no bloquear), para evitar segfault CREO QUE NO HACE FALTA

    //Calcular wall_x (posición de colisión dentro de la celda)
    wall_x = take_hit_door_position (ray, gdata);
    
    shifted_tex_x = convert_hit_position_to_text_coord (gdata, wall_x, open_ratio);
    
    //Si shifted_tex_x >= 0 → todavía hay puerta visible ahí → BLOQUEAMOS el rayo
    //Si shifted_tex_x < 0 → esa parte ya está "abierta" → dejamos pasar el rayo
    return (shifted_tex_x >= 0);
}
