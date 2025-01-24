/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:16:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 17:55:44 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*fill_void(t_map *map)
{
	char	*cp_line;//linea en la que pondremos el resto de chars

	cp_line = malloc(sizeof(char *) * (map->line_size + 1));
	if (!cp_line)
		return (NULL);
	cp_line = ft_memset(cp_line, 'R', map->line_size);
	return (cp_line);
}

int	complete_matrix(char **src, t_map *map)
{
	int		i;

	i = 0;
	map->fd_lines = count_fd_line(map->fd_path, map);
	map->tmp_matrix = malloc(sizeof(char *) * (map->fd_lines + 1));
	if (!map->tmp_matrix)
		return (0);
	while (src[i])
		map->tmp_matrix[i++] = fill_void(map);
	map->tmp_matrix[i] = NULL;
	return (1);
}