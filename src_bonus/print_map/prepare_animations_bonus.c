/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_animations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:05:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 14:40:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	prepare_dragon_animation(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.dragon_img[0], DRAGON_1))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[1], DRAGON_2))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[2], DRAGON_3))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.dragon_img[3], DRAGON_2))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}

int	fire_animation_1(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.fire_img[0], FIRE_0))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[1], FIRE_1))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[2], FIRE_2))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[3], FIRE_3))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}

int	fire_animation_2(t_game *gdata)
{
	if (!load_image(gdata, &gdata->texture.fire_img[4], FIRE_4))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[5], FIRE_5))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[6], FIRE_6))
	{
		clean_data(gdata);
		return (0);
	}
	if (!load_image(gdata, &gdata->texture.fire_img[7], FIRE_7))
	{
		clean_data(gdata);
		return (0);
	}
	return (1);
}

int	prepare_fire_animation(t_game *gdata)
{
	if (!fire_animation_1(gdata))
		return (0);
	if (!fire_animation_2(gdata))
		return (0);
	return (1);
}
