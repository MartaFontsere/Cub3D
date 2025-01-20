/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/20 19:56:17 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_error(char *msg, int status)
{
	while (*msg)
		write(2, msg++, 1);
	exit(status);
}

void	free_matrix(t_map *map)
{
	int	i;

	i = 0;
	if (map->my_map == NULL)
		return ;
	while (map->my_map[i])
	{
		free(map->my_map[i]);
		i++;
	}
	free(map->my_map);
	map->my_map = NULL;
}

/* void	free_before_end(t_map *map)
{
	
} */