/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/20 13:21:28 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cub_strdup(char *s1, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}

char	**copy_map(char **map, size_t height)
{
	char	**map_tmp;
	size_t	i;

	i = 0;
	map_tmp = malloc(sizeof(char*) * (height + 1));
	if (!map_tmp)
		return (NULL);
	while (i < height)
	{
		map_tmp[i] = ft_strdup(map[i]);
		if (!map_tmp[i])
			return (free_matrix(map_tmp), NULL);
		i++;
	}
	map_tmp[i] = NULL;
	return (map_tmp);
}
