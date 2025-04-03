/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:08:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 05:08:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void print_floor_texture(t_game *gdata, t_ray *ray, int row, int column)
{
    t_image *texture = &gdata->texture.floor_img;
    int tex_width = texture->xpm->texture.width;
    int tex_height = texture->xpm->texture.height;

    double view_angle_correction = cos(ray->current_angle - gdata->vision.vision_angle);
    double player_height = gdata->player.height;
    double proj_factor = gdata->vision.projection_factor;

    if (row <= gdata->print_map.draw_wall_end)
        row = gdata->print_map.draw_wall_end + 1;

    double scale = 12.0;  // Ajustá esto al gusto visual

    while (row < gdata->map.px_height)
    {
        double row_offset = row - (gdata->map.px_height / 2.0);
        if (row_offset <= 0)
        {
            row++;
            continue;
        }

        double distance = (player_height * proj_factor) / row_offset;
        distance /= view_angle_correction;

        // Calculamos coordenadas fijas del suelo en el mundo
        double floor_world_x = gdata->player.x + ray->dir_x * distance;
        double floor_world_y = gdata->player.y + ray->dir_y * distance;

        // Corregimos el mapeo para evitar que el suelo se deslice con el jugador
        double tex_unit_x = floor_world_x / (gdata->minimap.px_in_cell_width * scale);
        double tex_unit_y = floor_world_y / (gdata->minimap.px_in_cell_height * scale);

        double tex_u = tex_unit_x - floor(tex_unit_x);
        double tex_v = tex_unit_y - floor(tex_unit_y);

        if (tex_u < 0) tex_u += 1.0;
        if (tex_v < 0) tex_v += 1.0;

        int tex_x = (int)(tex_u * tex_width);
        int tex_y = (int)(tex_v * tex_height);

        if (tex_x >= tex_width) tex_x = tex_width - 1;
        if (tex_y >= tex_height) tex_y = tex_height - 1;

        int color = get_texture_pixel(texture, tex_x, tex_y);
        mlx_put_pixel(gdata->mlx.image, column, row, color);
        row++;
    }
}


void print_floor_color(t_game *gdata, int row, int column)
{
    t_mlx mlx;
    
    mlx = gdata->mlx;
    gdata->texture.F_hex_color = rgb_to_hex(gdata->texture.path.F.R,
            gdata->texture.path.F.G, gdata->texture.path.F.B);
            
    while (row < gdata->map.px_height)
    {
        mlx_put_pixel(mlx.image, column, row, gdata->texture.F_hex_color);
        row++;
    }
}

void print_floor(t_game *gdata, t_ray *ray, int row, int column)
{
    if (!gdata->texture.path.F.is_path)
        print_floor_color(gdata, row, column);
    else
        print_floor_texture(gdata, ray, row, column);
}



