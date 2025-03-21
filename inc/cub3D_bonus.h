/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/21 12:08:42 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../libs/Libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

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

typedef struct s_path	t_path;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	char		**split;
	int			assigned;
	int			is_path;//decimos que C || F tienen path en lugar del RGB
	char		*color_path;//guardamos el path de la textura
	t_path		*path;
}				t_color;

struct s_path
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*tmp_str;
	int			p_count;
	int			c_count;
	int			err_flag;
	t_color		c;
	t_color		f;
};

typedef struct s_map
{
	char		**matrix;
	char		**tmp_matrix;
	char		**void_matrix;
	char		*fd_path;
	char		pos;
	int			is_map;
	size_t		c_width;
	size_t		c_height;
	int			j;
	int			init;
	int			open;
	t_path		path;
}				t_map;

void	print_dirs(char **matrix, int i, int j, int end);

//-------------------------------------------------
//					MAIN
//-------------------------------------------------
void	init_structs(t_map *map);
void	init_path(t_path *path);

//-------------------------------------------------
//				FREE/ERRORS
//-------------------------------------------------
void	exit_error(char *msg, int status);
void	msg_error(char *msg, char *msg2);
void	free_matrix(char **matrix);
void	clean_path(t_path *path);
void	clean_data(t_map *map);

//-------------------------------------------------
//					READ_FD
//-------------------------------------------------
int		create_matrix(char *line, t_map *map);
void	assign_path(char *line, t_map *map, int i);
int		check_line(char *line, t_map *map, int i);
int		fd_is_correct(t_map *map);
int		read_file(int ac, char **av, t_map *map);

//------------------------------------------------
//					READ_FD_UTILS
//------------------------------------------------
int		check_name(char *map_path);
char	*cpy_path(char *line, t_map *map, int pos);
int		curr_char(int cur, char *line, t_map *map);
size_t	ft_max_size(char *line, size_t max);
void	map_control(char *line, t_map *map, int i);

//------------------------------------------------
//					READ_COLORS
//------------------------------------------------
//void	cpy_colors(char *rgb, t_color *color, int i);
//void	get_colors(char *line, t_path *path, int i, int init);
//void	assign_color(char *line, t_path *t_path, int i);
void	assign_color(char *line, t_path *path, int i);
void	control_c_values(char *line, t_path *path, int init_val, char c);
void	control_f_values(char *line, t_path *path, int init_val, char c);
void	get_color_path(char *line, t_color *color, int i);
void	get_colors(char *line, t_path *path, int i, char c);

	//UTILS READ
void	cpy_colors(char *rgb, t_color *color, int i);
char	*clean_str(char *src, int start, int end, t_path *path);



//------------------------------------------------
//						GET_MAP
//------------------------------------------------
char	*cub_strdup(char *s1, size_t len);
char	**copy_map(char **map, size_t height);
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);

//------------------------------------------------
//					PARSE_MAP
//------------------------------------------------
int		check_borders(char **matrix, int i, t_map *map);
int		is_close(char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		parse_map(char **matrix, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS
//------------------------------------------------
void	check_n_line(char **src, t_map *map);
int		check_esp(size_t x, size_t y, t_map *map);
int		check_zero(size_t x, size_t y, t_map *map);
int		check_player(size_t x, size_t y, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS2
//------------------------------------------------
int		is_door(size_t x, size_t y, t_map *map);
int		check_y_pos(int x, int y, t_map *map);
int		check_x_pos(int x, int y, t_map *map);

#endif
