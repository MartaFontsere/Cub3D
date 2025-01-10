/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 01:42:50 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	print_minimap(t_game *gdata, t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	if (load_sprites(gdata, mlx) == 0)
		return (0);
	while (gdata->map[y])
	{
		x = 0;
		while (gdata->map[y][x])
		{ 
			print_tile(gdata, x, y);
			x++;
		}
		y++;
	}
	gdata->player.x = gdata->player.x * SPRITES_WIDTH;
	gdata->player.y = gdata->player.y * SPRITES_HEIGHT;
	return (1);
}
