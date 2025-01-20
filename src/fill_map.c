/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:47:14 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/20 14:20:34 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*fill_void(char *raw_map)
{
	int i;

	i = 0;
	while (raw_map[i])
	{
		if (raw_map[i] == ' ' || raw_map[i] == '\t')
			raw_map[i] = 'R';
		i++;
	}
	return (raw_map);
}

int	ft_max_size(char *line, int max)
{
	int	size;

	size = ft_strlen(line) - 1;
	if (max < size)
		max = size;
	return (max);
}

