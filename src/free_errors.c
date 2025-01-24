/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 18:32:05 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//libero al salir?
void	exit_error(char *msg, int status)
{
	while (*msg)
		write(2, msg++, 1);
	exit(status);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	clean_data(t_map *map)
{
	free_matrix(map->matrix);
	free_matrix(map->tmp_matrix);
	if (map->rawmap)
		free(map->rawmap);
	map->rawmap = NULL;
	map->heigth = 0;
    map->width = 0;
	map->line_size = 0;
	map->fd_lines = 0;
}
