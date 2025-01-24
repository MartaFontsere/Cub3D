/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/24 02:26:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//PENDIENTE
int	check_right_move(t_game *gdata, double target_y, double target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.cell_width - 1;
	
	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
			+ tsize_minus_one - gdata->player.radius) / gdata->minimap.cell_width)] == '1')
		return (0);
	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
			/ gdata->minimap.cell_height)][(int)((target_x + tsize_minus_one - gdata->player.radius)
		/ gdata->minimap.cell_width)] == '1')
		return (0);
	return (1);
}

int	check_left_move(t_game *gdata, double target_y, double target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.cell_width - 1;
	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
			+ gdata->player.radius) / gdata->minimap.cell_width)] == '1')
		return (0);
	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
			/ gdata->minimap.cell_height)][(int)((target_x + gdata->player.radius)
		/ gdata->minimap.cell_width)] == '1')
		return (0);
	return (1);
}

int	check_up_move(t_game *gdata, double target_y, double target_x)
{
	int	tsize_minus_one;
	printf ("cell_width |%f|\n", gdata->minimap.cell_width);
	printf ("radio player |%f|\n", gdata->player.radius);
	printf ("target x a checkear |%f|\n", target_x);
	printf ("target y a checkear |%f|\n", target_y);
	printf ("revision target x final: |%d|\n", (int)((target_x + gdata->player.radius) / gdata->minimap.cell_width));
	printf ("revision target y final: |%d|\n", (int)((target_y + gdata->player.radius) / gdata->minimap.cell_height));


	tsize_minus_one = gdata->minimap.cell_width - 1;
	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
			+ gdata->player.radius) / gdata->minimap.cell_width)] == '1')
		return (0);
	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
			+ tsize_minus_one - gdata->player.radius) / gdata->minimap.cell_width)] == '1')
		return (0);
	return (1);
}

int	check_down_move(t_game *gdata, double target_y, double target_x)
{
	int	tsize_minus_one;

	tsize_minus_one = gdata->minimap.cell_width - 1;
	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
			/ gdata->minimap.cell_height)][(int)((target_x + gdata->player.radius)
		/ gdata->minimap.cell_width)] == '1')
		return (0);
	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
			/ gdata->minimap.cell_height)][(int)((target_x + tsize_minus_one - gdata->player.radius)
		/ gdata->minimap.cell_width)] == '1')
		return (0);
	return (1);
}

int	can_i_move_to(t_game *gdata, double target_x, double target_y)
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