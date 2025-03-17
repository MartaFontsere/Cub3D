/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 17:43:07 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(t_game	*gdata)
{
	if (gdata->finish_game == 0)
	{
		ft_write(1, "\nYou've left The Game... but The Game will never leave you 👀\n", 64);
		ft_write(1, "    See you soon 😈🔥\n", 26);
	}
	mlx_close_window(gdata->mlx.init);
}


int main(int ac, char **av)
{
	t_game	gdata;

	//gdata.map.matrix = parsing_pre_yajaira(&gdata);
	// if(!gdata.map.matrix)
	// {
	// 	ft_write(2, "Error generating the map matrix\n", 32);
	// 	return 1;
	// }

	init_map_params (&gdata.map);
	init_textures_and_colors_path(&gdata.texture.path);
	if (!read_file(ac, av, &gdata))
	{
		clean_data(&gdata);
		return (1);
	}
	if (!parse_map(gdata.map.matrix, &gdata.map, &gdata))
	{
		clean_data(&gdata);
		return (1);
	}
	if (init_gdata_values(&gdata) == 0)
	{
		clean_data(&gdata);
		return (1);
	}
	// printf ("letra del player |%c|\n", gdata.player)
	printf ("image pointer %p, mini pointer %p\n",gdata.mlx.image, gdata.mlx.mini_image);
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	if (prepare_textures (&gdata) == 0)
		return (1); //LIBERAR COSAS
	if (prepare_animation (&gdata) == 0)
		return (1); //LIBERAR COSAS
	print_map (&gdata, gdata.mlx, gdata.map);

 	// printf("The matrix is:\n");
 	// int i = 0;
 	// while (gdata.map.matrix[i])
 	// {
 	// 	int j = 0;
 	// 	while (gdata.map.matrix[i][j])
 	// 	{
 	// 		printf ("%c", gdata.map.matrix[i][j]);
 	// 		j++;
 	// 	}
 	// 	printf("\n");
 	// 	i++;
 	// }

	print_minimap(&gdata);
	print_dragon (&gdata);

	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init); 
	
	clean_data(&gdata); //añadir el free de vision->rays
	return (0);

}
