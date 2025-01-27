/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/27 17:58:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/Libft/libft.h"
//# include "sprites.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>


/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define TURQUOISE "\e[1;38;5;80m"
# define PINK "\e[1;38;5;213m"
# define FUCSIA "\e[1;38;5;201m"
# define PURPLE "\e[1;38;5;135m"
# define CYAN "\e[1;96m"
# define LIME_GREEN "\e[1;38;5;118m"
# define ORANGE "\e[1;38;2;255;128;0m"


/*MLXCOLORS*/
# define BLACK 0x000000FF
# define DARK_GREY 0x000000
# define MEDIUM_GREY 0X696969FF
//# define MEDIUM_GREY 0X575757FF
# define SOFT_GREY 0x959595FF
# define RED1 0xFF0000FF
# define YELLOW1 0xFFFF00FF // el FF final es maxima opacidad


/*PLAYER ORIENTATION*/
# define NORTH M_PI / 2 //90 grados
# define SOUTH 3 * M_PI / 2 // 270 grados
# define EAST 0 //0 grados
# define WEST M_PI //180 grados




/*MOVE*/
# define MOVE_RIGHT 0
# define MOVE_LEFT 1
# define MOVE_UP 2
# define MOVE_DOWN 3

/*PLAYER SPEED*/
# define MOVE_SPEED 4 // cuantos pixeles se mueve cada vez
# define ROTATION_SPEED 0.4

/*MINIMAP*/




//DEFINIR TAMAÑO DE VENTANA DE LAS CASILLAS CORRESPONDIENTES * 64 PIXELES (encontrar el mapa maximo)
//ALTURA DEL PLAYER DE 32 PIXELES
//PROJECTION PLANE DE 320 DE ANCHO Y 200 DE ALTO
/*
Dimension of the Projection Plane = 320 x 200 units
Center of the Projection Plane = (160,100)
Distance to the Projection Plane = 277 units
Angle between subsequent rays = 60/320 degrees*/

typedef struct s_images
{
	xpm_t		*xpm;
	mlx_image_t	*data;
}				t_images;

typedef struct s_mlx
{
	mlx_t		*init;
	int			window_height;
	int			window_width;
	mlx_image_t	*image;
}				t_mlx;

typedef struct s_ray
{
	double		vision_angle; // Orientacion Inicial en grados de la vision del personaje
	double 		FOV; //Field Of View

} 	t_ray;

typedef struct s_player
{
	int			raw_x; // Posición Inicial del Personaje en X (en casillas)
	int			raw_y; // Posición Inicial del Personaje en Y (en casillas)
	double		x; // Posición Inicial del Personaje en X (en pixeles para minimapa)
	double		y; // Posición Inicial del Personaje en Y (en pixeles para minimapa)
	double 	midle_x; // Posición del Personaje centrado en la casilla en X (en pixeles para minimapa)
	double 	midle_y; // Posición del Personaje centrado en la casilla en Y (en pixeles para minimapa)
	double  	radius; // radio del circulo que representara el personaje
	
	
	t_ray 		ray;
	int  		speed; // Cuantos pixeles se desplaza cada vez que tocamos una tecla
	int  		mov_right;
	int  		mov_left;
	int  		mov_up;
	int 		mov_down;
	int  		rotate_right;
	int 		rotate_left;

}				t_player;

typedef struct s_minimap
{
	//mlx_image_t		*background_img;
	int				width; // Valor máximo X del minimapa (en pixels)
	int				height; // Valor máximo Y del minimapa (en pixels)
	double 			cell_width; // Cantidad de pixels en el eje X
	double 			cell_height; //Cantidad de pixels en el eje Y
}					t_minimap;

typedef struct s_map
{
//	char			*north;
//	char			*south;
//	char			*west;
//	char			*east;
	// char			*raw_floor;
	// char			*raw_ceiling;
	// uint32_t		floor;
	// uint32_t		ceiling;
	char			*rawmap; // Mapa sin procesar
	char			**matrix; // Mapa en matriz
	int				width; // Valor máximo X del mapa (en casillas)
	int				height; // Valor máximo Y del mapa (en casillas)
}					t_map;


typedef struct s_game
{
	t_map			map;
	t_player		player;
	t_minimap 		minimap;

	t_mlx			mlx; // ???en funcion de que hacerlo puntero o no?
	int 			finish_game;
}					t_game;

//??? En base a que decidir si las variables las creas como puntero o la variable en si

//MAIN
void	close_window(t_game	*gdata);

//INITIALITATIONS
void	init_gdata_values(t_game *gdata);
void	init_minimap(t_game *gdata, t_map *map);
void 	init_player_parameters (t_game *gdata, t_player *player);
void	init_player_position(t_game *gdata, t_map *map_info, t_player *player);
void	init_player_orientation(t_map *map_info, t_player *player);
int		init_mlx_and_create_new_image(t_game *gdata, t_mlx *mlx);

//PSEUDOPARSING
char **parsing_pre_yahaira(t_game *gdata);

//PRINT MINIMAP
void	print_minimap(t_game *gdata);

void print_empty_space (t_mlx mlx, t_minimap minimap, t_map map);
void print_walls (t_mlx mlx, t_minimap minimap, t_map map);
void print_background (t_mlx mlx, t_minimap minimap);

//PRINT PLAYER PARAMS
void print_player (t_game *gdata, t_player player, double x, double y, int color);
void print_vision_angle (t_game *gdata, t_player player, double x, double y, int color);

//RENDER
void render_game (void *param);

//MOVE
void	prepare_movement(t_game *gdata, double *target_x, double *target_y);
void rotate_player(t_player *player);
void	print_player_move(t_game *gdata, t_player player, double target_x, double target_y);
void print_player_view (t_game *gdata, t_player player, double target_x, double target_y);

//PRESS KEY
int	there_is_a_key_pressed(t_game *gdata);
void	press_key(mlx_key_data_t keydata, void *param);
void	set_mov_params(t_game *gdata, int *move_direction);
void	reset_mov_params(t_game *gdata);
void	release_key(mlx_key_data_t keydata, t_game *gdata);

//COLLISIONS
int	can_i_move_to(t_game *gdata, double target_x, double target_y);
int	check_down_move(t_game *gdata, double target_y, double target_x);
int	check_up_move(t_game *gdata, double target_y, double target_x);
int	check_left_move(t_game *gdata, double target_y, double target_x);
int	check_right_move(t_game *gdata, double target_y, double target_x);

//ERROR
void	write_error(const char *str);

#endif