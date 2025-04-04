/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 14:23:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (!parse_map(&gdata, gdata.map.matrix, &gdata.map)
		|| init_gdata_values(&gdata) == 0)
		return (1);
	calculate_fov(&gdata, gdata.player.x, gdata.player.y);
	if (prepare_textures(&gdata) == 0 || prepare_dragon_animation(&gdata) == 0 || prepare_fire_animation(&gdata) == 0)
		return (1);

	update_doors(&gdata);
	print_map(&gdata, gdata.map);
	print_minimap(&gdata);
	print_dragon(&gdata);
	mlx_key_hook(gdata.mlx.init, press_key, &gdata);
	mlx_cursor_hook(gdata.mlx.init, cursor_handle, &gdata);
	mlx_loop_hook(gdata.mlx.init, render_game, &gdata);
	mlx_loop(gdata.mlx.init);
	clean_data(&gdata);
	mlx_terminate(gdata.mlx.init);
	return (0);
}
