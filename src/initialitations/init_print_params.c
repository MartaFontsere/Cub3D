/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_print_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:47:23 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/21 13:34:03 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_textures_and_colors_path(t_texture *texture, t_path *path)
{
	texture->north_wall_img.data = NULL;
	texture->south_wall_img.data = NULL;
	texture->west_wall_img.data = NULL;
	texture->east_wall_img.data = NULL;
	path->NO = NULL;
	path->SO = NULL;
	path->EA = NULL;
	path->WE = NULL;
	path->p_count = 0;
	path->c_count = 0;
	path->err_flag = 0;
	path->C.R = 0;
	path->C.G = 0;
	path->C.B = 0;
	path->C.path = path;
	path->C.assigned = 0;
	path->F.R = 0;
	path->F.G = 0;
	path->F.B = 0;
	path->F.path = path;
	path->F.assigned = 0;
}
