/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/11 21:03:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(t_game	*gdata)
{
	// if (gdata->finish_game == 0)
	// 	ft_write(1, "\nOoops... You left the game before finishing 😩\n", 50);
	mlx_close_window(gdata->mlx.init);
}


int main(int ac, char **av)
{
	t_game	gdata;


	(void)ac;
	(void)av;
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
	if (init_vision_parameters (&gdata, &gdata.vision) == 0)
		return (0);
	// instalar la mlx, y lanzar una pantalla del tamaño, x y, para ver que funciona
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (init_mlx(&gdata.mlx) == 0)
		return (0);
	if (create_new_images(&gdata, &gdata.mlx) == 0)
		return (0);
	if (mlx_image_to_window(gdata.mlx.init, gdata.mlx.image, 0, 0) == -1)
	{
		write_error("It's not possible to put new image to window");
		close_window(&gdata);
		return (0);
	}
	if (mlx_image_to_window(gdata.mlx.init, gdata.mlx.mini_image, 15, 15) == -1)
	{
		write_error("It's not possible to put new image to window");
		close_window(&gdata);
		return (0);
	}
	printf ("image %p, mini %p\n",gdata.mlx.image, gdata.mlx.mini_image);
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	prepare_textures (&gdata);
	print_map (&gdata, gdata.mlx, gdata.map);
	print_minimap(&gdata);
		print_player_and_fov (&gdata); //meter dentro de printminimap, y luego en print player fov in motion llamar a print tablero o algo asi
	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init); 
	

	//añadir el free de vision->rays

}

//INICIALIZAR ESTRUCTURAS, PUNTEROS, ARRAY... y los punteros de dentro de la estructura
//CUANDO SI Y CUANDO NO ALOCAR MEMORIA. EJ> *ray DENTRO DE T_FOV

//Lo mejor para ver que todos los numeros se hacen bien, es hacer un mapa de 5x5, ya que asi podemos hacer una ventana de 60x60, asumiendo que cada celda son 12 pixeles y asi cuando pongamos el player en el centro, cuando hagamos el fov de 60 grados, cada rayo ira a un pixel distinto
//Asi, al ver las cosas con numeros enteros y con un mapa pequenyo, sera mas facil detectar si estamos haciendo bien los calculos, relacionar conceptos y sacar conclusiones si falla algo