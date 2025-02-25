/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/25 20:21:12 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	check_n_line(char **src, t_map *map);
void	print_dirs(char **matrix, int i, int j, int end);

int	check_borders(char **matrix, int i, t_map *map)
{
	size_t		j;
	size_t	end;

	j = 0;
	end = map->c_width - 2;
	if (ft_strchr(matrix[0], '0') || ft_strchr(matrix[map->c_height - 1], '0'))
		return (msg_error("'0' is forbidden on border lines\n", NULL), 0);
	while (matrix[i][j] == '*' && j != end)
		j++;
	while (matrix[i][end] == '*' && end != 0)
		end--;
	//printf("%c\n", matrix[i][end]);
	if (end == 0 || j == map->c_width)
	{
		printf("HERE\n");
		return (1);
	}
	else if (matrix[i][j] != '1' || matrix[i][end] != '1')
	{
		printf("\n%c\n", matrix[i][end]);//char que genera el error
		return(msg_error("Map must be close with walls\n", NULL), 0);
	}
	return (1);
}

int	check_esp(size_t x, size_t y, t_map *map)
{
	printf("esp\n");
	if (map->matrix[x][y] != '*' /* || (x == map->c_height - 1) */)//si x es la ultima line, significa que todo lo anterior esta bien
		return (1);
	//printf("[%c]\n", map->matrix[map->c_height][map->c_width - 2]);
	//printf("[%c]\n", map->matrix[map->c_height - 1][map->c_width - 2]);
	if (y != map->c_width - 2)//si el siguiente char en y es \0, ni caso
	{
		if ((map->matrix[x][y + 1] != '*' && map->matrix[x][y + 1] != '1') \
		|| (map->matrix[x + 1][y] != '*' && map->matrix[x + 1][y] != '1'))
		{
			print_dirs(map->matrix, x, y, map->c_width);
			msg_error("' ' must be followed by '1' or ' '\n", NULL)	;
			return (0);
		}
	}
	return (1);
}
int	check_zero(size_t x, size_t y, t_map *map)
{
	printf("borde\n");
	if (map->matrix[x][y] != '0'/*  && x == map->c_height - 1 */)
		return (1);
	//player
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
	return (1);
	
}
//si ha llegado aqui significa que no es 1,*,0
int	check_player(size_t x, size_t y, t_map *map)
{
	printf("play\n");
	//printf("\n%c\n", map->matrix[x][y]);//char que genera el error
	//printf("%zu - %zu\n", x, y);
	print_dirs(map->matrix, x, y, map->c_width);
	if (x == 0 || x == map->c_height - 1)
	{
		msg_error("Player must be inside the map2", "\n");
		return (0);
	}
	if ((map->matrix[x][y + 1] != '1' && map->matrix[x][y + 1] != '0'))
	{
		printf("hi");
	}
	return (1);
}

//el player esta por controlar, porque no me interesa ponerlo en los bordes
int is_close(char **matrix, t_map *map)
{
	size_t i;
	size_t j;

	i = 0;
	if (matrix[map->c_height - 1][0] == '*')//la primera pos de esta linea es un espacio
		check_n_line(matrix, map);
	while (i < map->c_height)
	{
		if (!check_borders(matrix, i, map))
			return (0);
		j = 0;
		while (j < map->c_width)
		{
			//print_dirs(matrix, i, j, map->c_width);
			if (matrix[i][j] == '1')
				printf("✅\n");
			else if (!check_esp(i, j, map))//✅
				return(0);
			else if (!check_zero(i, j, map))//✅
				return(0);
			else if(!check_player(i, j, map))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int min_chars(char **map, int i)
{
	int j;
	int count;

	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' \
			&& map[i][j] != 'W' && map[i][j] != '1' && map[i][j] != '0' \
			&& map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '*')
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

int parse_map(char **matrix, t_map *map)
{
	print_matrix(matrix, 2);
	if (!min_chars(matrix, 0))
		return (0);
	map->is_map = 0;
	if (!is_close(matrix, map))
		return (0);
	return (1);
}
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
		{
			//printf("aplica: %s\n", src[new_size]);
			i++;
		}
		else
		{
			//printf("no aplica: %s\n", src[new_size]);
			break ;
		}
		new_size--;
	}
	if (i)
		map->c_height -= i;
	printf("new_size: %zu\n", map->c_height);
}

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