/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:36:13 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/17 13:44:42 by yanaranj         ###   ########.fr       */
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

/*	solo puede contener una de las letras indicadas. Y si o si debe haber una
	orientacion de camara
*/
int	min_chars(char *raw_map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (raw_map[i])
	{
		if (raw_map[i] == 'N' || raw_map[i] == 'S' || raw_map[i] == 'E' || raw_map[i] == 'W')
		{
			count++;
			i++;
		}
		if (raw_map[i] != '1' && raw_map[i] != '0' && raw_map[i] != '\n')
		{
			i++;
			return (0);	
		}
		else
			i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

//my_map es el mapa spliteado despues de haber rellenado los espacios encontrados

int	final_map(char **my_map, t_map *map, char *raw_map)
{
	(void)my_map;
	(void)map;
	if (!min_chars(raw_map))
		return (0);
	/*if (!min_size(map))
		return (0); */
	return (1);
}
