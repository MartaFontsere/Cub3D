/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/09 23:20:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void print_map (t_mlx mlx, t_map map)
{
	int	x;
	int	y;

	x = 0;
	printf ("MAP width %d\n", map.px_width);
	printf ("MAP height %d\n", map.px_height);
	
	while (x < px_width)
	{
		y = 0;
		while (y < map.px_height)
		{
			while ()
		}

	}


	while (y < map.px_height)
	{
		x = 0;
		while (x < map.px_width)
		{
			

			mlx_put_pixel(mlx.image, x, y, BLUE1);
			x++;
		}
		y++;
	}
}