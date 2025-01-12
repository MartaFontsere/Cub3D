/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 00:45:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_game	gdata;


	(void)argc;
	(void)argv;
	init_gdata_values(&gdata);
	//Primero necesito tener el mapa convertido a matriz
	gdata.map_info.map = parsing_pre_yahaira(&gdata);
	if(!gdata.map_info.map){
		write(2, "error generating the map matrix\n", 32);
		return 1;
	}
	// A partir de aqui:
	init_player_position(&gdata.map_info, &gdata.player);
	init_player_orientation(&gdata.map_info, &gdata.player);
	// instalar la mlx, y lanzar una pantalla del tamaño, x y, para ver que funciona
	// if (init_mlx(&gdata, &gdata.mlx) == 0)
	// 	return (0);
	// if (print_minimap(&gdata, &gdata.mlx) == 0)
		return (0);

}
