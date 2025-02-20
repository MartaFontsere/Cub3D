/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/20 13:37:35 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_borders(char **matrix, int i, t_map *map)
{
	int j;
	size_t end;

	j = 0;
	end = map->c_width - 1;
	if (ft_strchr(matrix[0], '0') || ft_strchr(matrix[map->c_height - 1], '0'))
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

/*
	-> Al hacer la lectura empieza controlando los bordes, para evitar un 0 abierto
	-> Si el char es un '*' vereficamos que el char comprobamos que los chars de sus 
	lados sean '*' o '1', de lo contrario, el mapa puede estar abierto
	-> Si el char es un '1', pasamos al siguiente, ya que no hace nada
	-> Si el char es NSWE, puede estar rodeado de '0' y '1'
	-> Si el char es un '0', puede estar rodeado de NSWE o '1'
*/


int	check_esp(char **mapa, size_t x, size_t y, t_map *map)
{
	if (x == 0)//solo miro positivos
	{
		if (y == 0 && mapa[x][y + 1] != '*' && mapa[x][y + 1] != '1' \
		&& mapa[x + 1][y] != '*' && mapa[x + 1][y] != '1')//char en pos 0,0
			return (0);
		else if (mapa[x][y + 1] != '*' && mapa[x][y + 1] != '1' \
		&& mapa[x][y - 1] != '*' && mapa[x][y - 1] != '1')
			return (0);
		else if (mapa[x + 1][y] != '*' && mapa[x + 1][y] != '1')
			return (0);
	}
	else if (x == map->c_height - 1)
	{
		if (mapa[x - 1][y] != '*' && mapa[x - 1][y] != '1')
			return (0);
	}
	else//si esta por medio mapa
	{
		if (mapa[x][y + 1] != '*' && mapa[x][y + 1] != '1' \
		&& mapa[x][y - 1] != '*' && mapa[x][y - 1] != '1')
			return (0);
		if ((mapa[x + 1][y] != '*' && mapa[x + 1][y] != '1') \
		|| (mapa[x - 1][y] != '*' && mapa[x - 1][y] != '1'))
			return (0);
		//printf("y-1: %c y+1: %c\n", mapa[x][y - 1], mapa[x][y + 1]);
		//printf("x-1: %c x+1: %c\n", mapa[x - 1][y], mapa[x + 1][y]);
	}
	return (1);
}
//nunca habra un 0 en los bordes, asi que checkeamos los del medio
int	check_zero(char **mapa, size_t x, size_t y, t_map *map)
{
	(void)map;
	if (mapa[x][y + 1] == '*' && mapa[x][y - 1] == '*' && mapa[x + 1][y] == '*' \
	&& mapa[x - 1][y] == '*')
		return (msg_error("'0' must be next to '1' or '0'", "\n"), 0);
	return (1);
}

int	is_close(char **matrix, t_map *map)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	print_matrix(matrix, 1);
	while (matrix[i])
	{
		if (!check_borders(matrix, i, map))
			return (0); 
		j = 0;
		while (j < map->c_width)
		{
			if (matrix[i][j] == '*')
			{
				if (!check_esp(matrix, i, j, map))
				{
					printf(BLUE"char: %c - pos x[%zu] - y[%zu]\n" , matrix[i][j], i, j);
					return (msg_error("' ' must be next to '1' or ' '", "\n"), 0);
				}
			}
			else if (matrix[i][j] == '0')
			{
				if (!check_zero(matrix, i, j, map))
					return (0);
			}
			else if (matrix[i][j] == 'N' || matrix[i][j] == 'S' \
			|| matrix[i][j] == 'W' || matrix[i][j] == 'E')
			{
				if (i == 0 || i == map->c_height - 1)//si esta al principio o final del mapa
					return(msg_error("Player must be inside the map", "\n"), 0);
				//if (!check_player(matrix, i, j, map))
				//	return (0);
			}
			j++;
		}
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
	return (1);
}
