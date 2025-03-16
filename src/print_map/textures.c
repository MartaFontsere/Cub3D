/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:03 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/14 00:30:09 by mfontser         ###   ########.fr       */
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

int	prepare_textures (t_game *gdata) //REVISAR TEXTURAS PARSEADAS, NO FUNCIONA
{
	//if (!load_image(gdata, &gdata->texture.north_wall_img, gdata->texture.path.NO)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.north_wall_img, NORTH_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	//if (!load_image(gdata, &gdata->texture.south_wall_img, gdata->texture.path.SO)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.south_wall_img, SOUTH_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	//if (!load_image(gdata, &gdata->texture.east_wall_img, gdata->texture.path.EA)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.east_wall_img, EAST_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	//if (!load_image(gdata, &gdata->texture.west_wall_img, gdata->texture.path.WE)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.west_wall_img, WEST_TEXTURE))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}
