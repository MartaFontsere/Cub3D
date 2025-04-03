/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:59:56 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 13:00:13 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void print_player(t_game *gdata, t_player player, int x, int y)
{

    int draw_x;
    int draw_y;
   	int x_limit;
    int y_limit;

    draw_y = y - player.radius;
    x_limit = x + player.radius;
    y_limit = y + player.radius;
    while (draw_y <= y_limit) {
        draw_x = x - player.radius;
        while (draw_x <= x_limit) {
            if ((draw_x - x) * (draw_x - x) + (draw_y - y) * (draw_y - y) <= player.radius * player.radius) {
                mlx_put_pixel(gdata->mlx.mini_image, (int)draw_x, (int)draw_y, RED1);  // Color del jugador en el centro
            }
            draw_x++;
        }
        draw_y++;
    }
}