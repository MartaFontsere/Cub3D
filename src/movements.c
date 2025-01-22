/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/22 16:19:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	print_player_move(t_game *gdata, t_player player, int target_x, int target_y)
{

	print_player (gdata, player, player.x, player.y, DARK_GREY);
	print_player (gdata, player, target_x, target_y, RED1);
}


void rotate (t_game *gdata)
{

}

// void	move_event(t_cub *cub, float new_x, float new_y)
// {
// 	if (mlx_is_key_down(cub->mlx, WKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle);
// 		new_y += MOVE_SPEED * sin(cub->player.angle);
// 	}
// 	if (mlx_is_key_down(cub->mlx, SKEY))
// 	{
// 		new_x -= MOVE_SPEED * cos(cub->player.angle);
// 		new_y -= MOVE_SPEED * sin(cub->player.angle);
// 	}
// 	if (mlx_is_key_down(cub->mlx, AKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle - M_PI_2);
// 		new_y += MOVE_SPEED * sin(cub->player.angle - M_PI_2);
// 	}
// 	if (mlx_is_key_down(cub->mlx, DKEY))
// 	{
// 		new_x += MOVE_SPEED * cos(cub->player.angle + M_PI_2);
// 		new_y += MOVE_SPEED * sin(cub->player.angle + M_PI_2);
// 	}

// void	rotate_event(t_cub *cub)
// {
// 	if (mlx_is_key_down(cub->mlx, LEFT))
// 		cub->player.angle -= ROTATE_SPEED;
// 	if (mlx_is_key_down(cub->mlx, RIGHT))
// 		cub->player.angle += ROTATE_SPEED;
// 	render(cub);
// }