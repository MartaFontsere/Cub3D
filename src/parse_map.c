/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/19 12:37:11 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_borders(char **matrix, int i, t_map *map)
{
	int j;
	size_t end;

	j = 0;
	//print_matrix(matrix, 2);
	end = map->cells_width - 2;
	if (ft_strchr(matrix[0], '0') || ft_strchr(matrix[map->cells_height - 1], '0'))
		return(msg_error("'0' is forbidden on border lines\n", NULL), 0);
	while (matrix[i][j] == '*')
		j++;
	if (matrix[i][j] == '0')
		return (msg_error("map must start with a wall\n", NULL), 0);
	while (matrix[i][end] == '*')
		end--;
	if (matrix[i][j] == '0' || matrix[i][end] == '0')
		return (msg_error("map must be closed\n", NULL), 0);
	return (1);
}

//Seran las posiciones anteriores del map, si estamos en la primera, no tenemos anterior
int	check_neg(int i, int j, t_map *map)
{
	if (!map->is_map && map->matrix[i][j - 1] != 1)
		return (msg_error("must be preceded by '1'", NULL), 0);
	if (map->matrix[i - 1][j] != 1)
		return (msg_error("must be close", NULL), 0);	
	return (1);
}
int	check_pos(int i, int j, t_map *map)
{
	if (!map->is_map && map->matrix[i][j - 1] != 1)
		return (msg_error("must be preceded by '1'", NULL), 0);
	//if (!map->is_map && map->matrix[i - 1][j] != 1)
	return (1);
}
//un 0 puede estar rodeado de 1 o 0 pero nunca de espacios, porque es mapa abierto
int	is_close(char **matrix, t_map *map)
{
	int	i;
	//int	j;
	
	i = 0;
	while (matrix[i])
	{
		if (!check_borders(matrix, i, map))
			return (0); 
		/* j = 0;
		while (j < map->cells_width)
		{
			if (matrix[i][j] == '0')
			{
				if (!check_neg(i, j, map) || !check_pos(i, j, map))
					return (0);
			}
			j++;
		} */
		i++;
	}
	return (1);
}
/*
	Para comprobar que el mapa este cerrado:
		->primero checkeamos los bordes: la primera y ultima linea no puede contener un '0'
		->si en la linea actual, tras un trim y r_trim de '*' encontramos un 0, el mapa es mal
		->los '*' no deben tener un 0 en ninguna de sus posiciones, porque seria mapa abierto



















*/




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
	if (!min_chars(matrix, 0))
		return (0);
	map->is_map = 0;
	//print_matrix(map->matrix, 1);
	if (!is_close(matrix, map))
		return (0);
	printf("MAP IS CORRECT!\n");
	return (1);
}
