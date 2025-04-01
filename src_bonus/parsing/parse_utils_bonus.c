/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:37:00 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/01 11:57:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_n_line(char **src, t_map *map)
{
	int	i;
	int	j;
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

int	check_esp(int i, int j, t_map *map)
{
	if (map->matrix[i][j] == '*')
	{
		if (i == map->c_height - 1)
		{
			if ((map->matrix[i][j + 1] != '*' && map->matrix[i][j + 1] != '1') \
			&& j != (map->c_width - 2))
				return (1);
		}
		else
		{
			if (((map->matrix[i][j + 1] != '*' && map->matrix[i][j + 1] != '1') \
			|| (map->matrix[i + 1][j] != '*' && map->matrix[i + 1][j] != '1')) \
			&& (j != map->c_width - 2))
			{
				msg_error("' ' must be followed by '1' or ' '\n", NULL);
				return (0);
			}
		}
	}
	return (1);
}

int	check_zero(int i, int j, t_map *map, t_player player)
{
	if (map->matrix[i][j] == '0')
	{
		if ((map->matrix[i][j + 1] != player.orientation \
		&& map->matrix[i][j + 1] != '0' && map->matrix[i][j + 1] != '1' \
		&& map->matrix[i][j + 1] != 'D')
		|| (map->matrix[i + 1][j] != player.orientation \
		&& map->matrix[i + 1][j] != '0' && map->matrix[i + 1][j] != '1' \
		&& map->matrix[i + 1][j] != 'D'))
		{
			msg_error("'0' must be followed by '1', '0', Door or Player", "\n");
			return (0);
		}
	}
	return (1);
}

int	check_player(int i, int j, t_map *map, t_player player)
{
	if (map->matrix[i][j] == player.orientation)
	{
		if (i == 0 || i == map->c_height - 1 || j == 0 || j == map->c_width - 2)
		{
			msg_error("Player must be inside the map", "\n");
			return (0);
		}
		if ((map->matrix[i][j + 1] != '1' && map->matrix[i][j + 1] != '0' \
		&& map->matrix[i][j + 1] != 'D') || (map->matrix[i + 1][j] != '1' \
		&& map->matrix[i + 1][j] != '0' && map->matrix[i + 1][j] != 'D'))
		{
			msg_error("Player must be next to '1' or '0' or Door\n", NULL);
			return (0);
		}
	}
	return (1);
}