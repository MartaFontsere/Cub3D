/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/31 18:50:30 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TEMPORAL
void	print_matrix(char **matrix, int flag)
{
	int	i = 0;

	while (matrix[i])
	{
		if (flag == 1)
			printf(YELLOW"%s\n"END, matrix[i]);
		else
			printf(BLUE"%s\n"END, matrix[i]);
		i++;
	}
}
void	prints_check(t_map *map)
{
	printf(YELLOW"%s\n"END, map->shader.NO);
	printf(YELLOW"%s\n"END, map->shader.SO);
	printf(YELLOW"%s\n"END, map->shader.WE);
	printf(YELLOW"%s\n"END, map->shader.EA);
	//colors
	printf(RED"%d,"END, map->shader.C.R);
	printf(GREEN"%d,"END, map->shader.C.G);
	printf(BLUE"%d\n"END, map->shader.C.B);
	printf(RED"[%d],"END, map->shader.F.R);
	printf(GREEN"[%d],"END, map->shader.F.G);
	printf(BLUE"[%d]\n"END, map->shader.F.B);
}
//END TEMPORAL



void    init_structs(char **av, t_map *map)
{	
	map->rawmap = NULL;
    map->matrix = NULL;
    map->tmp_matrix = NULL;
	map->fd_path = av[1];
	map->is_map = 0;
	map->map_width = 0;
	map->map_height = 0;
	init_shader(&map->shader);
}

void	init_shader(t_shader *shader)
{
	shader->NO = NULL;
	shader->SO = NULL;
	shader->EA = NULL;
	shader->WE = NULL;
	shader->count = 0;
	shader->err_flag = 0;
	shader->C.R = 0;
	shader->C.G = 0;
	shader->C.B = 0;
	shader->F.R = 0;
	shader->F.G = 0;
	shader->F.B = 0;
	shader->C.shader = shader;
	shader->F.shader = shader;
}

int main (int ac, char **av)
{
    t_map		map;
	
	(void)ac;
	init_structs(av, &map);
	if (!fd_is_correct(&map))
	{
		clean_data(&map);
		map.fd_path = NULL;
		return (0);
	}
	prints_check(&map);//si hay un error, no va a printar porque ha salido antes
	clean_data(&map);
    return (1);
}
