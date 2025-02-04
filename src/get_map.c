/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/04 14:21:10 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_map(char *line, t_map *map, int i)
{
	int	j;
	
	map->is_map = 1;
	if 	(line[i] == 0)
	{
		map->shader.err_flag = 1;
		return (msg_error("The map is not closed\n", NULL));
	}
	j = 0;
	map->tmp_matrix[j++] = ft_strdup(line);
	map->tmp_matrix[j]  = NULL;
}

int	get_final_map(int ac, t_map *map)
{
	//int	counter = map->shader.colors_count + map->shader.count;

	
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	if (!fd_is_correct(map) || map->shader.count != 4)
	{
		if (map->shader.count != 4 && map->shader.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		clean_data(map);
		map->fd_path = NULL;
		return (0);
	}
	return (1);
}
