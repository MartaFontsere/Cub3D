/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/14 12:22:49 by mfontser         ###   ########.fr       */
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
	if (init_gdata_values(&gdata) == 0)
	{
		clean_data(&gdata);
		return (1);
	}
	if (!parse_map(gdata.map.matrix, &gdata.map))
	{
		clean_data(&gdata);
		return (1);
	}
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	if (prepare_textures (&gdata) == 0)
		return (1); //LIBERAR COSAS
	print_map (&gdata, gdata.mlx, gdata.map);
	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init); 
	clean_data(&gdata); //añadir el free de vision->rays
	return (0);

}
