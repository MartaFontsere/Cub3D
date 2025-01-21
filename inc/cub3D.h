/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/21 20:16:06 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
#include "../libs/Libft/libft.h"
#include "../src/get_next_line/get_next_line.h"

/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define GREEN "\e[1;92m"
# define CYAN "\e[1;96m"
# define PURPLE "\e[1;95m"
# define ORANGE "\e[1;38;2;255;128;0m"

# define ERR 6 "Invalid map\n"
/*STANDARD*/
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_map
{
    void    *mlx;//se inicia al iniciar game(para evitar segv)
    void    *window;
	char	*raw_map;
    char    **my_map;//una vez hecho el parseo, volvemos a splitear el  raw_map
    int		heigth;
	int		width;
    int     nexit;
    int		pos_h;//para floodfill
	int		pos_w;
	size_t	line_size;//line max
	int		fd_lines;
    //t_img   img;
}           t_map;

/* typedef struct s_img
{
    int		img_w;
	int		img_h;
	int		i;
	int		j;
}			t_img; */

/*			--parsing_map--			*/
int		num_strchr(char *str, char c);
int		min_chars(char *raw_map);
int     final_map(char **my_map, t_map *map, char *raw_map);


/*			--fill_map--			*/
char	*fill_void(char *line, t_map *map);
size_t	ft_max_size(char *line, size_t max);
//char	**copy_map(char **my_map, size_t height, t_map *map);


/*			--getting_map--			*/
int     check_name(char *name);
//char	*get_raw_map(char *map_path);
char	**complete_map(char *map_path, t_map *map);
char	**get_final_map(int ac, char **av, t_map *map);
int		count_fd_line(char *map_path, t_map *map);

/*			--errors--			*/
void	exit_error(char *msg, int status);
void	free_matrix(char **matrix);

/*			--inits--			*/
void    init_map_values(t_map *map);

#endif
