/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 01:46:16 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



int	init_gdata_values(t_game *gdata)
{
	init_minimap_params(gdata);
	init_player_parameters(gdata, &gdata->player);
	if (init_vision_parameters (gdata, &gdata->vision) == 0)
		return (0);
	// instalar la mlx, y lanzar una pantalla del tamaño, x y, para ver que funciona
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (gdata->door.there_is_door == 1)
		init_door_position (&gdata->map, &gdata->door);
	if (init_mlx(&gdata->mlx) == 0)
		return (0);
	if (create_new_images(gdata, &gdata->mlx) == 0)
		return (0);
	if (put_image_to_window(gdata, &gdata->mlx) == 0)
		return (0);
	return (1);
	//gdata->finish_game = 0;
}


