/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:47:14 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/21 20:15:59 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_max_size(char *line, size_t max)
{
	size_t	size;

	size = ft_strlen(line) - 1;
	if (max < size)
		max = size;
	return (max);
}
/*hasta ahora esta funcion nos devuelve todo el mapa con R*/
char	*fill_void(char *line, t_map *map)
{
	(void)line;//lo dejamos por si la usamos a la hora de conseguir el mapa ok
	char	*cp_line;//linea en la que pondremos el resto de chars

	cp_line = malloc(sizeof(char *) * (map->line_size + 1));
	if (!cp_line)
		return (NULL);
	cp_line = ft_memset(cp_line, 'R', map->line_size);
	return (cp_line);
}

/* char	**copy_map(char **map, size_t height)
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
} */
