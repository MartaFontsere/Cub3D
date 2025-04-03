/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_colors_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:17:15 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/02 19:55:31 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_textures(t_texture *texture, t_path *path)
{
	texture->north_wall_img.data = NULL;
	texture->south_wall_img.data = NULL;
	texture->west_wall_img.data = NULL;
	texture->east_wall_img.data = NULL;
	path->NO = NULL;
	path->SO = NULL;
	path->EA = NULL;
	path->WE = NULL;
	texture->sky_img.data = NULL;
	texture->floor_img.data = NULL;
	texture->door_img.data = NULL;
	texture->dragon_img[0].data = NULL;
	path->C.is_path = 0;
	path->C.color_path = NULL;
	path->F.is_path = 0;
	path->F.color_path = NULL;
}

void	init_colors(t_path *path)
{
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->C.R = 0;
	path->C.G = 0;
	path->C.B = 0;
	path->C.split = NULL;
	path->C.path = path;
	path->C.assigned = 0;
	path->F.R = 0;
	path->F.G = 0;
	path->F.B = 0;
	path->C.split = NULL;
	path->F.path = path;
	path->F.assigned = 0;	
}

void init_textures_and_colors_path(t_texture *texture, t_path *path)
{
	init_textures(texture, path);
	init_colors(path);
}
