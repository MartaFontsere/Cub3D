/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:09:51 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/27 04:23:05 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	put_image_to_window(t_game *gdata, t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->init, mlx->image, 0, 0) == -1)
	{
		msg_error("It's not possible to put new image to window\n", NULL);
		close_window(gdata);
		clean_data(gdata);
		return (0);
	}
	if (mlx_image_to_window(mlx->init, mlx->mini_image, 15, 15) == -1)
	{
		msg_error("It's not possible to put new image to window\n", NULL);
		//free_raw_and_map(gdata); REVISAR 
		close_window(gdata);
		return (0);
	}
	return (1);
}

int	create_new_images(t_game *gdata, t_mlx *mlx)
{
	mlx->image = mlx_new_image(mlx->init, mlx->window_width,
			mlx->window_height);
	printf("window: %d, %d\n", mlx->window_width, mlx->window_height);
	if (!mlx->image)
	{
		msg_error("It's not possible to generate new image\n", NULL);
		close_window(gdata);
		clean_data(gdata);
		return (0);
	}
	mlx->mini_image = mlx_new_image(mlx->init, gdata->minimap.px_width, gdata->minimap.px_height);
	if (!mlx->mini_image)
	{
		msg_error("It's not possible to generate new mini_image\n", NULL);
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}

int	init_mlx(t_game *gdata, t_mlx *mlx)
{
	mlx->window_width = MAP_PX_WIDTH;
	mlx->window_height = MAP_PX_HEIGHT;
	mlx->init = mlx_init(mlx->window_width, mlx->window_height, "The Game",
			false);
	if (!mlx->init)
	{
		msg_error("It's not possible to initialize the mlx\n", NULL);
		clean_data(gdata);
		return (0);
	}
	return (1);
}
