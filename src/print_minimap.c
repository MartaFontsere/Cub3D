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

// void print_player (t_minimap minimap, t_map map)
// {
// 	int x;
// 	int y;
// 	int i;
// 	int j;

// 	y = 0;
// 	while (map.matrix[y])
// 	{
// 		x = 0;
// 		while (map.matrix[y][x])
// 		{
// 			if (map.matrix[y][x] == 'N' || map.matrix[y][x] == 'S' || map.matrix[y][x] == 'E' || map.matrix[y][x] == 'W')
// 			{
// 				i = 0;
// 				while (i < minimap.height / map.height)
// 				{
// 					j = 0;
// 					while (j < minimap.width / map.width)
// 					{
// 						mlx_put_pixel(minimap.background_img, j, i, RED1);
// 						j++;
// 					}
// 					i++;
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void print_walls (t_minimap minimap, t_map map)
{
	int x;
	int y;
	int i;
	int j;
	int count1;
	int count2;

	printf ("entro 2\n");
	y = 0;
	while (map.matrix[y])
	{
		x = 0;
		while (map.matrix[y][x])
		{
			if (map.matrix[y][x] == '1')
			{
				printf ("he encontrado un 1\n");
				i = y * (minimap.height / map.height);
				count1 = 0;
				while (count1 < minimap.height / map.height)
				{
					j = x * minimap.width / map.width;
					count2 = 0;
					while (count2 < minimap.width / map.width)
					{
						mlx_put_pixel(minimap.background_img, j, i, SOFT_GREY);
						j++;
						count2++;
					}
					i++;
					count1++;
				}
			}
			x++;
		}
		y++;
	}
	//como combinar posicion del pixel y cantidad de pixeles en la condicion
}

void print_background (t_minimap minimap)
{
	int	x;
	int	y;
	
	printf ("entro 1\n");
	y = 0;
	while (y < minimap.height)
	{
		x = 0;
		while (x < minimap.width)
		{
			mlx_put_pixel(minimap.background_img, x, y, DARK_GREY);
			x++;
		}
		y++;
	}

}

void	print_minimap(t_game *gdata)
{
	print_background (gdata->minimap); //CONFIRMAR si yo me paso esta info asi, no estoy mandando el puntero, por lo que si modifico algo en la estructura no se mantiene el cambio. aunque gdata sea puntero, lo que mando es algo nuevo, si quiero que sea puntero tendre que indicarlo concretamente para esa variable, aunque forme parte de gdata. 
	print_walls (gdata->minimap, gdata->map);
	//print_player (gdata->minimap);
	mlx_image_to_window(gdata->mlx.init, gdata->minimap.background_img, 0, 0);
}