/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:16:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/27 17:12:49 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*fill_void(t_map *map)
{
	char	*cp_line;//linea en la que pondremos el resto de chars

	cp_line = malloc(sizeof(char *) * (map->map_width + 1));
	if (!cp_line)
		return (NULL);
	cp_line = ft_memset(cp_line, '*', map->map_width);
	return (cp_line);
}

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
int	mix_matrix(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		k = 0;
		while (src[i][j] && src[i][j] != '\n')
		{
			if (src[i][j] == '1' || src[i][j] == '0' || src[i][j] == 'N'\
			|| src[i][j] == 'S' || src[i][j] == 'E' || src[i][j] == 'W')
				map->tmp_matrix[i][k] = src[i][j];
			k++;
			j++;
		}
		i++;
	}
	map->tmp_matrix[i] = NULL;
	map->matrix = copy_map(map->tmp_matrix, map->map_height);
	if (!map->matrix)
		free_matrix(src);
	return (1);
}

int	complete_matrix(char **src, t_map *map)
{
	int		i;

	i = 0;
	map->map_height = count_fd_line(map->fd_path, map);
	map->tmp_matrix = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->tmp_matrix)
		return (0);
	while (src[i])
		map->tmp_matrix[i++] = fill_void(map);
	map->tmp_matrix[i] = NULL;
	mix_matrix(src, map);
	return (1);
}
