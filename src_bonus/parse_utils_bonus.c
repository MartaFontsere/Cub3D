/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:37:00 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/28 10:12:37 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_n_line(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	int		new_size;

	i = 0;
	new_size = map->c_height - 1;
	while (src[new_size])
	{
		j = 0;
		while (src[new_size][j] == '*')
			j++;
		if (j == map->c_width - 1)
			i++;
		else
			break ;
		new_size--;
	}
	if (i)
		map->c_height -= i;
}

int	check_esp(size_t x, size_t y, t_map *map)
{
	if (map->matrix[x][y] == '*')
	{
		if (x == map->c_height - 1)
		{
			if ((map->matrix[x][y + 1] != '*' && map->matrix[x][y + 1] != '1') \
			&& y != (map->c_width - 2))
				return (1);
		}
		else
		{
			if (((map->matrix[x][y + 1] != '*' && map->matrix[x][y + 1] != '1') \
			|| (map->matrix[x + 1][y] != '*' && map->matrix[x + 1][y] != '1')) \
			&& (y != map->c_width - 2))
			{
				msg_error("' ' must be followed by '1' or ' '\n", NULL);
				return (0);
			}
		}
	}
	return (1);
}

int	check_zero(size_t x, size_t y, t_map *map)
{
	if (map->matrix[x][y] == '0')
	{
		if ((map->matrix[x][y + 1] != map->pos \
		&& map->matrix[x][y + 1] != '0' && map->matrix[x][y + 1] != '1' \
		&& map->matrix[x][y + 1] != 'D')
		|| (map->matrix[x + 1][y] != map->pos \
		&& map->matrix[x + 1][y] != '0' && map->matrix[x + 1][y] != '1' \
		&& map->matrix[x + 1][y] != 'D'))
		{
			msg_error("'0' must be followed by '1', '0', Door or Player", "\n");
			return (0);
		}
	}
	return (1);
}

int	check_player(size_t x, size_t y, t_map *map)
{
	if (map->matrix[x][y] == map->pos)
	{
		if (x == 0 || x == map->c_height - 1 || y == 0 || y == map->c_width - 2)
		{
			msg_error("Player must be inside the map", "\n");
			return (0);
		}
		if ((map->matrix[x][y + 1] != '1' && map->matrix[x][y + 1] != '0' \
		&& map->matrix[x][y + 1] != 'D') || (map->matrix[x + 1][y] != '1' \
		&& map->matrix[x + 1][y] != '0' && map->matrix[x + 1][y] != 'D'))
		{
			msg_error("Player must be next to '1' or '0' or Door\n", NULL);
			return (0);
		}
	}
	return (1);
}
