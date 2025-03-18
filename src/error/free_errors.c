/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/18 12:42:16 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_error(char *msg, int status)
{
	while (*msg)
		ft_write(2, msg++, 1);
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

void	clean_path(t_path *path)
{
	free(path->NO);
	free(path->SO);
	free(path->EA);
	free(path->WE);
}

void	free_map_sprites(t_game *gdata, t_texture *texture)
{
	if (texture->north_wall_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->north_wall_img.data);
		mlx_delete_xpm42(texture->north_wall_img.xpm);
	}
	if (texture->south_wall_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->south_wall_img.data);
		mlx_delete_xpm42(texture->south_wall_img.xpm);
	}
	if (texture->west_wall_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->west_wall_img.data);
		mlx_delete_xpm42(texture->west_wall_img.xpm);
	}
	if (texture->east_wall_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->east_wall_img.data);
		mlx_delete_xpm42(texture->east_wall_img.xpm);
	}
}

void	clean_data(t_game *gdata)
{
	clean_path(&gdata->texture.path);
	free_matrix(gdata->map.matrix);
	free_matrix(gdata->map.tmp_matrix);
	free_matrix(gdata->map.void_matrix);
	if (gdata && gdata->vision.FOV.rays)
		free(gdata->vision.FOV.rays); //REVISAR
	free_map_sprites(gdata, &gdata->texture);
}
