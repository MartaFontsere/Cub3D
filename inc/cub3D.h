/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 01:17:11 by mfontser         ###   ########.fr       */
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
# define DARK_GREY 0x000000
# define SOFT_GREY 0x959595FF
# define RED1 0xFF0000FF

/*PLAYER ORIENTATION*/
# define NORTH 90
# define SOUTH 270
# define EAST 0
# define WEST 180

/*MINIMAP*/
# define PLAYER_RADIUS 15 // lo que ocupara el player en el minimapa
//# define WALL_SIZE 100

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
	//t_images	*images;
}				t_mlx;

typedef struct s_player
{
	int			x; // Posición Inicial del Personaje en X (en casillas)
	int			y; // Posición Inicial del Personaje en Y (en casillas)
	double		cell_x; //Posición en x dentro de la casilla (en casillas)
	double 		cell_y; //Posición en y dentro de la casilla (en casillas)
		//Consideramos que cada casilla es una unidad, como lo queremos centrado necesitamos que esté en el 0,5 tanto de x como de y, por eso necesito que sea double 
	int			orientation; // Orientacion Inicial que apunta el Persoanje
	double		vision_angle; // Orientacion en grados de la vision del personaje. ira girando en tramos mas pequeños que enteros, es decir, con decimales, por eso es double
}				t_player;

typedef struct s_minimap
{
	mlx_image_t		*background_img;
	int				width; // Valor máximo X del minimapa (en pixels)
	int				height; // Valor máximo Y del minimapa (en pixels)

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
}					t_game;

//??? En base a que decidir si las variables las creas como puntero o la variable en si

//INITIALITATIONS
void	init_gdata_values(t_game *gdata);
void	init_player_position(t_map *map_info, t_player *player);
void	init_player_orientation(t_map *map_info, t_player *player);
int	init_mlx(t_game *gdata, t_mlx *mlx);

//PSEUDOPARSING
char **parsing_pre_yahaira(t_game *gdata);

//PRINT MINIMAP
void	print_minimap(t_game *gdata);

//RENDER
void render_game (void *param);


//ERROR
void	write_error(const char *str);

#endif