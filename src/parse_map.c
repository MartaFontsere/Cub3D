/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:45:21 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/14 20:07:56 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
						11**11
						1001**
						1****1
						1*0011
						11111*
*/

#include "cub3D.h"

int	min_chars(char **matrix, t_map *map)
{
	(void)map;
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{	
			if (matrix[i][j] != 'N' && matrix[i][j] != 'S' && matrix[i][j] != 'E'\
			&& matrix[i][j] != 'W' && matrix[i][j] != '1' && matrix[i][j] != '0'\
			&& matrix[i][j] != '\n' && matrix[i][j] != ' ' && matrix[i][j] != '*')
				return (0);
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E'\
			|| matrix[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		msg_error("Invalid number of player", NULL);
		printf(RED"players: [%d]\n"END, count);
		return (0);
	}
	return (1);
}



int		parse_map(char **matrix, t_map *map)
{
	if (!min_chars(matrix, map))
		return (0);
	return (1);
}
