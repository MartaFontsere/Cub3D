/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dragon_animation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:21:47 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 12:27:11 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	do_dragon_animation(t_game *gdata)
{
	double		animation_speed;
	static int	fly_clock = 0;
	static int	current_index = 0;
	static int	last_index = -1;
	t_image		*dragon;

	animation_speed = 1.5;
	dragon = gdata->texture.dragon_img;
	fly_clock++;
	if (fly_clock >= animation_speed * 4)
		fly_clock = 0;
	current_index = fly_clock / animation_speed;
	if (last_index != -1 && last_index != current_index)
	{
		if (dragon[last_index].data)
			mlx_delete_image(gdata->mlx.init, dragon[last_index].data);
		dragon[last_index].data = NULL;
	}
	if (dragon[current_index].data == NULL)
		dragon[current_index].data = mlx_texture_to_image(gdata->mlx.init,
				&dragon[current_index].xpm->texture);
	mlx_image_to_window(gdata->mlx.init, dragon[current_index].data, 430, 900);
	gdata->player.dragon_frame = current_index;
	last_index = current_index;
}

void	print_dragon(t_game *gdata)
{
	mlx_image_to_window(gdata->mlx.init, gdata->texture.dragon_img[0].data, 430,
		900);
}
