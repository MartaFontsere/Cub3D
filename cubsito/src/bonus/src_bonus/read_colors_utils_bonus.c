/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:58:12 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/21 12:22:20 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

//CUIDADO CON path->c_count++, porque esta funcion es tambien para NSWE
char	*clean_str(char *src, int start, int end, t_path *path)
{
	char	*str;
	
	(void)path;
	//path->c_count++;
	str = ft_substr(src, start, end);
	free(src);
	return (str);
}

void	cpy_colors(char *rgb, t_color *color, int i)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split[0] || !split[1] || !split[2])
	{
		color->path->err_flag = 1;
		return (free_matrix(split), msg_error("Invaid split\n", NULL));
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
