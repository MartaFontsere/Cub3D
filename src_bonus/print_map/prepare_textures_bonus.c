/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_textures_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:03 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 14:31:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	printf ("path: %s\n", path);
	if (check_file_can_be_open(path) == 0)
	{
		msg_error("There have been problems opening the textures\n", NULL);
		return (0);
	}
	image->xpm = mlx_load_xpm42(path);
	image->data = mlx_texture_to_image(gdata->mlx.init, &image->xpm->texture);
	return (1);
}

int	prepare_wall_textures(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.north_wall_img,
			gdata->texture.path.no))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.south_wall_img,
			gdata->texture.path.so))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.east_wall_img,
			gdata->texture.path.ea))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.west_wall_img,
			gdata->texture.path.we))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}

int	prepare_map_bonus_textures(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.sky_img,
			gdata->texture.path.c.color_path))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.floor_img,
			gdata->texture.path.f.color_path))
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

int	prepare_textures(t_game *gdata)
{
	if (!prepare_wall_textures(gdata))
		return (0);
	if (gdata->texture.path.f.is_path && gdata->texture.path.c.is_path)
	{
		if (!prepare_map_bonus_textures(gdata))
			return (0);
	}
	return (1);
}
