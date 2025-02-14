/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/14 18:40:14 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TEMPORAL
void	print_matrix(char **matrix, int flag)
{
	int	i = 0;

	while (*matrix && matrix[i])
	{
		if (flag == 1)
			printf(YELLOW"%s"END, matrix[i]);
		else if (flag == 2)
			printf(BLUE"%s"END, matrix[i]);
		else if (flag == 3)
			printf(ORANGE"%s"END, matrix[i]);
		i++;
	}
}
void	prints_check(t_map *map)
{
	printf(YELLOW"%s\n"END, map->path.NO);
	printf(YELLOW"%s\n"END, map->path.SO);
	printf(YELLOW"%s\n"END, map->path.WE);
	printf(YELLOW"%s\n"END, map->path.EA);
	//colors
	printf(RED"%d,"END, map->path.C.R);
	printf(GREEN"%d,"END, map->path.C.G);
	printf(BLUE"%d\n"END, map->path.C.B);
	printf(RED"[%d],"END, map->path.F.R);
	printf(GREEN"[%d],"END, map->path.F.G);
	printf(BLUE"[%d]\n"END, map->path.F.B);
	printf(ORANGE"m_h %zu\n"END, map->cells_height);
	printf(ORANGE"m_w %zu\n"END, map->cells_width);
	print_matrix(map->tmp_matrix, 1);
	printf("\n");
	print_matrix(map->matrix, 3);
	printf("\n");
}
//END TEMPORAL

void    init_structs(t_map *map)
{	
	map->rawmap = NULL;
    map->matrix = NULL;
    map->tmp_matrix = NULL;
	map->void_matrix = NULL;
	map->is_map = 0;
	map->cells_width = 0;
	map->cells_height = 0;
	map->j = 0;
	init_path(&map->path);
}

void	init_path(t_path *path)
{
	path->NO = NULL;
	path->SO = NULL;
	path->EA = NULL;
	path->WE = NULL;
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->C.R = 0;
	path->C.G = 0;
	path->C.B = 0;
	path->F.R = 0;
	path->F.G = 0;
	path->F.B = 0;
	path->C.path = path;
	path->F.path = path;
}

int main (int ac, char **av)
{
    t_map		map;
	
	init_structs(&map);
	if (!get_final_map(ac, av, &map))
	{
		clean_data(&map);
		return (0);
	}
	prints_check(&map);
	clean_data(&map);
    return (1);
}
