/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:03 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/18 16:05:52 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_can_be_open(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	load_image(t_game *gdata, t_image *image, char *path)
{
	if (check_file_can_be_open(path) == 0)
	{
		msg_error("There have been problems opening the textures\n", NULL);
		return (0);
	}
	image->xpm = mlx_load_xpm42(path);
	image->data = mlx_texture_to_image(gdata->mlx.init, &image->xpm->texture);
	return (1);
}

int	prepare_textures(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.north_wall_img,
			gdata->texture.path.NO))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.south_wall_img,
			gdata->texture.path.SO))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.east_wall_img,
			gdata->texture.path.EA))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.west_wall_img,
			gdata->texture.path.WE))
	{
		clean_data(gdata);
		return (0);
	}
	//BONUS
	if (!load_image(gdata, &gdata->texture.sky_img, SKY_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.floor_img, FLOOR_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.door_img, DOOR_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}

int	prepare_animation (t_game *gdata)
{
		///return error; //MIRAR LA FUNCION DE FREE PERTINENTE y escribir error
	if (!load_image(gdata, &gdata->texture.dragon_img[0], DRAGON_1))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[1], DRAGON_2))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[2], DRAGON_3))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[3], DRAGON_2))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}