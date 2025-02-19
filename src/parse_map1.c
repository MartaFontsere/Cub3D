/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/18 16:36:37 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//negatives
int	check_up(int i, int j, t_map *map)
{
	(void)j;
	(void)map;
	if (map->matrix[i] == 0)
	{
		printf("primera pos del array");
		return (1);
	}
	else//ya entra con la flag is map
	{
		if (map->matrix[i - 1][j] != '0' || map->matrix[i - 1][j] != '1')
			return (msg_error("map error ", "[2]"), 0);
	}
	return (1);
}


//la i sera + 1
//si el char de la siguiente line es * o 1, el mapa aun es valido
int	check_down(int i, int j, t_map *map)//positives
{
	if (map->matrix[i][j] == '0' && map->is_map == 0)
	{
		if (map->matrix[i - 1] != '1' && map->matrix[j - 1] != '1')
			map;
	}
	return (1);
	//return (msg_error("Map is not close\n", NULL), 0);
}

/*
	a medida que recorremos la line, si hay uno simplemente itero.
	Si encuentro un 0 fuera del mapa. Debo verificar que este este rodeado de 1
	Si encuentro un *	-> si esta fuera del mapa puede tener otro * a su al rededor
						-> si esta dentro del mapa, este debe estar rodeado de 1
*/
int	is_close(char **matrix, t_map *map)
{
	int i;
	int j;
	int start;
	int end;
	
	i = 0;
	while (matrix[i])
	{
		j = 0;
		if ((size_t)j < map->cells_width)//todo el rato estamos controlando el char actual
		{
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' \
			|| matrix[i][j] == 'W' || matrix[i][j] == 'E')//por ahora esto no checkea que este dentro del mapa
				j++;
			while (matrix[i][j] == '1')
			{
				map->is_map = 1;
				j++;
			}
			while (matrix[i][j] == '0')
			{
				if (!check_down(i, j, map) || !check_up(i, j, map))//check positive || negative
					return (0);
				j++;
			}
			if (matrix[i][j] != '1' && matrix[i][j] != '\0')
				return(msg_error("Open map\n", NULL), 0);
			while (matrix[i][j] == '*')
				j++;
		}
		i++;
	}
	printf("todo ok\n");
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
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'\
			&& map[i][j] != 'W' && map[i][j] != '1' && map[i][j] != '0'\
			&& map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '*')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'\
			|| map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return ( msg_error("Invalid number of players\n", NULL), 0);
	return (1);

}
int		parse_map(char **matrix, t_map *map)
{
	(void)map;
	if (!min_chars(matrix, 0))
		return (0);
	map->is_map = 0;
	print_matrix(map->matrix, 1);
	if (!is_close(matrix, map))
		return (0);
	printf("MAP IS CORRECT!\n");
	return (1);
}

