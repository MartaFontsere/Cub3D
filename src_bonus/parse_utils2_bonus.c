/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:56:10 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/28 10:14:58 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_y_pos(int x, int y, t_map *map)
{
	if (map->matrix[x][y - 1] == '0')
	{
		if (map->matrix[x][y + 1] != '0' && map->matrix[x][y + 1] != map->pos)
			return (msg_error("Player must be able to move on Y", "\n"), 0);
		if (map->matrix[x - 1][y] != '1' || map->matrix[x + 1][y] != '1')
			return (msg_error("Door should be between walls on X\n", NULL), 0);
	}
	else if (map->matrix[x][y - 1] == map->pos)
	{
		if (map->matrix[x][y + 1] != '0')
			return (msg_error("A door does not have an exit\n", NULL), 0);
		if (map->matrix[x - 1][y] != '1' || map->matrix[x + 1][y] != '1')
			return (msg_error("Door should be between walls on X\n", NULL), 0);
	}
	return (1);
}

int	check_x_pos(int x, int y, t_map *map)
{
	if (map->matrix[x][y + 1] != '1')
		return (msg_error("Door should be between walls\n", NULL), 0);
	if (map->matrix[x - 1][y] != '0' && map->matrix[x - 1][y] != map->pos)
		return (msg_error("Player must be able to move on Y or X", "\n"), 0);
	if (map->matrix[x + 1][y] != '0' && map->matrix[x + 1][y] != map->pos)
		return (msg_error("Player must be able to move on X\n", NULL), 0);
	return (1);
}

int	is_door(size_t x, size_t y, t_map *map)
{
	if (map->matrix[x][y] == 'D')
	{
		if (x == 0 || x == map->c_height - 1 || y == 0 || y == map->c_width - 2)
			return (msg_error("Door never should be on borders", "\n"), 0);
		if (map->matrix[x][y - 1] == '0' || map->matrix[x][y - 1] == map->pos)
		{
			if (!check_y_pos(x, y, map))
				return (0);
		}
		else if (map->matrix[x][y - 1] == '1')
		{
			if (!check_x_pos(x, y, map))
				return (0);
		}
	}
	return (1);
}
