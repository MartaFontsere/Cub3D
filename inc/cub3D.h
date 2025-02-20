/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/20 15:39:38 by yanaranj         ###   ########.fr       */
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

typedef struct s_path	t_path;

typedef struct s_color
{
	int			R;
	int			G;
	int			B;
	char		**split;
	t_path		*path;
}				t_color;

struct s_path
{
    char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			p_count;
	int			c_count;
	int			err_flag;
	t_color		C;
	t_color		F;
};

typedef struct s_map
{
	char		*rawmap;
    char    	**matrix;
    char    	**tmp_matrix;
	char		**void_matrix;
	char		*fd_path;
	int			is_map;
	size_t		c_width;
	size_t		c_height;
	int			j;
	int			init;
	int			open;
    t_path		path;
}           	t_map;


/*			--main--			*/
void    init_structs(t_map *map);
void	init_path(t_path *path);
void	print_matrix(char **matrix, int flag);
void	prints_check(t_map *map);


/*			--free_errors--			*/
void	exit_error(char *msg, int status);
void	msg_error(char *msg, char *msg2);
void	free_matrix(char **matrix);
void	clean_path(t_path *path);
void	clean_data(t_map *map);

/*				--read_fd--				*/
int		create_matrix(char *line, t_map *map);
void	assign_path(char *line, t_map *map, int i);
int		check_line(char *line, t_map *map, int i);
int		fd_is_correct(t_map *map);
int		read_file(int ac, char **av, t_map *map);


/*				--read_fd_utils--				*/
int		check_name(char *map_path);
char	*cpy_path(char *line, t_map *map);
int		curr_char(int cur, char *line, t_map *map);
size_t	ft_max_size(char *line, size_t max);
void	map_control(char *line, t_map *map);


/*				--read_colors--				*/
void	cpy_colors(char *rgb, t_color *color, int i);
void	get_colors(char *line, t_path *path, int i, int init);
void	assign_color(char *line, t_path *t_path, int i);


/*					--get_map--				*/
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);


/*				--get_map_utils--				*/
char	*cub_strdup(char *s1, size_t len);
char	**copy_map(char **map, size_t height);


/*				--parse_map--				*/
int		check_borders(char **matrix, int i, t_map *map);
int		check_esp(char **mapa, size_t x, size_t y, t_map *map);
int		check_zero(char **mapa, size_t x, size_t y, t_map *map);
int		is_close(char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		parse_map(char **matrix, t_map *map);


#endif
