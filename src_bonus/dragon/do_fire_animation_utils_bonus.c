/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fire_animation_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:53:24 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 12:59:13 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	remove_last_fire_frame(t_game *gdata, t_image *fire, int current_index,
		int *last_index)
{
	if (*last_index != -1 && *last_index != current_index)
	{
		mlx_delete_image(gdata->mlx.init, fire[*last_index].data);
		fire[*last_index].data = NULL;
	}
}

void	ensure_fire_frame_exists(t_game *gdata, t_image *fire,
		int current_index)
{
	if (fire[current_index].data == NULL)
		fire[current_index].data = mlx_texture_to_image(gdata->mlx.init,
				&fire[current_index].xpm->texture);
}

void	update_fire_position(t_game *gdata)
{
	int	fire_weight;
	int	fire_height;

	fire_weight = get_fire_weight_for_dragon_frame(gdata->player.dragon_frame);
	fire_height = get_fire_height_for_dragon_frame(gdata->player.dragon_frame);
	gdata->player.fire_weight = fire_weight;
	gdata->player.fire_height = fire_height;
}
