/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/13 23:18:20 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_error(char *msg, int status)
{
	while (*msg)
		ft_write(2, msg++, 1);
	exit(status);
}

void	msg_error(char *msg, char *msg2)
{
	ft_write (2, RED, ft_strlen(RED));
	while (*msg)
		ft_write(2, msg++, 1);
	ft_write (2, END, ft_strlen(END));
	if (msg2)
	{
		ft_write (2, BLUE, ft_strlen(BLUE));
		while (*msg2)
			ft_write(2, msg2++, 1);
		ft_write (2, END, ft_strlen(END));
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
	free(path->NO);
	free(path->SO);
	free(path->EA);
	free(path->WE);
}

void	clean_data(t_game *gdata)
{
	clean_path(&gdata->texture.path);
	free_matrix(gdata->map.matrix);
	free_matrix(gdata->map.tmp_matrix);
	free_matrix(gdata->map.void_matrix);
	free(gdata->vision.FOV.rays); //REVISAR
}
