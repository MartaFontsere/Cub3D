/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/24 18:29:25 by yanaranj         ###   ########.fr       */
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
    //void    *mlx;//se inicia al iniciar game(para evitar segv)
    //void    *window;
	char	*rawmap;
    char    **matrix;
    char    **tmp_matrix;
	char	*fd_path;
    int		heigth;
	int		width;
	size_t	line_size;
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

/*			--main--			*/
void    init_map_values(t_map *map);
void	print_matrix(char **matrix, int flag);


/*			--fill_matrix--			*/
char	*fill_void(t_map *map);
int		complete_matrix(char **src, t_map *map);

/*			--free_errors--			*/
void	exit_error(char *msg, int status);
void	free_matrix(char **matrix);
void	clean_data(t_map *map);

/*			--get_matrix--			*/
char	*get_rawmap(char *path, t_map *map);
int		get_final_map(int ac, char **av, t_map *map);


/*			--get_matrix_utils--			*/
int		check_name(char *map_path);
int		min_chars(char *rawmap);
int		count_fd_line(char *map_path, t_map *map);
size_t	ft_max_size(char *line, size_t max);



#endif
