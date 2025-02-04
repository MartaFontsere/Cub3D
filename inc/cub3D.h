/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/04 14:17:13 by yanaranj         ###   ########.fr       */
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

typedef struct s_shader	t_shader;

typedef struct s_color
{
	int			R;
	int			G;
	int			B;
	char		**split;
	t_shader	*shader;
}				t_color;

struct s_shader
{
    char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			count;
	int			colors_count;
	int			err_flag;
	t_color		C;//luego hay que chekear los rangos RGB
	t_color		F;
};

typedef struct s_map
{
	char		*rawmap;
    char    	**matrix;
    char    	**tmp_matrix;
	char		*fd_path;
	int			is_map;
	size_t		map_width;
	size_t		map_height;
    t_shader	shader;
}           	t_map;

/* typedef struct s_img
{
    int		img_w;
	int		img_h;
	int		i;
	int		j;
}			t_img; */
/*			--main--			*/

void    init_structs(char **av, t_map *map);
void	init_shader(t_shader *shader);
void	init_shader(t_shader *shader);
void	print_matrix(char **matrix, int flag);


/*			--free_errors--			*/
void	exit_error(char *msg, int status);
void	msg_error(char *msg, char *msg2);
void	free_matrix(char **matrix);
void	clean_shader(t_shader *shader);
void	clean_data(t_map *map);

/*				--read_fd--				*/
char	*cpy_path(char *line, t_map *map);
void	assign_path(char *line, t_map *map, int i);
int		check_line(char *line, t_map *map);
int		fd_is_correct(t_map *map);


/*				--read_colors--				*/
void	get_colors(char *line, t_shader *shader, int i, int init);
void	assign_color(char *line, t_shader *t_shader, int i);
void	cpy_colors(char *rgb, t_color *color, int i);



/*					--get_map--				*/
int	get_final_map(int ac, t_map *map);
void	start_map(char *line, t_map *map, int i);



/*				--get_map_utils--				*/
int	check_name(char *map_path);




#endif
