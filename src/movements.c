/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/22 11:26:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	print_player_move(t_game *gdata, t_player player, int target_x, int target_y)
{

	print_player (gdata, player, player.x, player.y, DARK_GREY);
	print_player (gdata, player, target_x, target_y, RED1);
}

