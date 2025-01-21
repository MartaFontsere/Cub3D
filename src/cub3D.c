/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/21 20:16:11 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    init_map_values(t_map *map)
{
    map->my_map = NULL;
	map->raw_map = NULL;
    map->heigth = 0;
    map->width = 0;
    map->nexit = 0;
	map->line_size = 0;
	map->fd_lines = 0;
}

int main (int ac, char **av)
{
    t_map   map;
	char	**final_map;

    if (ac != 2)
    {
        printf("Args Error\n"); //STDERR
        return (0);
    }
    init_map_values(&map);
    final_map = get_final_map(ac, av, &map);//PONERLO EN IF
	if (!final_map)
	{
		free_matrix(map.my_map);
        return (0);
	}
	free_matrix(map.my_map);
	free_matrix(final_map);//DEL
    //si hay errores, liberar las structs???
    //init_game (MARTA);
    return (0);
}
