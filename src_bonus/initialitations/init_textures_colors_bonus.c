/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_colors_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:17:15 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/14 15:39:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_sprites(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture->dragon_img[i].data = NULL;
		texture->dragon_img[i].xpm = NULL;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		texture->fire_img[i].data = NULL;
		texture->fire_img[i].xpm = NULL;
		i++;
	}
}

void	init_textures(t_texture *texture, t_path *path)
{
	texture->north_wall_img.data = NULL;
	texture->south_wall_img.data = NULL;
	texture->west_wall_img.data = NULL;
	texture->east_wall_img.data = NULL;
	path->no = NULL;
	path->so = NULL;
	path->ea = NULL;
	path->we = NULL;
	texture->sky_img.data = NULL;
	texture->floor_img.data = NULL;
	texture->door_img.data = NULL;
	path->c.is_path = 0;
	path->c.color_path = NULL;
	path->f.is_path = 0;
	path->f.color_path = NULL;
}

void	init_colors(t_path *path)
{
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->c.r = 0;
	path->c.g = 0;
	path->c.b = 0;
	path->c.split = NULL;
	path->c.path = path;
	path->c.assigned = 0;
	path->f.r = 0;
	path->f.g = 0;
	path->f.b = 0;
	path->c.split = NULL;
	path->f.path = path;
	path->f.assigned = 0;
}

void	init_textures_and_colors_path(t_texture *texture, t_path *path)
{
	init_textures(texture, path);
	init_sprites(texture);
	init_colors(path);
}
