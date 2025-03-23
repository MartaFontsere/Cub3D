/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 22:40:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	check_collision(t_game *gdata, double target_x, double target_y)
// {
// 	int cell_x;
//     int cell_y;
//     double angle;
//     double angle_step;

//     angle = 0;
//     angle_step = M_PI / 36;

//     while (angle <= 2 * M_PI)
//     {
//         double contour_x = target_x + (gdata->player.radius - 2.5) * cos(angle);
//         double contour_y = target_y + (gdata->player.radius - 2.5) * sin(angle);
//          //mlx_put_pixel(gdata->mlx.image, contour_x, contour_y, YELLOW1);

//         cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
//         cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }

//     return 1;
// }


int check_collision_x(t_game *gdata, double target_x)
{
    int cell_x;
    int cell_y;
    double angle;
    double angle_step;

    angle = 0;
    angle_step = M_PI / 36;

    while (angle <= 2 * M_PI)
    {
        double contour_x = target_x + (gdata->player.radius) * cos(angle);
        double contour_y = gdata->player.y + (gdata->player.radius) * sin(angle);
         mlx_put_pixel(gdata->mlx.image, contour_x, contour_y, YELLOW1);
        cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
        cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);
        if (gdata->map.matrix[cell_y][cell_x] == '1')
            return 0; // Hay colisión en X
        angle += angle_step;
    }

    return 1; // No hay colisión en X

}

int check_collision_y(t_game *gdata, double target_y)
{
    int cell_x;
    int cell_y;
    double angle;
    double angle_step;

    angle = 0;
    angle_step = M_PI / 36;

    while (angle <= 2 * M_PI)
    {
        double contour_x = gdata->player.x + (gdata->player.radius) * cos(angle);
        double contour_y = target_y + (gdata->player.radius) * sin(angle);
         //mlx_put_pixel(gdata->mlx.image, contour_x, contour_y, YELLOW1);
         cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
         cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);
       if (gdata->map.matrix[cell_y][cell_x] == '1')
            return 0; // Hay colisión en X
        angle += angle_step;
    }

    return 1; // No hay colisión en X

}

// int check_collision_x(t_game *gdata, double target_x) {
//     int cell_x;
//     double contour_y = gdata->player.y;  // Usamos la posición actual Y del jugador

//     cell_x = (int)(target_x / gdata->minimap.px_in_cell_width);
//     if (gdata->map.matrix[(int)(contour_y / gdata->minimap.px_in_cell_height)][cell_x] == '1')
//         return 0; // Hay colisión en X

//     return 1; // No hay colisión en X
// }

// int check_collision_y(t_game *gdata, double target_y) {
//     int cell_y;
//     double contour_x = gdata->player.x;  // Usamos la posición actual X del jugador

//     cell_y = (int)(target_y / gdata->minimap.px_in_cell_height);
//     if (gdata->map.matrix[cell_y][(int)(contour_x / gdata->minimap.px_in_cell_width)] == '1')
//         return 0; // Hay colisión en Y

//     return 1; // No hay colisión en Y
// }

// int check_collision_x(t_game *gdata, double target_x)
// {
//     int cell_x, cell_y;
//     double angle = 0;
//     double angle_step = M_PI / 18;
//     double contour_x, contour_y;
//     double margin = 2.5; // Ajusta este valor según necesites

//     while (angle <= M_PI)
//     {
//         contour_x = target_x;
//         contour_y = gdata->player.y + (gdata->player.radius - margin) * cos(angle);

//         // Añade 0.0001 para evitar caer en la celda anterior por redondeo al truncar
//         double corrected_cx = contour_x + ((contour_x >= gdata->player.x) ? margin : -margin);
//         cell_x = (int)(corrected_cx / gdata->minimap.px_in_cell_width);
//         cell_y = (int)(contour_y / gdata->minimap.px_in_cell_height);

//         if (cell_x < 0 || cell_x >= gdata->map.c_width || cell_y < 0 || cell_y >= gdata->map.c_height)
//             return 0;

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }
//     return 1;
// }


// int check_collision_y(t_game *gdata, double target_y)
// {
//     int cell_x, cell_y;
//     double angle = 0;
//     double angle_step = M_PI / 18;
//     double contour_x, contour_y;
//     double margin = 2.5; // Ajusta este valor según necesites

//     while (angle <= M_PI)
//     {
//         contour_y = target_y;
//         contour_x = gdata->player.x + (gdata->player.radius - margin) * cos(angle);

//         double corrected_cy = contour_y + ((contour_y >= gdata->player.y) ? margin : -margin);
//         cell_x = (int)(contour_x / gdata->minimap.px_in_cell_width);
//         cell_y = (int)(corrected_cy / gdata->minimap.px_in_cell_height);

//         if (cell_x < 0 || cell_x >= gdata->map.c_width || cell_y < 0 || cell_y >= gdata->map.c_height)
//             return 0;

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }
//     return 1;
// }
