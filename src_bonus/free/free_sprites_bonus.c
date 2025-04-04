/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:25:43 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 03:51:58 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_walls_sprites(t_game *gdata, t_texture *texture)
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

void	free_bonus_map_sprites(t_game *gdata, t_texture *texture)
{
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
	int	i;

	i = 0;
	if (texture->dragon_img[0].data)
	{
		while (i < 4)
		{
			mlx_delete_image(gdata->mlx.init, texture->dragon_img[i].data);
			mlx_delete_xpm42(texture->dragon_img[i].xpm);
			i++;
		}
	}
}
