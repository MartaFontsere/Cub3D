/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/15 16:16:53 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
#include "../libs/Libft/libft.h"

/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define GREEN "\e[1;92m"
# define CYAN "\e[1;96m"
# define PURPLE "\e[1;95m"
# define ORANGE "\e[1;38;2;255;128;0m"

/*STANDARD*/
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_map
{
    void    *mlx;//se inicia al iniciar game(para evitar segv)
    void    *window;
    char    **map;
	char	*raw_map;
    int		heigth;
	int		width;
    int     nexit;
    //t_img   img;
}           t_map;

/* typedef struct s_img
{
    int		img_w;
	int		img_h;
	int		i;
	int		j;
}			t_img; */

/*			--parsing--			*/
char	**get_final_map(int ac, char **av, t_map *map);
int     check_name(char *name);
void	exit_error(char *msg, int status);

/*			--inits--			*/
void    init_map_values(t_map *map);

#endif
