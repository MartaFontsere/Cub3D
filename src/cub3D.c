/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/21 13:22:39 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(t_game *gdata)
{
	if (gdata->finish_game == 0)
	{
		ft_write(1,
			"\nYou've left The Game... but The Game will never leave you 👀\n",
			64);
		ft_write(1, "    See you soon 😈🔥\n", 26);
	}
	mlx_close_window(gdata->mlx.init);
}

int	main(int ac, char **av)
{
	t_game	gdata;

	init_map_params(&gdata, &gdata.map);
	init_textures_and_colors_path(&gdata.texture, &gdata.texture.path);
	if (!read_file(ac, av, &gdata, &gdata.map))
		return (1);
	if (!parse_map(&gdata, gdata.map.matrix, &gdata.map))
		return (1);
	if (init_gdata_values(&gdata) == 0)
		return (1);
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	if (prepare_textures(&gdata) == 0)
		return (1);
	print_map(&gdata, gdata.mlx, gdata.map);
	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init);
	clean_data(&gdata);
	mlx_terminate(gdata.mlx.init);
	return (0);
}
