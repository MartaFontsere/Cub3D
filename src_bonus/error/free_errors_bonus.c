/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (texture->sky_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->sky_img.data);
		mlx_delete_xpm42(texture->sky_img.xpm);
	}
	if (texture->floor_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->floor_img.data);
		mlx_delete_xpm42(texture->floor_img.xpm);
	}
	if (texture->door_img.data)
	{
		mlx_delete_image(gdata->mlx.init, texture->door_img.data);
		mlx_delete_xpm42(texture->door_img.xpm);
	}
}

void	free_dragon_sprites(t_game *gdata, t_texture *texture)
{
	int i;

	i = 0;
	if (texture->dragon_img[0].data)
	{
		while (i < 4)
		{
			mlx_delete_image(gdata->mlx.init, texture->dragon_img[i].data);
			mlx_delete_xpm42(texture->dragon_img[i].xpm);
			i++;
			printf ("%d\n", i);
		}
	}
}
void	clean_data(t_game *gdata)
{
	clean_path(&gdata->texture.path);
	free_matrix(gdata->map.matrix);
	free_matrix(gdata->map.tmp_matrix);
	free_matrix(gdata->map.void_matrix);
	if (/*gdata && */gdata->vision.FOV.rays) 
		free(gdata->vision.FOV.rays);
	free_map_sprites(gdata, &gdata->texture);
	free_dragon_sprites(gdata, &gdata->texture);
}
