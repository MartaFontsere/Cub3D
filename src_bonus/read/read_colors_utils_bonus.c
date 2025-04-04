/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:58:12 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/04 12:50:57 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	cpy_colors(char *rgb, t_color *color, int i)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split[0] || !split[1] || !split[2])
	{
		color->path->err_flag = 1;
		return (free_matrix(split), msg_error("Invaid split\n", rgb));
	}
	while (split[++i])
	{
		if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 0)
			color->r = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 1)
			color->g = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 2)
			color->b = ft_atoi(split[i]);
		else
		{
			color->path->err_flag = 1;
			return (msg_error("Out of range: ", split[i]), free_matrix(split));
		}
	}
	color->assigned = 1;
	color->path->c_count++;
	free_matrix(split);
}
