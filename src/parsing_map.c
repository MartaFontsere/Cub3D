/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:42:57 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/23 19:56:48 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		min_chars(char **matrix)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] != '1' && matrix[i][j] != '0' && matrix[i][j] != '\n' \
			&& matrix[i][j] != ' ' && matrix[i][j] != 'N' && matrix[i][j] != 'S' \
			&& matrix[i][j] != 'E' && matrix[i][j] != 'W')
			{
				printf("no me sirve, salgo\n");
				return (0);
			}
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E' \
			|| matrix[i][j] == 'W')
			{
				printf("es un valid char\n");
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return(0);
	return (1);
}
