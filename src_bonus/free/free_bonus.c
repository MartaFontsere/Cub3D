/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/08 11:55:41 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (path->c.is_path)
		free(path->c.color_path);
	if (path->f.is_path)
		free(path->f.color_path);
}

void	clean_data(t_game *gdata)
{
	clean_path(&gdata->texture.path);
	free_matrix(gdata->map.matrix);
	free_matrix(gdata->map.tmp_matrix);
	free_matrix(gdata->map.void_matrix);
	if (gdata->vision.fov.rays)
		free(gdata->vision.fov.rays);
	free_walls_sprites(gdata, &gdata->texture);
	free_bonus_map_sprites(gdata, &gdata->texture);
	free_dragon_sprites(gdata, &gdata->texture);
	free_fire_sprites(gdata, &gdata->texture);
}
