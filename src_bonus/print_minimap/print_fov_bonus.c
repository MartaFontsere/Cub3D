/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fov_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 03:02:49 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 14:23:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"


int ray_is_out_of_map(t_game *gdata, t_ray *ray, double origin_x, double origin_y)
{
    int map_x = (int)((ray->draw.current_x - origin_x + gdata->player.x) / gdata->minimap.px_in_cell_width);
    int map_y = (int)((ray->draw.current_y - origin_y + gdata->player.y) / gdata->minimap.px_in_cell_height);

    if (map_x < 0 || map_x >= gdata->map.c_width ||
        map_y < 0 || map_y >= gdata->map.c_height)
        return 1;
    return 0;
}

void draw_ray_pixel(t_game *gdata, t_ray *ray, int current_step)
{
    int px_x = (int)(ray->draw.current_x + 0.5);
    int px_y = (int)(ray->draw.current_y + 0.5);

    if (px_x >= 0 && px_x < gdata->minimap.px_width &&
        px_y >= 0 && px_y < gdata->minimap.px_height)
    {
        if (current_step == (int)(ray->draw.steps - 1))
            mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, RED1);
        else
            mlx_put_pixel(gdata->mlx.mini_image, px_x, px_y, SOFT_YELLOW);
    }
}

void draw_ray(t_game *gdata, t_ray *ray, double origin_x, double origin_y)
{
    int current_step;

    ray->draw.x_distance = ray->px_collision_x - gdata->player.x;
    ray->draw.y_distance = ray->px_collision_y - gdata->player.y;
    ray->draw.steps = fmax(fabs(ray->draw.x_distance), fabs(ray->draw.y_distance));
    if (ray->draw.steps < 1e-6)
        return;
    ray->draw.x_inc = ray->draw.x_distance / ray->draw.steps;
    ray->draw.y_inc = ray->draw.y_distance / ray->draw.steps;
    ray->draw.current_x = origin_x;
    ray->draw.current_y = origin_y;
    current_step = 0;

    while (current_step < (int)ray->draw.steps)
    {
        draw_ray_pixel(gdata, ray, current_step);
        ray->draw.current_x += ray->draw.x_inc;
        ray->draw.current_y += ray->draw.y_inc;
        current_step++;
        if (ray_is_out_of_map(gdata, ray, origin_x, origin_y))
            break;
    }
}

void print_FOV(t_game *gdata, t_vision vision, double origin_x, double origin_y)
{
    int i = 0;

    while (i < vision.FOV.num_rays)
    {
        t_ray *ray = &vision.FOV.rays[i];
        draw_ray(gdata, ray, origin_x, origin_y);
        i++;
    }
}
