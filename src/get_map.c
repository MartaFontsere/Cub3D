/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/20 13:20:58 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mix_matrix(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < map->c_height)
	{
		j = 0;
		k = 0;
		while (src[i][j] && src[i][j] != '\n')
		{//si  no es espacio, copia en esta nueva matriz
			if (src[i][j] == '1' || src[i][j] == '0' || src[i][j] == 'N'\
			|| src[i][j] == 'S' || src[i][j] == 'E' || src[i][j] == 'W')
				map->void_matrix[i][k] = src[i][j];
			k++;
			j++;
		}
		i++;
	}
	map->void_matrix[i] = NULL;
	map->matrix = copy_map(map->void_matrix, map->c_height);
	if (!map->matrix)
		free_matrix(src);
	return (1);
}

char	*fill_void(t_map *map)
{
	char	*cp_line;
	char	*new_line;
	
	cp_line = malloc(sizeof(char *) * (map->c_width));
	if (!cp_line)
		return (NULL);
	cp_line = ft_memset(cp_line, '*', map->c_width - 1);
	new_line = ft_strjoin(cp_line, "\n");
	free(cp_line);
	return (new_line);
}

int	get_final_map(char **src, t_map *map)
{
	int		i;

	i = 0;
	map->void_matrix = malloc(sizeof(char *) * (map->c_height + 1));
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
	mix_matrix(src, map);
	return (1);
}

