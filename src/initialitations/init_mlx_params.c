/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:09:51 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/25 17:31:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->window_width = MAP_PX_WIDTH;
	mlx->window_height = MAP_PX_HEIGHT;
	mlx->init = mlx_init(mlx->window_width, mlx->window_height,
			"The Game", true); // ESTO CAMBIARA, LAS MEDIDAS DE LA VENTANA
	if (!mlx->init)
	{
		write_error("It's not possible to initialize the mlx");
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}

int	create_new_images(t_game *gdata, t_mlx *mlx)
{
	mlx->image = mlx_new_image(mlx->init, mlx->window_width, mlx->window_height);
	printf ("window: %d, %d\n",  mlx->window_width,mlx->window_height);
	if (!mlx->image)
	{
		write_error("It's not possible to generate new image");
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	mlx->mini_image = mlx_new_image(mlx->init, gdata->minimap.px_width, gdata->minimap.px_height);
	if (!mlx->mini_image)
	{
		write_error("It's not possible to generate new mini_image");
		close_window(gdata);
		//free_raw_and_map(gdata); REVISAR 
		return (0);
	}
	return (1);
}

int	put_image_to_window(t_game *gdata, t_mlx *mlx)
{
	if (mlx_image_to_window(mlx->init, mlx->image, 0, 0) == -1)
	{
		write_error("It's not possible to put new image to window");
		//free_raw_and_map(gdata); REVISAR 
		close_window(gdata);
		return (0);
	}
	if (mlx_image_to_window(mlx->init, mlx->mini_image, 15, 15) == -1)
	{
		write_error("It's not possible to put new image to window");
		//free_raw_and_map(gdata); REVISAR 
		close_window(gdata);
		return (0);
	}
	return (1);
}
