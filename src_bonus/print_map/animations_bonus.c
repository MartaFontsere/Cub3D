/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:05:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 13:43:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	prepare_animation(t_game *gdata)
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
