/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/19 12:39:07 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mix_matrix(char **src, t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < map->cells_height)
	{
		j = 0;
		k = 0;
		while (src[i][j] && src[i][j] != '\n')
		{//si  no es espacio, copia en esta nueva matriz
			if (src[i][j] == '1' || src[i][j] == '0' || src[i][j] == 'N'\
			|| src[i][j] == 'S' || src[i][j] == 'E' || src[i][j] == 'W')
				map->void_matrix[i][k] = src[i][j];
			k++;
			j++;
		}
		//printf(PURPLE"curr_size: [%zu]\n"END, ft_strlen(map->void_matrix[i]));
		//printf(PURPLE"curr_line: %s\n"END, map->void_matrix[i]);
		i++;
	}
	map->void_matrix[i] = NULL;
	map->matrix = copy_map(map->void_matrix, map->cells_height);
	if (!map->matrix)
		free_matrix(src);
	return (1);
}

char	*fill_void(t_map *map)
{
	char	*cp_line;
	char	*new_line;
	
	cp_line = malloc(sizeof(char *) * (map->cells_width));
	if (!cp_line)
		return (NULL);
	//printf("W: %zu\n", map->cells_width);
	cp_line = ft_memset(cp_line, '*', map->cells_width - 1);//le quito uno para que no me sume un char extra
	//printf("C_L_len: [%zu]\n", ft_strlen(cp_line));
	//printf("C_L %s\n", cp_line);
	new_line = ft_strjoin(cp_line, "\n");
	//printf("N_L[%zu]\n", ft_strlen(new_line));
	free(cp_line);
	return (new_line);
}
int	complete_matrix(char **src, t_map *map)
{
	int		i;

	i = 0;
	map->void_matrix = malloc(sizeof(char *) * (map->cells_height + 1));
	if (!map->void_matrix)
		return (msg_error("Error allocating memory\n", NULL) ,0);
	while (src[i])
	{
		map->void_matrix[i] = fill_void(map);
		if (!map->void_matrix[i])
			return (0); 
		i++;
	}
	map->void_matrix[i] = NULL;
	//print_matrix(map->void_matrix, 2);
	//printf("\n");
	mix_matrix(src, map);
	return (1);
}


//me crea la matriz y hace un realloc a medida que se actualiza la altura del mapa
int	get_final_map(int ac, char **av, t_map *map)
{
	map->fd_path = av[1];
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	if (!fd_is_correct(map) || map->path.p_count != 4)//te genera la matriz con el realloc
	{
		if (map->path.p_count != 4 && map->path.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		map->fd_path = NULL;
		return (0);
	}
	//printf(RED"%zu\n"END, map->cells_width);
	if (!complete_matrix(map->tmp_matrix, map))
		return (0);
	for (size_t i = 0; i < map->cells_height; i++)
		printf(GREEN"[%zu] %s"END, ft_strlen(map->matrix[i]), map->matrix[i]);
	//print_matrix(map->matrix, 3);
	if (!parse_map(map->matrix, map))
		return (0);
	return (1);
}
