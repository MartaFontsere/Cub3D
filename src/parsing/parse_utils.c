/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:37:00 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/07 06:39:09 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_n_line(char **src, t_map *map)
{
	int	i;
	int	j;
	int	new_size;

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

int	check_zero(int i, int j, t_map *map)
{
	if (map->matrix[i][j] == '0')
	{
		if ((map->matrix[i][j + 1] != 'N' && map->matrix[i][j + 1] != 'S' \
		&& map->matrix[i][j + 1] != 'W' && map->matrix[i][j + 1] != 'E' \
		&& map->matrix[i][j + 1] != '0' && map->matrix[i][j + 1] != '1')
		|| (map->matrix[i + 1][j] != 'N' && map->matrix[i + 1][j] != 'S' \
		&& map->matrix[i + 1][j] != 'W' && map->matrix[i + 1][j] != 'E' \
		&& map->matrix[i + 1][j] != '0' && map->matrix[i + 1][j] != '1'))
		{
			msg_error("'0' must be followed by '1', '0' or player\n", NULL);
			return (0);
		}
	}
	return (1);
}

int	check_player(int i, int j, t_map *map)
{
	if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S' \
	|| map->matrix[i][j] == 'W' || map->matrix[i][j] == 'E')
	{
		if (i == 0 || i == map->c_height - 1 || j == 0 || j == map->c_width - 2)
		{
			msg_error("camera must be inside the map", "\n");
			return (0);
		}
		if ((map->matrix[i][j + 1] != '1' && map->matrix[i][j + 1] != '0') \
		|| (map->matrix[i + 1][j] != '1' && map->matrix[i + 1][j] != '0'))
		{
			msg_error("Player must be next to '1' or '0'\n", NULL);
			return (0);
		}
	}
	return (1);
}

// void	print_dirs(char **matrix, int i, int j, int end) //ESTOS PRINTF HAY QUE DEJARLOS????
// {
// 	if (i != 0)
// 		printf(BLUE"   [%c]\n"END, matrix[i - 1][j]);
// 	if (j != 0)
// 		printf(BLUE"[%c]"END, matrix[i][j - 1]);
// 	printf(PURPLE"[%c]"END, matrix[i][j]);
// 	if (j != '\0')
// 		printf(BLUE"[%c]\n"END, matrix[i][j + 1]);
// 	if (i != end)
// 		printf(BLUE"   [%c]\n"END, matrix[i + 1][j]);
// }
