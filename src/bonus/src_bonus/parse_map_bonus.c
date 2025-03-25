/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/21 13:28:16 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	print_dirs(char **matrix, int i, int j, int end)
{
	if (i != 0)
		printf(BLUE"   [%c]\n"END, matrix[i - 1][j]);
	if (j != 0)
		printf(BLUE"[%c]"END, matrix[i][j - 1]);
	printf(PURPLE"[%c]"END, matrix[i][j]);
	if (j != '\0')
		printf(BLUE"[%c]\n"END, matrix[i][j + 1]);
	if (i != end)
		printf(BLUE"   [%c]\n"END, matrix[i + 1][j]);
}

int	check_borders(char **matrix, int i, t_map *map)
{
	size_t	j;
	size_t	end;

	j = 0;
	end = map->c_width - 2;
	if (ft_strchr(matrix[0], '0') || ft_strchr(matrix[map->c_height - 1], '0'))
		return (msg_error("'0' is forbidden on border lines\n", NULL), 0);
	while (matrix[i][j] == '*' && j != end)
		j++;
	while (matrix[i][end] == '*' && end != 0)
		end--;
	if (end == 0 || j == map->c_width)
		return (1);
	else if (matrix[i][j] != '1' || matrix[i][end] != '1')
	{
		if (matrix[i][j] != '0')
			return (msg_error("Player must be inside map\n", NULL), 0);
		else if ( matrix[i][j] == 'D')
			return (msg_error("Door must be inside map\n", NULL), 0);
		return (msg_error("Map must be close with walls\n", NULL), 0);
	}
	return (1);
}

int	is_close(char **matrix, t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (matrix[map->c_height - 1][0] == '*')
		check_n_line(matrix, map);
	while (i < map->c_height)
	{
		if (!check_borders(matrix, i, map))
			return (0);
		j = 0;
		while (j < map->c_width)
		{
			if (matrix[i][j] == '1')
				;
			else if (!check_esp(i, j, map) || !check_zero(i, j, map))
				return (0);
			else if (!check_player(i, j, map) || !is_door(i, j, map))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	min_chars(char **map, int i)
{
	int	j;
	int	count;

	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' \
			&& map[i][j] != 'W' && map[i][j] != '1' && map[i][j] != '0' \
			&& map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '*' \
			&& map[i][j] != 'D')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
			|| map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (msg_error("Invalid number of players\n", NULL), 0);
	return (1);
}

int	parse_map(char **matrix, t_map *map)
{
	if (!min_chars(matrix, 0))
		return (0);
	map->is_map = 0;
	if (!is_close(matrix, map))
		return (0);
	printf("MAP IS GOOD ✅\n");
	return (1);
}
