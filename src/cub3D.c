/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/21 20:28:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(t_game	*gdata)
{
	// if (gdata->finish_game == 0)
	// 	ft_write(1, "\nOoops... You left the game before finishing 😩\n", 50);
	mlx_close_window(gdata->mlx.init);
}


int main(int argc, char **argv)
{
	t_game	gdata;


	(void)argc;
	(void)argv;
	init_gdata_values(&gdata);
	//Primero necesito tener el mapa convertido a matriz
	gdata.map.matrix = parsing_pre_yahaira(&gdata);
	if(!gdata.map.matrix)
	{
		write(2, "error generating the map matrix\n", 32);
		return 1;
	}
	// A partir de aqui:
	init_minimap(&gdata, &gdata.map);
	init_player_parameters(&gdata, &gdata.player);
	// instalar la mlx, y lanzar una pantalla del tamaño, x y, para ver que funciona
	if (init_mlx_and_create_new_image(&gdata, &gdata.mlx) == 0)
		return (0);
	if (mlx_image_to_window(gdata.mlx.init, gdata.mlx.image, 0, 0) == -1)
	{
		write_error("It's not possible to put new image to window");
		close_window(&gdata);
		return (0);
	}
	print_minimap(&gdata);
	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init);
	

}
