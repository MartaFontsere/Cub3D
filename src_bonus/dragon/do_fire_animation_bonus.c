/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fire_animation_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 05:39:40 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 12:57:37 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_fire_weight_for_dragon_frame(int dragon_frame)
{
	if (dragon_frame == 0)
		return (410);
	else if (dragon_frame == 1)
		return (431);
	else if (dragon_frame == 2)
		return (445);
	else if (dragon_frame == 3)
		return (431);
	return (410);
}

int	get_fire_height_for_dragon_frame(int dragon_frame)
{
	if (dragon_frame == 0)
		return (708);
	else if (dragon_frame == 1)
		return (645);
	else if (dragon_frame == 2)
		return (620);
	else if (dragon_frame == 3)
		return (645);
	return (708);
}

void	update_fire_clock(int *fire_clock, double speed)
{
	if (*fire_clock >= speed * 8)
		*fire_clock = 0;
}

void	end_fire_animation(t_game *gdata, int current_index,
		int *fire_clock, int *last_index)
{
	t_image		*fire;

	fire = gdata->texture.fire_img;
	if (fire[current_index].data != NULL)
	{
		mlx_delete_image(gdata->mlx.init, fire[current_index].data);
		fire[current_index].data = NULL;
	}
	gdata->player.fire = 0;
	*last_index = -1;
	*fire_clock = 0;
}

void	do_fire_animation(t_game *gdata)
{
	static int	fire_clock = 0;
	static int	current_index = 0;
	static int	last_index = -1;
	t_image		*fire;
	double		animation_speed;

	fire = gdata->texture.fire_img;
	animation_speed = 1.5;
	update_fire_clock(&fire_clock, animation_speed);
	current_index = fire_clock / animation_speed;
	remove_last_fire_frame(gdata, fire, current_index, &last_index);
	ensure_fire_frame_exists(gdata, fire, current_index);
	update_fire_position(gdata);
	mlx_image_to_window(gdata->mlx.init, fire[current_index].data,
		gdata->player.fire_weight, gdata->player.fire_height);
	last_index = current_index;
	if (current_index == 7)
		end_fire_animation(gdata, current_index, &fire_clock,
			&last_index);
	else
		fire_clock++;
}
