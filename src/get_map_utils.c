/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/13 22:39:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_name(char *map_path)
{
	int	len;

	len = ft_strlen(map_path);
	if (ft_strncmp(map_path + len - 4, ".cub", 4) != 0)
	{
		printf("Invalid name map\n");
		return (0);
	}
	return (1);
}

size_t	ft_max_size(char *line, size_t max)
{
	size_t	size;
	int		flag;

	size = 0;
	flag = 0;
	while (line[size])
	{
		if (line[size] == '\t')
			flag = 1;
		size++;
	}
	if (flag == 1)
		size += 4;
	size -= 1;//me quita el null final
	if (max < size)
		max = size;
	printf("MAX: %zu\n", max);
	return (max);
}

/* char	**copy_map(char *line, t_map *map)
{
	char	**map_tmp;
	size_t	i;

	i = 0;
	map_tmp = malloc(sizeof(char*) * (map->cells_height + 1));
	if (!map_tmp)
		return (NULL);
	while (i < map->cells_height)
	{
		map_tmp[i] = ft_strdup(line);
		if (!map_tmp[i])
			return (free_matrix(map_tmp), NULL);
		i++;
	}
	map_tmp[i] = NULL;
	return (map_tmp);
} */

char	**copy_map(char **map, size_t height)
{
	char	**map_tmp;
	size_t	i;

	i = 0;
	map_tmp = malloc(sizeof(char*) * (height + 1));
	if (!map_tmp)
		return (NULL);
	while (i < height)
	{
		map_tmp[i] = ft_strdup(map[i]);
		if (!map_tmp[i])
			return (free_matrix(map_tmp), NULL);
		i++;
	}
	map_tmp[i] = NULL;
	return (map_tmp);
}

//las tabulaciones no las esta detectando correctamente
int	mix_matrix(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < map->cells_height)
	{
		j = 0;
		k = 0;
		while (src[i][j] && src[i][j] != '\n')
		{
			if (src[i][j] == '1' || src[i][j] == '0' || src[i][j] == 'N'\
			|| src[i][j] == 'S' || src[i][j] == 'E' || src[i][j] == 'W')
				map->void_matrix[i][k] = src[i][j];
			k++;
			j++;
		}
		i++;
	}
	map->void_matrix[i] = NULL;
	map->matrix = copy_map(map->void_matrix, map->cells_height);
	if (!map->matrix)
		free_matrix(src);
	return (1);
}

char	*fill_void(t_map *map)
{
	char	*cp_line;
	char	*new_line;
	
	cp_line = malloc(sizeof(char *) * (map->cells_width + 1));
	if (!cp_line)
		return (NULL);
	cp_line = ft_memset(cp_line, '*', map->cells_width - 1);
	new_line = ft_strjoin(cp_line, "\n");
	free(cp_line);
	return (new_line);
}

int	complete_matrix(char **src, t_map *map)
{
	int		i;

	i = 0;
	map->void_matrix = malloc(sizeof(char *) * (map->cells_height + 1));
	if (!map->void_matrix)
		return (msg_error("Error allocating memory\n", NULL) ,0);
	while (src[i])
	{
		map->void_matrix[i] = fill_void(map);
		if (!map->void_matrix[i])
			return (0);
		i++;
	}
	map->void_matrix[i] = NULL;
	print_matrix(map->void_matrix, 2);
	printf("\n");
	mix_matrix(src, map);
	return (1);
}
