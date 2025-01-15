/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:28:37 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/15 16:45:51 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_name(char *map_path)
{
	char	*ext;

	ext = ft_strchr(map_path, '.');
	//printf("ext: %s\n", ext);
	if (ft_strlen(map_path) < 5)
		return (0);
	if (strcmp(ext, ".cub") != 0)
	{
		printf("Invalid name map\n");
		return (1);
	}
	return (0);
}
void	exit_error(char *msg, int status)
{
	while (*msg)
		write(2, msg++, 1);
	exit(status);
}

char    **get_final_map(int ac, char **av, t_map *map)
{
    //char    **map;
	(void)map;
    if (ac != 2 || check_name(av[1]) != 0)
		exit_error("Invalid arguments\n", 1);
	printf("name ook\n");
    return (NULL);
}
