/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/31 12:02:56 by yanaranj         ###   ########.fr       */
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

/*MAP*/
#define MAP_PX_WIDTH 2560
#define MAP_PX_HEIGHT 1440

typedef struct s_path	t_path;

typedef struct s_color
{
	int			R;
	int			G;
	int			B;
	char		**split;
	int			assigned;
	int			is_path;//decimos que C || F tienen path en lugar del RGB
	char		*color_path;//guardamos el path de la textura
	t_path		*path;
}				t_color;

struct s_path
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*tmp_str;
	int			p_count;
	int			c_count;
	int			err_flag;
	t_color		C;
	t_color		F;
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

typedef struct s_texture 
{
	t_path 		path;
	//t_image 	north_wall_img;
	//t_image 	south_wall_img;
	//t_image 	west_wall_img;
	//t_image 	east_wall_img;
	//int 		C_hex_color; // Color transformado a hexadecimal
	//int 		F_hex_color; // Color transformado a hexadecimal

	//BONUS
	//t_image 	sky_img;
	//t_image 	floor_img;
	//t_image  	door_img;
	//t_image 	dragon_img[4];
} 				t_texture;

typedef struct s_game
{
	t_texture 		texture;
	//t_player		player;
	t_map			map;
	//t_minimap 		minimap;
	//t_vision 		vision;
	//t_collision 	collision;
	//t_print 		print_map;
	//t_mlx			mlx; 
	int 			finish_game;
}					t_game;

//void	print_dirs(char **matrix, int i, int j, int end);

//-------------------------------------------------
//					MAIN
//-------------------------------------------------
void	init_map_params(t_game *gdata, t_map *map);
void	init_textures_and_colors_path(t_texture *texture, t_path *path);

//-------------------------------------------------
//				FREE/ERRORS
//-------------------------------------------------
void	exit_error(char *msg, int status);
void	free_matrix(char **matrix);
void	clean_path(t_path *path);
void	clean_data(t_game *gdata);
void	free_map_sprites(t_game *gdata, t_texture *texture);
/*msg error*/
void	msg_error(char *msg, char *msg2);

//-------------------------------------------------
//					READ_FD
//-------------------------------------------------
int		create_matrix(char *line, t_map *map);
void	assign_path(char *line, t_path *path, int i);
int		check_line(char *line, t_path *path, t_map *map, int i);
int		fd_is_correct(t_game *gdata, t_map *map);
int		read_file(int ac, char **av, t_game *gdata,t_map *map);

//------------------------------------------------
//					READ_FD_UTILS
//------------------------------------------------
int		check_name(char *map_path);
char	*cpy_path(char *line, t_path *path, int pos, int i);
int		curr_char(int cur, char *line, t_path *path);
int		ft_max_size(char *line, int max);
void	map_control(char *line, t_map *map, t_path *path, int i);

//------------------------------------------------
//					READ_COLORS
//------------------------------------------------
void	get_colors(char *line, t_path *path, int i, char c);
void	get_color_path(char *line, t_color *color, int i);
void	control_c_values(char *line, t_path *path, int init_val, char c);
void	control_f_values(char *line, t_path *path, int init_val, char c);
void	assign_color(char *line, t_path *path, int i);

	//UTILS READ
void	cpy_colors(char *rgb, t_color *color, int i);
char	*clean_str(char *src, int start, int end, t_path *path);
//------------------------------------------------
//						GET_MAP
//------------------------------------------------
char	*cub_strdup(char *s1, int len);
char	**copy_map(char **map, int height);
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);

//------------------------------------------------
//					PARSE_MAP
//------------------------------------------------
int		check_borders(char **matrix, int i, t_map *map);
int		is_close(char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		parse_map(t_game *gdata, char **matrix, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS
//------------------------------------------------
void	check_n_line(char **src, t_map *map);
int		check_esp(size_t i, size_t j, t_map *map);
int		check_zero(size_t i, size_t j, t_map *map);
int		check_player(size_t i, size_t j, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS2
//------------------------------------------------
int		is_door(size_t i, size_t j, t_map *map);
int		check_y_pos(int i, int j, t_map *map);
int		check_x_pos(int i, int j, t_map *map);

#endif