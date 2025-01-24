/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 18:29:19 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TEMPORAL
void	print_matrix(char **matrix, int flag)
{
	int	i = 0;

	while (matrix[i])
	{
		if (flag == 1)
			printf(YELLOW"%s\n"END, matrix[i]);
		else
			printf(BLUE"%s\n"END, matrix[i]);
		i++;
	}
}

void    init_map_values(t_map *map)
{
    map->matrix = NULL;
    map->tmp_matrix = NULL;
	map->rawmap = NULL;
	map->fd_lines = 0;
    map->heigth = 0;
    map->width = 0;
	map->line_size = 0;
	map->fd_lines = 0;
}

int main (int ac, char **av)
{
    t_map   map;
	
	init_map_values(&map);
	if (!get_final_map(ac, av, &map))//de aqui sacamos map.matrix
	{
		printf("llego para liberar\n");
		clean_data(&map);
		return (1);
	}
	print_matrix(map.tmp_matrix, 1);
	clean_data(&map);
    return (1);
}
