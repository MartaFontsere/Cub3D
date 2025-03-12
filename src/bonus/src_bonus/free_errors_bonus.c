/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/26 16:58:51 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

void	clean_path(t_path *path)
{
	free(path->no);
	free(path->so);
	free(path->ea);
	free(path->we);
}

void	clean_data(t_map *map)
{
	clean_path(&map->path);
	free_matrix(map->matrix);
	free_matrix(map->tmp_matrix);
	free_matrix(map->void_matrix);
}
