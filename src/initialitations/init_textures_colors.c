/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:06:32 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/14 13:44:49 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	init_colors(path);
}
