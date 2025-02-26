/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/26 13:54:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_structs(t_map *map)
{
	map->matrix = NULL;
	map->tmp_matrix = NULL;
	map->void_matrix = NULL;
	map->is_map = 0;
	map->c_width = 0;
	map->c_height = 0;
	map->j = 0;
	init_path(&map->path);
}

void	init_path(t_path *path)
{
	path->no = NULL;
	path->so = NULL;
	path->ea = NULL;
	path->we = NULL;
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->c.r = 0;
	path->c.g = 0;
	path->c.b = 0;
	path->c.path = path;
	path->c.assigned = 0;
	path->f.r = 0;
	path->f.g = 0;
	path->f.b = 0;
	path->f.path = path;
	path->f.assigned = 0;
}

int	main(int ac, char **av)
{
	t_map	map;

	init_structs(&map);
	if (!read_file(ac, av, &map))
	{
		clean_data(&map);
		return (0);
	}
	if (!parse_map(map.matrix, &map))
	{
		clean_data(&map);
		return (0);
	}
	clean_data(&map);
	return (1);
}
