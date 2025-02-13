/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/10 13:47:34 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//el exit me libera al salir, pero es mejor si yo tengo control sobre estas variables
void	exit_error(char *msg, int status)
{
	while (*msg)
		write(2, msg++, 1);
	exit(status);
}

void	msg_error(char *msg, char *msg2)
{
	write (2, RED, ft_strlen(RED));
	while (*msg)
		write(2, msg++, 1);
	write (2, END, ft_strlen(END));
	if (msg2)
	{
		write (2, BLUE, ft_strlen(BLUE));
		while (*msg2)
			write(2, msg2++, 1);
		//write(2, "\n", 1);
		write (2, END, ft_strlen(END));
	}
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

void	clean_shader(t_shader *shader)//deberia ser un free, no?
{
	free(shader->NO);
	free(shader->SO);
	free(shader->EA);
	free(shader->WE);
	//no hace falta volver a poner a 0
	shader->C.R = 0;
	shader->C.G = 0;
	shader->C.B = 0;
	shader->F.R = 0;
	shader->F.G = 0;
	shader->F.B = 0;
}

void	clean_data(t_map *map)
{
	clean_shader(&map->shader);
	free_matrix(map->matrix);
	if (map->tmp_matrix)
		free_matrix(map->tmp_matrix);
	if (map->rawmap)
		free(map->rawmap);
	map->rawmap = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->fd_path = NULL;
}
