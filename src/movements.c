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

void	prepare_right_target(t_game *gdata, int *target_x, int *count)
{
	*target_x = (*target_x + gdata->player.speed);
}

void	prepare_left_target(t_game *gdata, int *target_x, int *count)
{
	*target_x = (*target_x - gdata->player.speed);
}

void	prepare_up_target(t_game *gdata, int *target_y, int *count)
{
	*target_y = (*target_y - gdata->player.speed);
}

void	prepare_down_target(t_game *gdata, int *target_y, int *count)
{
	*target_y = (*target_y + gdata->player.speed);
}