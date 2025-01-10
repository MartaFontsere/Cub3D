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
// # define DARK_GREY "0xFC7A00FF"
// # define SOFT_GREY "0x00DADAFF"

/*ORIENTATION*/
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

/*MINIMAP*/
# define PLAYER_RADIUS 15
# define WALL_SIZE 100

typedef struct s_images
{
	xpm_t		*xpm;
	mlx_image_t	*data;
}				t_images;

typedef struct s_mlx
{
	mlx_t		*init;
	t_images	*images;
}				t_mlx;

typedef struct s_player
{
	int			x; // Posición Inicial del Personaje en X
	int			y; // Posición Inicial del Personaje en Y 
	int			orientation; // Orientacion Inicial que apunta el Persoanje
}				t_player;

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
	char			**map; // Mapa en matriz
	int				map_width; // Valor máximo X del mapa
	int				map_height; // Valor máximo Y del mapa
}					t_map;


typedef struct s_game
{
	t_map			map_info;
	t_player		player;
	int				window_height;
	int				window_width;
	t_mlx			mlx; // ???en funcion de que hacerlo puntero o no?
	mlx_image_t		*txt_image; //??? idem. y esto para que era???
}					t_game;


//??? En base a que decidir si las variables las creas como puntero o la variable en si

#endif