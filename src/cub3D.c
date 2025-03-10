/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 01:48:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(t_game	*gdata)
{
	if (gdata->finish_game == 0)
	{
		ft_write(1, "\nYou've left The Game... but The Game will never leave you 👀\n", 64);
		ft_write(1, "    See you soon 😈🔥\n", 26);
		//ft_write(1, "\nOoops... You left the game before finishing 😩\n", 50);
	}
	mlx_close_window(gdata->mlx.init);
}


int main(int ac, char **av)
{
	t_game	gdata;

 //YAJA
	(void)ac;
	(void)av;


	gdata.map.matrix = parsing_pre_yajaira(&gdata);
	if(!gdata.map.matrix)
	{
		ft_write(2, "Error generating the map matrix\n", 32);
		return 1;
	}

	if (init_gdata_values(&gdata) == 0)
		return (1);

	printf ("image %p, mini %p\n",gdata.mlx.image, gdata.mlx.mini_image);
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	if (prepare_textures (&gdata) == 0)
		return (1);
	print_map (&gdata, gdata.mlx, gdata.map);
	print_minimap(&gdata);
		

	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init); 
	

	//añadir el free de vision->rays
	return (0);

}

//INICIALIZAR ESTRUCTURAS, PUNTEROS, ARRAY... y los punteros de dentro de la estructura
//CUANDO SI Y CUANDO NO ALOCAR MEMORIA. EJ> *ray DENTRO DE T_FOV

//Lo mejor para ver que todos los numeros se hacen bien, es hacer un mapa de 5x5, ya que asi podemos hacer una ventana de 60x60, asumiendo que cada celda son 12 pixeles y asi cuando pongamos el player en el centro, cuando hagamos el fov de 60 grados, cada rayo ira a un pixel distinto
//Asi, al ver las cosas con numeros enteros y con un mapa pequenyo, sera mas facil detectar si estamos haciendo bien los calculos, relacionar conceptos y sacar conclusiones si falla algo