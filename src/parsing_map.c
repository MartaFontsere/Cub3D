/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:13 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/16 19:27:09 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	num_strchr(char *str, char c)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (*str == c)
			n++;
		str++;
	}
	return (n);
}

/*solo puede contener una de las letras indicadas*/
int	min_chars(char *raw_map, t_map *map)
{
	(void)map;
	while (*raw_map)
	{
		if (*raw_map != '1' && *raw_map != '0' && *raw_map != '\n' \
			&& *raw_map != 'N' && *raw_map != 'S' && *raw_map != 'E' \
			&& *raw_map != 'W')
			{
				printf("flag1\n");
				return (0);	
			}
		raw_map++;
	}
	if (num_strchr(raw_map, 'N') != 1 || num_strchr(raw_map, 'S') != 1 \
		|| num_strchr(raw_map, 'E') != 1 || num_strchr(raw_map, 'W') != 1)
		return (0);
	return (1);
}

int	final_map(char **my_map, t_map *map, char *raw_map)
{
	(void)my_map;
	if (!min_chars(raw_map, map))
		return (0);
	/*if (!min_size(map))
		return (0); */
	return (1);
}
