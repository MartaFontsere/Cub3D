/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:57:05 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 02:09:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void    rotate_player(t_player *player, t_vision *vision)
{
    if (player->rotate_right == 1)
    {
        vision->vision_angle -= ROTATION_SPEED;
        if (vision->vision_angle > 2 * M_PI)
            vision->vision_angle -= 2 * M_PI;
    }
    else if (player->rotate_left == 1)
    {
        vision->vision_angle += ROTATION_SPEED;
        if (vision->vision_angle < 0)
            vision->vision_angle += 2 * M_PI;
    }
}
