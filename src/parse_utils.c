/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:37:00 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/26 12:40:28 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*siempre necesitamos tener +1 para simular el null en el c_height*/
void	check_n_line(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	int	new_size;

	i = 0;
	new_size = map->c_height - 1;
	//printf("curr_size: %d\n", new_size);
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
	printf("new_size: %zu\n", map->c_height);
}

int	check_esp(size_t x, size_t y, t_map *map)
{
	if (map->matrix[x][y] == '*')
	{
		if (x == map->c_height - 1)//last line
		{
			if ((map->matrix[x][y + 1] != '*' && map->matrix[x][y + 1] != '1') \
			&& y != (map->c_width - 2))
			{
				printf("is last line, nothing to check down!\n");
				return (1);
			}
		}
		else
		{
			if (((map->matrix[x][y + 1] != '*' && map->matrix[x][y + 1] != '1') \
			|| (map->matrix[x + 1][y] != '*' && map->matrix[x + 1][y] != '1')) \
			&& (y != map->c_width - 2))
			{
				print_dirs(map->matrix, x, y, map->c_width);
				msg_error("' ' must be followed by '1' or ' '\n", NULL)	;
				return (0);
			}
		}
	}
	return (1);
}
int	check_zero(size_t x, size_t y, t_map *map)
{
	//no miramos en x o y si son el ultimo char porque ya estan parseados en el borde
	if (map->matrix[x][y] == '0')
	{
		if ((map->matrix[x][y + 1] != 'N' && map->matrix[x][y + 1] != 'S' \
		&& map->matrix[x][y + 1] != 'W' && map->matrix[x][y + 1] != 'E' \
		&& map->matrix[x][y + 1] != '0' && map->matrix[x][y + 1] != '1')
		|| (map->matrix[x + 1][y] != 'N' && map->matrix[x + 1][y] != 'S' \
		&& map->matrix[x + 1][y] != 'W' && map->matrix[x + 1][y] != 'S' \
		&& map->matrix[x + 1][y] != '0' && map->matrix[x + 1][y] != '1'))
		{
			print_dirs(map->matrix, x, y, map->c_width);
			msg_error("'0' must be followed by '1', '0' or player\n", NULL)	;
			return (0);
		}
	}
	return (1);
	
}

int	check_player(size_t x, size_t y, t_map *map)
{
	if(map->matrix[x][y] == 'N' || map->matrix[x][y] == 'S' \
	|| map->matrix[x][y] == 'W' || map->matrix[x][y] == 'E')
	{
		if (x == 0 || x == map->c_height - 1 || y == 0 || y == map->c_width - 2)
		{
			msg_error("camera must be inside the map", "\n");
			return (0);
		}
		if ((map->matrix[x][y + 1] != '1' && map->matrix[x][y + 1] != '0') \
		|| (map->matrix[x + 1][y] != '1' && map->matrix[x + 1][y] != '0'))
		{
			msg_error("Player must be next to '1' or '0'\n", NULL);
			return(0);
		}
	}
	return (1);
}
