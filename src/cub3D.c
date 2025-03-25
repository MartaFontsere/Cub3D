/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/19 16:43:22 by yanaranj         ###   ########.fr       */
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

	init_map_params (&gdata.map);
	init_textures_and_colors_path(&gdata.texture.path);
	if (!read_file(ac, av, &gdata))
	{
		clean_data(&gdata);
		return (1);
	}
	//if (init_gdata_values(&gdata) == 0)// no deberiamos hacer el parseo antes de esto?
	//{
	//	clean_data(&gdata);
	//	return (1);
	//}
	if (!parse_map(gdata.map.matrix, &gdata.map))
	{
		clean_data(&gdata);
		return (1);
	}
	//printf ("image pointer %p, mini pointer %p\n",gdata.mlx.image, gdata.mlx.mini_image);
	//calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	//if (prepare_textures (&gdata) == 0)
	//	return (1);
	//print_map (&gdata, gdata.mlx, gdata.map);
//
 	//printf("The matrix is:\n");
 	//int i = 0;
 	//while (gdata.map.matrix[i])
 	//{
 	//	int j = 0;
 	//	while (gdata.map.matrix[i][j])
 	//	{
 	//		printf ("%c", gdata.map.matrix[i][j]);
 	//		j++;
 	//	}
 	//	printf("\n");
 	//	i++;
 	//}
//
//
	//print_minimap(&gdata);
	//	
//
	//mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	//mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	//mlx_loop(gdata.mlx.init); 
	//
	clean_data(&gdata); //añadir el free de vision->rays
	return (0);

}
