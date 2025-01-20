/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/20 19:39:03 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//PENDIENTE
int	check_right_move(t_game *gdata, int target_y, int target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.width - 1;
	
	if (gdata->map.matrix[(target_y + gdata->player.collision_size) / gdata->minimap.height][(target_x
			+ tsize_minus_one - gdata->player.collision_size) / gdata->minimap.width] == '1')
		return (0);
	if (gdata->map.matrix[(target_y + tsize_minus_one - gdata->player.collision_size)
			/ gdata->minimap.height][(target_x + tsize_minus_one - gdata->player.collision_size)
		/ gdata->minimap.width] == '1')
		return (0);
	return (1);
}

int	check_left_move(t_game *gdata, int target_y, int target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.width - 1;
	if (gdata->map.matrix[(target_y + gdata->player.collision_size) / gdata->minimap.height][(target_x
			+ gdata->player.collision_size) / gdata->minimap.width] == '1')
		return (0);
	if (gdata->map.matrix[(target_y + tsize_minus_one - gdata->player.collision_size)
			/ gdata->minimap.height][(target_x + gdata->player.collision_size)
		/ gdata->minimap.width] == '1')
		return (0);
	return (1);
}

int	check_up_move(t_game *gdata, int target_y, int target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.width - 1;
	if (gdata->map.matrix[(target_y + gdata->player.collision_size) / gdata->minimap.height][(target_x
			+ gdata->player.collision_size) / gdata->minimap.width] == '1')
		return (0);
	if (gdata->map.matrix[(target_y + gdata->player.collision_size) / gdata->minimap.height][(target_x
			+ tsize_minus_one - gdata->player.collision_size) / gdata->minimap.width] == '1')
		return (0);
	return (1);
}

int	check_down_move(t_game *gdata, int target_y, int target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.width - 1;
	if (gdata->map.matrix[(target_y + tsize_minus_one - gdata->player.collision_size)
			/ gdata->minimap.height][(target_x + gdata->player.collision_size)
		/ gdata->minimap.width] == '1')
		return (0);
	if (gdata->map.matrix[(target_y + tsize_minus_one - gdata->player.collision_size)
			/ gdata->minimap.height][(target_x + tsize_minus_one - gdata->player.collision_size)
		/ gdata->minimap.width] == '1')
		return (0);
	return (1);
}

int	can_i_move_to(t_game *gdata, int target_x, int target_y)
{
	if (gdata->player.mov_right == 1)
	{
		if (check_right_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_left == 1)
	{
		if (check_left_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_up == 1)
	{
		if (check_up_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_down == 1)
	{
		if (check_down_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	return (1);
}