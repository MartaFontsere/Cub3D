/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:08:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/04 14:33:58 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//podemos agregar la flag de color
int	is_valid_value(int value)
{
	if (!value)
		return (0);
	if (value >= 0 && value <= 255)
		return (1);
	return (1);
}

void	cpy_colors(char *rgb, t_color *color, int i)
{
	char	**split;

	split = ft_split(rgb, ',');
	if ((split[0] == NULL || split[1] == NULL || split[2] == NULL) && !split[3])
	{
		free_matrix(split);
		color->shader->err_flag = 1;
		return (msg_error("Invaid split\n", NULL));	
	}
	while (split[i])
	{
		if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 0)
			color->R = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 1)
			color->G = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 2)
			color->B = ft_atoi(split[i]);
		else
		{
			color->shader->err_flag = 1;
			msg_error("Is not a valid value: ", split[i]);
			break ;
		}
		i++;
	}
	color->shader->colors_count++;
	free_matrix(split);
}

void	get_colors(char *line, t_shader *shader, int i, int init)
{
	int		start;
	int		end;
	char	*str;
	int		comma;

	comma = 0;
	start = i;
	while (ft_isdigit(line[i]) || line[i] == ',')
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	end = i;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0' || comma != 2)
	{
		msg_error("This values are not correct: ", line);
		shader->err_flag = 1;
		return ;
	}
	str = ft_substr(line, start, end);
	if (line[init] == 'C')
		cpy_colors(str, &shader->C, 0);
	else if (line[init] == 'F')
		cpy_colors(str, &shader->F, 0);
	free(str);
}

void	assign_color(char *line, t_shader *shader, int i)
{
	int	init;

	init = i;
	if ((line[i] == 'C' || line[i] == 'F') && ft_isspace(line[i + 1]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
	{
		msg_error("Invalid line: ", line);
		shader->err_flag = 1;
		return ;
	}
	if (shader->colors_count < 2)
		get_colors(line, shader, i, init);
	else
	{
		shader->err_flag =1;
		return (msg_error("The colors are alreday assigned\n", NULL));
	}
}
