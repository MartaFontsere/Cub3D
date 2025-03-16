/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/14 12:47:13 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_game(void *param)
{
	t_game	*gdata;
	double	target_x;
	double	target_y;

	gdata = param;
	target_x = gdata->player.x;
	target_y = gdata->player.y;
	if (there_is_a_key_pressed(gdata))
	{
		if (gdata->player.rotate_right == 1 || gdata->player.rotate_left == 1)
			rotate_player(&gdata->player, &gdata->vision);
		if (gdata->player.mov_right == 1 || gdata->player.mov_left == 1
			|| gdata->player.mov_up == 1 || gdata->player.mov_down == 1)
			move_player(gdata, gdata->vision, &target_x, &target_y);
		calculate_fov(gdata, gdata->player.x, gdata->player.y);
		print_map(gdata, gdata->mlx, gdata->map);
		gdata->player.x = target_x;
		gdata->player.y = target_y;
	}
}
