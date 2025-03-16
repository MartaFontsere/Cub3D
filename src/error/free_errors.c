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
	mlx_delete_image(gdata->mlx.init, texture->north_wall_img.data);
	mlx_delete_xpm42(texture->north_wall_img.xpm);
	mlx_delete_image(gdata->mlx.init, texture->south_wall_img.data);
	mlx_delete_xpm42(texture->south_wall_img.xpm);
	mlx_delete_image(gdata->mlx.init, texture->west_wall_img.data);
	mlx_delete_xpm42(texture->west_wall_img.xpm);
	mlx_delete_image(gdata->mlx.init, texture->east_wall_img.data);
	mlx_delete_xpm42(texture->east_wall_img.xpm);
}

void	clean_data(t_game *gdata)
{
	clean_path(&gdata->texture.path);
	free_matrix(gdata->map.matrix);
	free_matrix(gdata->map.tmp_matrix);
	free_matrix(gdata->map.void_matrix);
	free(gdata->vision.FOV.rays); //REVISAR
	free_map_sprites(gdata, &gdata->texture);
}
