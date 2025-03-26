/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dragon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 05:23:11 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 17:54:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_dragon(t_game *gdata)
{
	mlx_image_to_window(gdata->mlx.init, gdata->texture.dragon_img[0].data,
				430, 900);
}