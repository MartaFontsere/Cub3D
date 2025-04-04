/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:56:10 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/04 14:54:32 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_y_pos(int i, int j, t_map *map)
{
	if (map->matrix[i][j - 1] == '0')
	{
		if (map->matrix[i][j + 1] != '0' && map->matrix[i][j + 1] != map->pos)
			return (msg_error("Player must be able to move on X", "\n"), 0);
		if (map->matrix[i - 1][j] != '1' || map->matrix[i + 1][j] != '1')
			return (msg_error("Door should be between walls on Y\n", NULL), 0);
	}
	else if (map->matrix[i][j - 1] == map->pos)
	{
		if (map->matrix[i][j + 1] != '0')
			return (msg_error("A door does not have an exit\n", NULL), 0);
		if (map->matrix[i - 1][j] != '1' || map->matrix[i + 1][j] != '1')
			return (msg_error("Door should be between walls on Y\n", NULL), 0);
	}
	return (1);
}

int	check_x_pos(int i, int j, t_map *map)
{
	if (map->matrix[i][j + 1] != '1')
		return (msg_error("Door should be between walls\n", NULL), 0);
	if (map->matrix[i - 1][j] != '0' && map->matrix[i - 1][j] != map->pos)
		return (msg_error("Player must be able to move on Y or X", "\n"), 0);
	if (map->matrix[i + 1][j] != '0' && map->matrix[i + 1][j] != map->pos)
		return (msg_error("Player must be able to move on Y\n", NULL), 0);
	return (1);
}

int	is_door(int i, int j, t_map *map)
{
	if (map->matrix[i][j] == 'D')
	{
		map->is_door = 1;
		if (i == 0 || i == map->c_height - 1 || j == 0 || j == map->c_width - 2)
			return (msg_error("Door never should be on borders", "\n"), 0);
		if (map->matrix[i][j - 1] == '0' || map->matrix[i][j - 1] == map->pos)
		{
			if (!check_y_pos(i, j, map))
				return (0);
		}
		else if (map->matrix[i][j - 1] == '1')
		{
			if (!check_x_pos(i, j, map))
				return (0);
		}
	}
	return (1);
}
