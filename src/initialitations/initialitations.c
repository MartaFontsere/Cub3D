/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialitations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 02:14:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_gdata_values(t_game *gdata)
{
	gdata->finish_game = 0;
	init_minimap_params(gdata);
	init_player_params(gdata, &gdata->player);
	if (init_vision_params(gdata, &gdata->vision) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (init_mlx(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (create_new_images(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	if (put_image_to_window(gdata, &gdata->mlx) == 0)
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}
