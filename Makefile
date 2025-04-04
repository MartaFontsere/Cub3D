# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/04/04 03:11:12 by mfontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

NC = \033[0m
RED = \e[1;91m
GREEN = \e[1;92m
YELLOW = \e[1;93m
BLUE = \e[1;94m
TURQUOISE = \e[1;38;5;80m
PINK = \e[1;38;5;213m
FUCSIA = \e[1;38;5;201m
PURPLE = \e[1;38;5;135m
CYAN = \e[1;96m
LIME_GREEN = \e[1;38;5;118m
ORANGE = \e[1;38;2;255;128;0m

#------------------------------------------------VARIABLES---------------------------------------------------#

#---MANDATORY---# 

#Files
BASE_FILES = cub3D.c render.c 
INIT_FILES = initialitations.c init_map_minimap_params.c init_player_and_vision_params.c init_mlx_params.c init_textures_colors.c
RAYCAST_FILES = calculate_fov.c calculate_ray.c calculate_ray_utils.c 
MOVE_FILES = press_or_release_key.c move_player.c rotate_player.c check_collisions.c
PRINT_FILES = print_map.c print_walls.c print_utils.c textures.c
PARSE_FILES = parse_map.c parse_utils.c
READ_FILES = read_fd.c read_fd_utils.c read_fd_utils2.c read_colors.c get_map.c
ERROR_FILES = free_errors.c msg_errors.c
GNL_FILES = get_next_line.c get_next_line_utils.c

#Directories
INIT_DIR = initialitations/
RAYCAST_DIR = raycasting/
MOVE_DIR = movements/
PRINT_DIR = print_map/
PARSE_DIR = parsing/
READ_DIR = read/
ERROR_DIR = error/
GNL_DIR = ../libs/get_next_line/

#Sources
INIT_SRCS = $(addprefix $(INIT_DIR), $(INIT_FILES))
RAYCAST_SRCS = $(addprefix $(RAYCAST_DIR), $(RAYCAST_FILES))
MOVE_SRCS = $(addprefix $(MOVE_DIR), $(MOVE_FILES))
PRINT_SRCS = $(addprefix $(PRINT_DIR), $(PRINT_FILES))
PARSE_SRCS = $(addprefix $(PARSE_DIR), $(PARSE_FILES))
READ_SRCS = $(addprefix $(READ_DIR), $(READ_FILES))
ERROR_SRCS = $(addprefix $(ERROR_DIR), $(ERROR_FILES))
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))


FILES = $(BASE_FILES) $(INIT_SRCS) $(RAYCAST_SRCS) $(MOVE_SRCS) $(PRINT_SRCS) \
		$(PARSE_SRCS) $(READ_SRCS) $(ERROR_SRCS) $(GNL_SRCS)	

SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))


#---BONUS---# 

# Files 
B_BASE_FILES = cub3D_bonus.c render_bonus.c 
B_INIT_FILES = initialitations_bonus.c init_player_and_vision_params_bonus.c init_mlx_params_bonus.c init_map_minimap_bonus.c init_textures_colors_bonus.c
B_WALLS_RAYCAST_FILES = calculate_fov_bonus.c calculate_ray_bonus.c final_collision_coordinates.c calculate_ray_utils_bonus.c 
B_DOORS_RAYCAST_FILES = check_ray_opened_door_bonus.c door_raycasting_bonus.c door_raycasting_utils_bonus.c update_doors_status_bonus.c
B_FLOOR_RAYCAST_FILES = floor_raycasting_bonus.c
B_MOVE_FILES = press_or_release_key_bonus.c move_player_bonus.c rotate_player_bonus.c cursor_rotation_bonus.c check_collisions_bonus.c
B_PRINT_MAP_FILES = print_map_bonus.c print_walls_bonus.c print_doors_bonus.c print_sky_bonus.c print_sky_utils_bonus.c print_floor_bonus.c print_floor_utils_bonus.c print_utils_bonus.c textures_bonus.c
B_PRINT_MINI_FILES = print_fov_bonus.c print_minimap_bonus.c print_minimap_utils_bonus.c print_player_bonus.c print_vision_angle_bonus.c
B_DRAGON_FILES = do_dragon_animation_bonus.c
B_PARSE_FILES = parse_door_bonus.c parse_map_bonus.c parse_utils_bonus.c
B_READ_FILES = read_fd_bonus.c read_fd_utils_bonus.c read_fd_utils2_bonus.c read_colors_bonus.c read_colors_utils_bonus.c get_map_bonus.c
B_ERROR_FILES =  manage_errors_bonus.c
B_FREE_FILES = free_bonus.c free_sprites_bonus.c
B_GNL_FILES = get_next_line_bonus.c get_next_line_utils_bonus.c

# Directories
B_WALLS_RAYCAST_DIR = walls_raycasting/
B_DOORS_RAYCAST_DIR = doors_raycasting/
B_FLOOR_RAYCAST_DIR = floor_raycasting/
B_PRINT_MINI_DIR = print_minimap/
B_DRAGON_DIR = dragon/
B_FREE_DIR = free/

#Sources
B_INIT_SRCS = $(addprefix $(INIT_DIR), $(B_INIT_FILES))
B_WALLS_RAYCAST_SRCS = $(addprefix $(B_WALLS_RAYCAST_DIR), $(B_WALLS_RAYCAST_FILES))
B_DOORS_RAYCAST_SRCS = $(addprefix $(B_DOORS_RAYCAST_DIR), $(B_DOORS_RAYCAST_FILES))
B_FLOOR_RAYCAST_SRCS = $(addprefix $(B_FLOOR_RAYCAST_DIR), $(B_FLOOR_RAYCAST_FILES))
B_MOVE_SRCS = $(addprefix $(MOVE_DIR), $(B_MOVE_FILES))
B_PRINT_MAP_SRCS = $(addprefix $(PRINT_DIR), $(B_PRINT_MAP_FILES))
B_PRINT_MINI_SRCS = $(addprefix $(B_PRINT_MINI_DIR), $(B_PRINT_MINI_FILES))
B_DRAGON_SRCS = $(addprefix $(B_DRAGON_DIR), $(B_DRAGON_FILES))
B_PARSE_SRCS = $(addprefix $(PARSE_DIR), $(B_PARSE_FILES))
B_READ_SRCS = $(addprefix $(READ_DIR), $(B_READ_FILES))
B_ERROR_SRCS = $(addprefix $(ERROR_DIR), $(B_ERROR_FILES))
B_FREE_SRCS = $(addprefix $(B_FREE_DIR), $(B_FREE_FILES))


B_FILES = $(B_BASE_FILES) $(B_INIT_SRCS) $(B_WALLS_RAYCAST_SRCS) $(B_DOORS_RAYCAST_SRCS) $(B_MOVE_SRCS) $(B_PRINT_MAP_SRCS) \
		$(B_PRINT_MINI_SRCS) $(B_DRAGON_SRCS) $(B_PARSE_SRCS) $(B_READ_SRCS) $(B_ERROR_SRCS) $(B_FREE_SRCS) $(GNL_SRCS)	

B_SRCDIR = src_bonus/
B_SRCS = $(addprefix $(B_SRCDIR), $(B_FILES))

B_OBJDIR= objbonus/
B_OBJS = $(patsubst $(B_SRCDIR)%.c, $(B_OBJDIR)%.o, $(B_SRCS))


#---DEFINES---# 
INCLUDES = -I ./libs/Libft -I ./inc -I ./libs/get_next_line/

NAME = cub3D

HEADER = inc/cub3D.h inc/structs.h libs/get_next_line/get_next_line.h inc/cub3D_bonus.h inc/structs_bonus.h 

CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -Ofast 
CFLAGS += #-g -fsanitize=address

MLXDIR = libs/MLX42
LIBS = libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(patsubst $(DIR_BUILD)%,%,$@)"

$(B_OBJDIR)%.o: $(B_SRCDIR)%.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos

all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all --no-print-directory
	@cmake $(MLXDIR) -DDEBUG=1 -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 --no-print-directory

ifndef BONUS
${NAME}: ${OBJS} baby_dragon
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
else
${NAME}: ${B_OBJS} dragon
	@$(CC) $(CFLAGS) ${B_OBJS} $(LIBS) -o $(NAME)
endif

baby_dragon:
	@echo ""⠀⠀
	@echo "                   ⠀⠀         ⠀⠀$(YELLOW)⢀⣶⠀⠀$(PINK)⢀⣄ ⠀⠀⣠⣶⣾⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " 	             ⠀⠀⠀⠀  $(PINK)⢀⣼⡛$(YELLOW)⣆⣰⣿⣿$(PINK)⣠⠞⣓⣿⣿⠶⠞⠛⣫⣿⣷⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " $(RED) ⠈⣇      $(CYAN)DRACARYS        $(PINK)⣸⣿⡥⣿⡏⣸⡿⠛⠉⠉⠉⠉⠉⠓⢲$(YELLOW)⣠⠼⢱$(PINK)⣿⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀ $(RED)⣄ ⢻⡆                 $(BLUE)⢀⡴⠶⢿⡋⠀$(PINK)⠟⠛⠁$(BLUE)⣀⣀⣀⠀⠀⠀$(YELLOW)⠺⡷⠚⠉⢀⣾$(PINK)⣿⣶⣿⠗⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀ $(RED)⡽ ⢸$(ORANGE)⡿$(RED)⣆⠀⠀     $(RED)⠀$(CYAN)TEAM  ⠀ $(NC)⢸⡿⣷⣄$(BLUE)⠙⠀⠀$(BLUE)⢠⠞⢛⣿⣭⣙⠛⣦⡀$(YELLOW)⠹⣄⣀⡼⣻$(PINK)⣿⣯⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " $(RED)⠈⠀ ⡬$(ORANGE)⠃⠸$(RED)⡆  $(ORANGE)⡼⡄           $(NC)⢸⣧⡏⣿⠀⠀⠀$(NC)⢠⡞⠋⢹⡟⠟⢳$(BLUE)⠈⢧⠀$(BLUE)⠈⠙⠿⢻⠃$(PINK)⣷⠈⢻⣄⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀$(RED)  ⢸$(ORANGE)⠖$(YELLOW)⣸⡆$(RED)⣿⠀ 	⠀⠀⠀  ⠀$(BLUE)⣀$(NC)⣘⡦⠿⠟$(BLUE)⠲⠶⢤$(NC)⣼⠀⢹⣿⠁⠀⢨⡇$(PINK)⠀⠀⠀⠀⠀$(BLUE)⠉⠀$(PINK)⢿⣷⡾⣿⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀$(RED) ⣮$(ORANGE)⠅$(YELLOW)⡼⠋$(ORANGE)⢠$(RED)⡏    ⢠⡧	   ⠀$(BLUE)⠀⡾$(CYAN)⠹⠆$(BLUE)⠀⠀⠀⠀⠀⠀$(NC)⠈⠳⣼⣿⣷⣤⡾⠁$(PINK)⠀⠀⠀⠀⠀⠀⠀⣿⣏⠻⠟⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀$(RED)⢸$(ORANGE)⡟$(YELLOW)⢀⡄$(ORANGE)⣠$(RED)⠟⠀   ⢠$(ORANGE)⣟$(RED)⣇       $(BLUE)⠘⣧⣀⡀⠀⠀$(CYAN)⠐⠓⠀$(BLUE)⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀$(PINK)⠀⠀⠀⠀⠀⣰⠃⠘⣧⠀⠀⠀⠀$(CYAN)⢠⣄⠀⠀⠀"
	@echo "⠀$(RED)⠸$(ORANGE)⣇$(YELLOW)⠛$(ORANGE)⢰$(RED)⡏⠀⠀   ⡾$(ORANGE)⡏⠙$(RED)⣦⡀      $(BLUE)⠈⢯⡉⠙⢦⣀⠀⠀⠀⠀⠀⢀⣰⠏⠀⠀⠀⠀⠀⠀⠀$(PINK)⣶⣯⣤⢄⡿⠀⠀$(CYAN)⢀⣀⣠⣾⣏⠳⣄⠀⠀⠀"
	@echo "⠀$(RED) ⠙⢧$(ORANGE)⣘$(RED)⣧    ⢸$(ORANGE)⠃⠃$(YELLOW)⢠⡈$(RED)⢷    ⠀  $(BLUE)⠈⠹⢦⣀⣉⠒⠶⠶⠶⢶⣊⣡⣄⣀⣀⣀⣀⡤⠀⠀⠀$(PINK)⡿⠙⣯⣹$(CYAN)⠷⣚⣋⣉⣡⡴⠟⢦⠈⣷⠀⠀⠀"
	@echo "⠀$(RED)   ⠉⠛⠆   ⠘⠀⠀$(YELLOW)⠙⡃$(RED)⣸         $(BLUE)⠀⠀⠉⠙⠛⠛⠛⠛⠉⠀⠀⢹⣯⠉⠁$(CYAN)⢠⣄⡀⠀$(PINK)⢤⣤⣬⣿$(CYAN)⣟⠉⠉⠁⢠⠀⠀⠀⢳⡸⡆⠀⠀"
	@echo "⠀  $(RED)      ⠀⠀⢠$(ORANGE)⣴⡀$(RED)⢠⡏⠀⠀  ⠀⠀⠀⠀⠀⠀⠀⠀  ⠀$(BLUE)⠀⠀⠀⢀⡾⠋⠀⠀⠀$(CYAN)⢺⡇⠙⢷$(PINK)⣽⣧⣠⣿⠿$(CYAN)⢿⡉⠻⣾⣤⢤⣄⠀⣧⡇⠀⠀"
	@echo "     $(CYAN)IS     $(RED)⠻$(ORANGE)⣯$(RED)⠟⠀⠀   ⠀          $(BLUE)⠀⠀⢠⡟⢀⡼⠁⠀⠀$(CYAN)⠸⣇⢠⠘⢿$(PINK)⠙⢿⡏⠀$(BLUE)⠈⠹⣄⠀⠀$(CYAN)⠀⠈⢻⣿⠁⠀⠀"
	@echo "⠀		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀$(BLUE)⠀⠀⢸⣷⠞⠀⠀⠀⠀⠀$(CYAN)⡇⢸⣿⢸⠀$(PINK)⠘⣏⠉⠳⢤$(BLUE)⣘⣆⠀⠀$(CYAN)⠀⠘⠁⠀⠀"
	@echo "       $(CYAN) BACK⠀⠀⠀⠀    ⠀⠀⠀⠀⠀⠀⠀  ⠀$(BLUE)⠀⠀⠀⣸⠇⠀⠀⠀⠀⠀⠀$(CYAN)⣧⣾⣾⡟⠀⠀$(PINK)⠙⣶⣶⡦⠿⠛$(BLUE)⣧⠀⠀⠀⠀⠀"
	@echo "⠀		⠀ $(YELLOW)⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⢀⣀⣤⣄⣤⡏⠀⠀⠀⠀⠀⠀$(CYAN)⢰⣿⠟⠁⠀⠀⠀$(PINK)⠀⠛⣧⣀⡀$(BLUE)⠀⠸⣆⠀⠀⠀"
	@echo "⠀		 $(YELLOW)⣾⠛⢦⡀⠀⠀⠀⠀⠀$(BLUE)⣠⠞⠋⠉⠀⠈⣹⠃⠀⠀⠀⠀⠀$(CYAN)⢠⡿⠋⠀⠀⠀⠀⠀$(PINK)⠀⠀⢻⣌⣙⢦⠀$(BLUE)⠛⢷⡀⠀⠀"
	@echo "⠀	        $(YELLOW)⣸⡇⠀⠀⠙⢦⠀⠀⠀$(BLUE)⣼⠇⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(PINK)⠀⠀⠀⠈⣿⠋⠉⠁⠀$(BLUE)⠈⣷⠀⠀⠀"
	@echo "⠀		$(YELLOW)⣿⠀$(PINK)⢰⠻⡄$(YELLOW)⠈⢧⠀$(BLUE)⢰⡇⠀⠀⠀⠀⠀⠐⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(PINK)⠀⠀⠀⠀⠀⢠⣿⡄⠀$(BLUE)⠀⢠⠀⢸⡀⠀⠀"
	@echo "⠀		$(YELLOW)⢿⣤$(PINK)⣾⠀$(BLUE)⠻⢿⡛⠉⣇⠀⠀⠀⠀⠀⠀⠘⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(PINK)⣼⡃⣹⡆⠀$(BLUE)⠀⠈⡇⢸⠇⠀⠀"
	@echo "		⠀$(YELLOW)⠈⠉$(PINK)⠸⣆⢀$(BLUE)⣨⡻⣄⡸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣰⠆⠀⠀⠀⠀⠀⠀$(PINK)⢰⡿⠛⠉⠀$(BLUE)⠀⣸⠁⡾⠀⠀⠀"
	@echo "⠀		⠀⠀  ⢿⡄$(PINK)⠹⣿⣎$(BLUE)⡹⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡴⠋⠁⠀⠀$(PINK)⠠⣿⡉⠉⢓⡾⠁⠀$(BLUE)⠀⠀⢠⣿⠞⠀⠀⠀"
	@echo "⠀		⠀⠀  ⠈⢷⡀$(PINK)⠈⠳⣷⣴⣤$(BLUE)⠉⠛⠛⠒⠲⠶⠚⠛⠋⠀⠀$(PINK)⢸⣿⠓⢤⡀⢸⣿⡴⠛⠀⠀$(BLUE)⠀⠀⢠⡾⠁⠀⠀⠀"
	@echo "⠀		⠀⠀⠀  ⠀⠹⣦⠀$(PINK)⠈⠛⠮⡇⣠⡟⠓⣆⠀⢸⠏⠛⢶⠀⣾⣿⡤⠼⠃⠀$(BLUE)⠀⠀⠀⠀⠀⠀⣴⡟⠁⠀⠀⠀ "
	@echo "⠀	⠀	⠀⠀⠀⠀   ⠈⠳⣤⡀⠀⠀$(PINK)⠉⠙⠓⠻⠀⠛⠛⠒⠚⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⢀⣴⡾⠋⠀⠀⠀⠀⠀⠀"
	@echo "⠀		⠀⠀⠀⠀⠀⠀⠀  ⠈⠙⠶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⡶⠛⠉⠀⠀⠀$(GREEN)  CUB3D DONE$(BLUE)⠀⠀⠀"
	@echo "⠀⠀		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠈⠙⠛⠲⠦⢤⣤⣤⣤⣤⣤⣤⡶⠶⠚⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo ""⠀⠀⠀⠀⠀⠀

dragon:
	@echo "	⠀⠀⠀⠀⠀⠀⠀"⠀⠀
	@echo "	⠀⠀⠀⠀⠀⠀$(YELLOW)⣰⠂⠀$(BLUE)⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠀⠀⠀⠀⠀"⠀⠀⠀
	@echo "	⠀⠀⠀⠀⠀⠀$(YELLOW)⡟⢆$(BLUE)⢠⢣⠀$(YELLOW)  ⣔⡀⠀⠀ ⠀$(BLUE)⠀⡘⡇⠀⠀⠀⠀⠀⠀"⠀⠀
	@echo "	⠀⠀⠀⠀⠀⠀$(YELLOW)⠹⣦$(BLUE)⣹⢸⡆$(YELLOW)⠤⢀⠈⠙⠩⡉⠐⢄⠀$(BLUE)⢃⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀"⠀
	@echo "	⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⠹⠀⡷⣄$(YELLOW)⠢⡈⠑⠢⢌⢢⡀⠳$(BLUE)⠼⢔⠈⢆⠀⠀⠀⠀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⠀$(PINK)⠤⢞$(BLUE)⡆⠰⡙⢕⢤$(YELLOW)⠢⣄⠀⠑⢥⠀⠘$(BLUE)⢿⠆⠀⠱⠀"
	@echo "	⠀⠀⠀⠀⠀$(PINK)⢀⣤⡶⠮$(BLUE)⢧⡀⠑⡈⢢⣕⡄$(YELLOW)⢷⠀⠀⣱⣠⠉⠀$(BLUE)⢺⡄⢹⠀⠀⠀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⠀$(PINK)⢀⡸⠀$(BLUE)⠈⡗⢄⡈⢆⠙⠿⣶⣿⠿⢿⣷⣴⠉⠹⢶⢾⡆⠀⠀⠀"
	@echo "	⠀⠀⠀⠀$(PINK)⢠⠶⠿⡉⠉⠉⠙$(BLUE)⢻⣮⡙⢦⣱⡐⣌⠿⡄⢁⠄⠑⢤⣀⠐⢻⡇⠀⠀⠀"
	@echo "	⠀⠀⠀$(PINK)⢀⣠⠾⠖⠛⢻⠟⠁$(BLUE)⢘⣿⣆⠹⢷⡏⠀⠈⢻⣤⡆⠀⠑⢴⠉⢿⣄⠀⠀"
	@echo "	⠀⠀$(PINK)⢠⠞⢃⢀⣠⡴⠋⠀$(BLUE)⠈⠁⠉⢻⣷⣤⠧⡀⠀⠈⢻⠿⣿⡀⠀⢀⡀⣸⠀⠀"
	@echo "	⠀$(PINK)⠀⢀⠔⠋⠁⡰⠁⠀$(BLUE)⢀⠠⣤⣶⠞⢻⡙⠀⠀$(BLUE)⠙⢦⠀$(NC)⠈⠓$(BLUE)⢾⡟⡖⠊⡏⡟⠀⠀⠀"
	@echo "	$(PINK)⠀⢠⣋⢀⣠⡞⠁⠀⠀$(BLUE)⠔⣡⡾$(CYAN)⠋⠈⢆⡀$(BLUE)⢱⡀ ⠀⠀⠀⠀⠀⢿⡄⠀⢇⠇⠀⠀"
	@echo "	$(PINK)⠀⠎⣴⠛⢡⠃⠀⠀$(BLUE)⣴$(CYAN)⡏⠈⠢⣀⣸⣉⠦$(BLUE)⣬⠦⣀⠀⣄⠀⠀ ⠈⠃⠀⠀⠙⡀⠀"
	@echo "	$(PINK)⠀⡸⡁⣠⡆⠀⠀$(BLUE)⣾$(CYAN)⠋⠑⢄⣀⣠⡤⢕$(BLUE)⡶⠁⠀⠀⠁⢪⠑⠤⡀⠀ ⢰⡐⠂⠑⢀"
	@echo "	$(PINK)⠀⠏⡼⢋⠇⠀$(BLUE)⣸$(CYAN)⣟⣄⠀⠀⢠⡠⠓$(BLUE)⣿⠇⠀⠀⠀⠀⠀⠑⢄⡌⡆ ⢰⣷⣀⡀⢸"
	@echo "	$(PINK)⠀⣸⠁⢸⠀$(BLUE)⢀$(CYAN)⡿⡀⠀⠈⢇⡀⠗⢲$(BLUE)⡟⠅⠀⠀⠀⠀⠀⠀⠀⠹⡌⠢⣀ ⠀⣸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "	$(PINK)⠀⣧⠤⣼⠀$(BLUE)⢸$(CYAN)⠇⠉⠂⠔⠘⢄⣀⢼$(BLUE)⠃⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠚⠳⡤⠋⠀$(RED)⠈⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "	$(PINK)⠐⠇⣰⢿⠀$(CYAN)⣾⢂⣀⣀⡸⠆⠁⠀⣹⠀$(BLUE)⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠠⣀$(ORANGE)⢏⠺⢮$(RED)⡒⠤⠄⠀⠀⠀  ⠀⢰⠿⣷⣆⠀"
	@echo "	⠀$(PINK)⢀⡏⣸⠀$(CYAN)⣟⠁⠀⠙⢄⠼⠁⠈⢺⠀$(BLUE)⠘⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠀⠿⡺⣦$(ORANGE)⠘⢷⣄⡄   ⠀⠀⠀⢀⢀⡿⣿⡶⡷⠤⠀⠀⠀"
	@echo "	$(PINK)⠀⠈⡏⣸$(BLUE)⢰$(CYAN)⡯⠆⢤⠔⠊⢢⣀⣀⡼$(BLUE)⡇⠀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED) ⠀⠽$(ORANGE)⢷⣄⡙⠻⣷⣷⣤⣤⣤⣾⡾⢫⣿⣽⣳⣶⣶⣄⠀⠀⠀"
	@echo "	$(PINK)⠀⠀⢠⢻$(BLUE)⢸$(CYAN)⡇⠀⠀⠑⣤⠊⠀⠀⠈$(BLUE)⣧⠀⠀⠙⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  $(RED)⠀⢸$(ORANGE)⠘⣿⡔$(YELLOW)⠆         ⣄⣀$(ORANGE)⡹⣾⣿⡇⠀⠀⠀⠀⠀⠀"
	@echo "	⠀$(PINK)⠀⠸⣼$(BLUE)⢸$(CYAN)⠟⠑⠺⡉⠈⢑⠆⠠⠐⢻$(BLUE)⡄⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠸$(YELLOW)⣿ $(CYAN)DRACARYS$(ORANGE) $(YELLOW)⢶⣟$(ORANGE)⣿⣳⡏⠀⠀⠀⠀⠀⠀⠀"
	@echo "	⠀⠀$(PINK)⠀⡟$(BLUE)⣸$(CYAN)⡀⠀⠀⣈⣶⡁⠀⠀⠀⢠$(BLUE)⢻⡄⠀⠀⠀⠑⠤⣄⡀⠀⠀⠀⠀⠀⠀$(RED)⢀⣀⡀⠀⠀$(ORANGE)⢠$(YELLOW)⣿⡇   $(CYAN)IS $(YELLOW)   ⠈⠳ $(ORANGE)⣿⢿⠋$(RED)⢤⠀⠀⠀"
	@echo "	⠀⠀$(PINK)⢰⠁$(BLUE)⣿$(CYAN)⡿⠟⢏⠁⠀⢈⠖⠒⠊⠉⠉⠹$(BLUE)⣄⠀⠀⠀⠀⠀⠈⠑⠢⡀⠀⠀⠀$(RED)⢿⣧$(ORANGE)⣀⣀⣤⣿⡿$(YELLOW)⠂ $(CYAN) BACK $(YELLOW)⣀⣠⣡⠀$(ORANGE)⢺⡿⡇⠀$(RED)⢀⠀⠀"
	@echo "	⠀$(PINK)⣀⠟$(BLUE)⢰$(CYAN)⡇⠀⠀⠈⢢⡴⠊⠀⠀⠀⠀⠀⣸⢙$(BLUE)⣷⢄⣀⡠⠤⠤⠒⠒⠚⠀⠀⠀$(ORANGE)⠈⠻⣿⢿⣻⣽$(YELLOW)⡑        ⠀$(ORANGE)⠛⢿⣻⣦⣼⢷⡇⠀$(RED)⠘⠆⠀⠀"
	@echo "	$(PINK)⠘⠹⠤$(BLUE)⠛$(CYAN)⠛⠲⢤⠐⠊⠈⠂⢤⢀⠠⠔⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⣀⠀⠀$(ORANGE)⠿⢻⣿⣻$(YELLOW)⡿⡇⠀⢨⠊⢵⡄⣁⠢⣍⠶⣄$(ORANGE)⢹⣟⣽⣿⠀⠀⠀$(RED)⣤⠀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⠀$(CYAN)⠣⢀⡀⠔⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠈⢀⣠⠀$(ORANGE)⢸⣿⠋⣿$(YELLOW)⢧⡀⠺⣥⣴⣖⣉⣿⢿⣄⡚$(ORANGE)⢸⣯⡿⣾⡷⣶⣶$(RED)⣿⠀⠀⠀"
	@echo "				    $(RED)⠈⠁⠀⠀⠛⠷$(ORANGE)⠙⠿⠿⠿⢯⣿⡏$(YELLOW)⢻⣯⢻⣯⠉$(ORANGE)⢸⣷⠀⠈⠙⠛⠊⠁⠀⠀"
	@echo "	$(GREEN)  CUB3D BONUS DONE  	          ⠀   ⠀$(RED)⠐⠛⠃$(ORANGE)⣼⣿$(YELLOW)⡿⣟⣗$(ORANGE)⠈⠿⣷⣤⣠⣤⣦$(RED)⣶⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⢻⡿⣽⣾$(YELLOW)⢿⣷⣦⣶⢾$(ORANGE)⣯⠗⠉⠀$(RED)⠙"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⠈⠑⠉⠛⠾⠽⠋⠛⠊⠉⠀⠀⠀⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠐⠆⢀⡀⠀⠀⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠈⠛⠁⠀⠀⠀⠀⠀⠀"
	@echo ""

bonus: 
	@$(MAKE) BONUS=42 --no-print-directory

clean:
	@${RM} ${OBJDIR} ${B_OBJDIR}
	@make -C libs/Libft clean --no-print-directory
	@make -C $(MLXDIR)/build clean --no-print-directory
	@echo "$(RED)CUB3D OBJECTS DELETED$(NC)"

fclean:
	@${RM} ${OBJDIR} ${B_OBJDIR}
	@echo "$(RED)CUB3D OBJECTS DELETED"
	@${RM} ${NAME}
	@make -C libs/Libft fclean --no-print-directory
	@rm -rf $(MLXDIR)/build
	@echo "$(RED)CUB3D EXEC DELETED"
	@echo "$(ORANGE)"
	@echo "	⠀⠀⠀⠀⠀⠀⢱⣆⠀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⠈⣿⣷⡀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣧⠀⠀⠀"
	@echo "	⠀⠀⠀⠀⡀⢠⣿$(YELLOW)⡟⣿$(ORANGE)⣿⣿⡇⠀"
	@echo "	⠀⠀⠀⠀⣳⣼⣿$(YELLOW)⡏⢸$(ORANGE)⣿⣿⣿⢀⠀"
	@echo "	⠀⠀⠀⣰⣿⣿$(YELLOW)⡿⠁⢸$(ORANGE)⣿⣿⡟⣼⡆"
	@echo "	⢰⢀⣾⣿$(YELLOW)⣿⠟⠀⠀⣾⢿$(ORANGE)⣿⣿⣿⣿"
	@echo "	⢸⣿⣿$(YELLOW)⣿⡏⠀⠀⠀⠃⠸⣿$(ORANGE)⣿⣿⡿"
	@echo "	⢳⣿⣿$(YELLOW)⣿⠀⠀⠀⠀⠀⠀⢹⣿$(ORANGE)⡿⡁"
	@echo "	⠀⠹⣿$(YELLOW)⣿⡄⠀⠀⠀⠀⠀⢠⣿$(ORANGE)⡞⠁"
	@echo "	⠀⠀⠈⠛$(YELLOW)⢿⣄⠀⠀⠀⣠⠞$(ORANGE)⠋⠀⠀"
	@echo "	⠀⠀⠀⠀⠀$(YELLOW)⠉ "
	@echo ""

re: fclean all
	@echo "$(RED)CUB3D RE DONE"

bonus_re: fclean bonus
	@echo "$(RED)CUB3D_BONUS RE DONE"

.PHONY: all clean fclean re⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
