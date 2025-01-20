/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/20 20:10:41 by yanaranj         ###   ########.fr       */
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
}

int main (int ac, char **av)
{
    t_map   map;

    if (ac != 2)
    {
        printf("Args Error\n"); //STDERR
        return (0);
    }
    init_map_values(&map);
    if (get_final_map(ac, av, &map) == NULL)
	{
		//free_matrix(&map);
        return (0);
	}
	free_matrix(&map);
    //si hay errores, liberar las structs???
    //init_game (MARTA);
    return (0);
}
