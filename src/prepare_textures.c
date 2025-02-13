/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:03 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/13 04:22:00 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_can_be_open(char *path) //PREGUNTAR YAJA SI YA LO HACE ELLA
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
	//int32_t	index;

	if (check_file_can_be_open(path) == 0)
	{
		write_error("There have been problems opening the textures");
		return (0);
	}
	image->xpm = mlx_load_xpm42(path);
	image->data = mlx_texture_to_image(gdata->mlx.init, &image->xpm->texture);
	// index = mlx_image_to_window(gdata->mlx.init, image->data, -100, -100);
	// mlx_set_instance_depth(&image->data->instances[index], 8);
	return (1);
}


int	prepare_textures (t_game *gdata)
{
	//if (!load_image(gdata, &gdata->texture.north_wall_img, gdata->texture.path.NO)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.north_wall_img, NORTH_TEXTURE))
		printf ("hola"); //BORRAR
		//return (free_error_idle_right(0, gdata)); //MIRAR LA FUNCION DE ERROR PERTINENTE
	//if (!load_image(gdata, &gdata->texture.south_wall_img, gdata->texture.path.SO)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.south_wall_img, SOUTH_TEXTURE))
		printf ("hola"); //BORRAR
		//return (free_error_idle_right(0, gdata)); //MIRAR LA FUNCION DE ERROR PERTINENTE
	//if (!load_image(gdata, &gdata->texture.east_wall_img, gdata->texture.path.EA)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.east_wall_img, EAST_TEXTURE))
		printf ("hola"); //BORRAR
		//return (free_error_idle_right(0, gdata)); //MIRAR LA FUNCION DE ERROR PERTINENTE
	//if (!load_image(gdata, &gdata->texture.west_wall_img, gdata->texture.path.WE)) --> LO CORRECTO CUANDO TENGA LAS TEXTURAS GUARDADAS DEL PARSING
	if (!load_image(gdata, &gdata->texture.west_wall_img, WEST_TEXTURE))
		printf ("hola"); //BORRAR
		//return (free_error_idle_right(0, gdata)); //MIRAR LA FUNCION DE ERROR PERTINENTE
	return (1);
}

	