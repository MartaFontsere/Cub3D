# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/03/27 16:46:29 by mfontser         ###   ########.fr        #
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

# MANDATORY
# Directories
INIT_DIR = initialitations/
RAYCAST_DIR = raycasting/
MOVE_DIR = movements/
PRINT_DIR = print_map/
PARSE_DIR = parsing/
READ_DIR = read/
ERROR_DIR = error/
GNL_DIR = ../libs/get_next_line/

# Files by directory
BASE_FILES = cub3D.c render.c 
INIT_FILES = initialitations.c init_map_minimap_params.c init_player_and_vision_params.c init_print_params.c init_mlx_params.c
RAYCAST_FILES = calculate_fov.c calculate_ray.c calculate_ray_utils.c 
MOVE_FILES = press_or_release_key.c move_player.c rotate_player.c check_collisions.c
PRINT_FILES = print_map.c print_walls.c print_utils.c textures.c
PARSE_FILES = parse_map.c parse_utils.c
READ_FILES = read_fd.c read_fd_utils.c read_fd_utils2.c read_colors.c get_map.c
ERROR_FILES = free_errors.c msg_errors.c
GNL_FILES = get_next_line.c get_next_line_utils.c

# Relacion de los directories con sus respectivos files
INIT_SRCS = $(addprefix $(INIT_DIR), $(INIT_FILES))
RAYCAST_SRCS = $(addprefix $(RAYCAST_DIR), $(RAYCAST_FILES))
MOVE_SRCS = $(addprefix $(MOVE_DIR), $(MOVE_FILES))
PRINT_SRCS = $(addprefix $(PRINT_DIR), $(PRINT_FILES))
PRINT_MINI_SRCS = $(addprefix $(PRINT_MINI_DIR), $(PRINT_MINI_FILES))
PARSE_SRCS = $(addprefix $(PARSE_DIR), $(PARSE_FILES))
READ_SRCS = $(addprefix $(READ_DIR), $(READ_FILES))
ERROR_SRCS = $(addprefix $(ERROR_DIR), $(ERROR_FILES))
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))

# Todos los files con su respectivo path
FILES = $(BASE_FILES) $(INIT_SRCS) $(RAYCAST_SRCS) $(MOVE_SRCS) $(PRINT_SRCS) \
		$(PRINT_MINI_SRCS) $(PARSE_SRCS) $(READ_SRCS) $(ERROR_SRCS) $(GNL_SRCS)	


# BONUS
# Directories
B_INIT_DIR = initialitations/
B_WALLS_RAYCAST_DIR = walls_raycasting/
B_DOORS_RAYCAST_DIR = doors_raycasting/
B_MOVE_DIR = movements/
B_PRINT_MAP_DIR = print_map/
B_PRINT_MINI_DIR = print_minimap/
B_DRAGON_DIR = dragon/
B_PARSE_DIR = parsing/
B_READ_DIR = read/
B_ERROR_DIR = error/
B_GNL_DIR = ../libs/get_next_line/

# Files by directory
B_BASE_FILES = cub3D.c render.c 
B_INIT_FILES = initialitations.c init_map_minimap_params.c init_player_and_vision_params.c init_print_params.c init_mlx_params.c
B_WALLS_RAYCAST_FILES = calculate_fov.c calculate_ray.c calculate_ray_utils.c 
B_DOORS_RAYCAST_FILES = check_ray_opened_door.c door_raycasting.c door_raycasting_utils.c update_doors_status.c
B_MOVE_FILES = press_or_release_key.c move_player.c rotate_player.c check_collisions.c
B_PRINT_MAP_FILES = print_map.c print_walls.c print_utils.c textures.c
B_PRINT_MINI_FILES = print_fov_and_vision_angle.c print_minimap_skeleton.c
B_DRAGON_FILES = do_dragon_animation.c print_dragon.c
B_PARSE_FILES = parse_map.c parse_utils.c
B_READ_FILES = read_fd.c read_fd_utils.c read_fd_utils2.c read_colors.c get_map.c
B_ERROR_FILES = free_errors.c msg_errors.c
B_GNL_FILES = get_next_line.c get_next_line_utils.c

# Relacion de los directories con sus respectivos files
B_INIT_SRCS = $(addprefix $(B_INIT_DIR), $(B_INIT_FILES))
B_WALLS_RAYCAST_SRCS = $(addprefix $(B_WALLS_RAYCAST_DIR), $(B_WALLS_RAYCAST_FILES))
B_DOORS_RAYCAST_SRCS = $(addprefix $(B_DOORS_RAYCAST_DIR), $(B_DOORS_RAYCAST_FILES))
B_MOVE_SRCS = $(addprefix $(B_MOVE_DIR), $(B_MOVE_FILES))
B_PRINT_MAP_SRCS = $(addprefix $(B_PRINT_MAP_DIR), $(B_PRINT_MAP_FILES))
B_PRINT_MINI_SRCS = $(addprefix $(B_PRINT_MINI_DIR), $(B_PRINT_MINI_FILES))
B_DRAGON_SRCS = $(addprefix $(B_DRAGON_DIR), $(B_DRAGON_FILES))
B_PARSE_SRCS = $(addprefix $(B_PARSE_DIR), $(B_PARSE_FILES))
B_READ_SRCS = $(addprefix $(B_READ_DIR), $(B_READ_FILES))
B_ERROR_SRCS = $(addprefix $(B_ERROR_DIR), $(B_ERROR_FILES))
B_GNL_SRCS = $(addprefix $(B_GNL_DIR), $(B_GNL_FILES))

# Todos los files con su respectivo path
FILES_BONUS = $(B_BASE_FILES) $(B_INIT_SRCS) $(B_WALLS_RAYCAST_SRCS) $(B_DOORS_RAYCAST_SRCS) $(B_MOVE_SRCS) $(B_PRINT_MAP_SRCS) \
		$(B_PRINT_MINI_SRCS) $(B_DRAGON_SRCS) $(B_PARSE_SRCS) $(B_READ_SRCS) $(B_ERROR_SRCS) $(B_GNL_SRCS)	


		
SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

SRCDIR_BONUS = srcbonus/
SRCS_BONUS = $(addprefix $(SRCDIR_BONUS), $(FILES_BONUS))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

OBJDIR_BONUS = objbonus/
OBJS_BONUS = $(patsubst $(SRCDIR_BONUS)%.c, $(OBJDIR_BONUS)%.o, $(SRCS_BONUS))

INCLUDES = -I ./libs/Libft -I ./inc -I ./libs/get_next_line/

NAME = cub3D
NAME_BONUS = cub3Dbonus

HEADER = inc/cub3D.h libs/get_next_line/get_next_line.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -Ofast #-g -fsanitize=address #


MLXDIR = libs/MLX42
LIBS = libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

$(OBJDIR_BONUS)%.o: $(SRCDIR_BONUS)%.c $(HEADER) Makefile libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos

all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all --no-print-directory
	@cmake $(MLXDIR) -DDEBUG=1 -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 --no-print-directory

${NAME}: ${OBJS}
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
	@echo ""⠀⠀
	@echo "                   ⠀⠀         ⠀⠀$(YELLOW)⢀⣶⠀⠀$(PINK)⢀⣄ ⠀⠀⣠⣶⣾⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " 	             ⠀⠀⠀⠀  $(PINK)⢀⣼⡛$(YELLOW)⣆⣰⣿⣿$(PINK)⣠⠞⣓⣿⣿⠶⠞⠛⣫⣿⣷⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " $(RED) ⠈⣇      $(CYAN)DRACARYS        $(PINK)⣸⣿⡥⣿⡏⣸⡿⠛⠉⠉⠉⠉⠉⠓⢲$(YELLOW)⣠⠼⢱$(PINK)⣿⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀ $(RED) ⣄⢻⡆                 $(BLUE)⢀⡴⠶⢿⡋⠀$(PINK)⠟⠛⠁$(BLUE)⣀⣀⣀⠀⠀⠀$(YELLOW)⠺⡷⠚⠉⢀⣾$(PINK)⣿⣶⣿⠗⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀ $(RED) ⡽⢸$(ORANGE)⡿$(RED)⣆⠀⠀     $(RED)⠀$(CYAN)TEAM  ⠀ $(NC)⢸⡿⣷⣄$(BLUE)⠙⠀⠀$(BLUE)⢠⠞⢛⣿⣭⣙⠛⣦⡀$(YELLOW)⠹⣄⣀⡼⣻$(PINK)⣿⣯⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "  $(RED)⠈⠀⡬$(ORANGE)⠃⠸$(RED)⡆  $(ORANGE)⡼⡄           $(NC)⢸⣧⡏⣿⠀⠀⠀$(NC)⢠⡞⠋⢹⡟⠟⢳$(BLUE)⠈⢧⠀$(BLUE)⠈⠙⠿⢻⠃$(PINK)⣷⠈⢻⣄⠀⠀⠀⠀⠀⠀⠀"
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

bonus: make_libs ${NAME_BONUS}

$(NAME_BONUS): ${OBJS_BONUS}
	@$(CC) $(CFLAGS) ${OBJS_BONUS} $(LIBS) -o $(NAME_BONUS)
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
	@echo "	$(PINK)⠀⠎⣴⠛⢡⠃⠀⠀$(BLUE)⣴$(CYAN)⡏⠈⠢⣀⣸⣉⠦$(BLUE)⣬⠦⣀⠀⣄⠀⠀ ⠈⠃⠀⠀⠙⡀⠀$(END)"
	@echo "	$(PINK)⠀⡸⡁⣠⡆⠀⠀$(BLUE)⣾$(CYAN)⠋⠑⢄⣀⣠⡤⢕$(BLUE)⡶⠁⠀⠀⠁⢪⠑⠤⡀⠀ ⢰⡐⠂⠑⢀$(END)"
	@echo "	$(PINK)⠀⠏⡼⢋⠇⠀$(BLUE)⣸$(CYAN)⣟⣄⠀⠀⢠⡠⠓$(BLUE)⣿⠇⠀⠀⠀⠀⠀⠑⢄⡌⡆ ⢰⣷⣀⡀⢸$(END)"
	@echo "	$(PINK)⠀⣸⠁⢸⠀$(BLUE)⢀$(CYAN)⡿⡀⠀⠈⢇⡀⠗⢲$(BLUE)⡟⠅⠀⠀⠀⠀⠀⠀⠀⠹⡌⠢⣀ ⠀⣸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "	$(PINK)⠀⣧⠤⣼⠀$(BLUE)⢸$(CYAN)⠇⠉⠂⠔⠘⢄⣀⢼$(BLUE)⠃⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠚⠳⡤⠋⠀$(RED)⠈⠢⠀$(END)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "	$(PINK)⠐⠇⣰⢿⠀$(CYAN)⣾⢂⣀⣀⡸⠆⠁⠀⣹⠀$(BLUE)⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠠⣀$(ORANGE)⢏⠺⢮$(RED)⡒⠤⠄⠀⠀⠀  ⠀⢰⠿⣷⣆⠀$(END)"
	@echo "	⠀$(PINK)⢀⡏⣸⠀$(CYAN)⣟⠁⠀⠙⢄⠼⠁⠈⢺⠀$(BLUE)⠘⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠀⠿⡺⣦$(ORANGE)⠘⢷⣄⡄   ⠀⠀⠀⢀⢀⡿⣿⡶⡷⠤⠀⠀$(END)⠀"
	@echo "	$(PINK)⠀⠈⡏⣸$(BLUE)⢰$(CYAN)⡯⠆⢤⠔⠊⢢⣀⣀⡼$(BLUE)⡇⠀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED) ⠀⠽$(ORANGE)⢷⣄⡙⠻⣷⣷⣤⣤⣤⣾⡾⢫⣿⣽⣳⣶⣶⣄⠀$(END)⠀⠀"
	@echo "	$(PINK)⠀⠀⢠⢻$(BLUE)⢸$(CYAN)⡇⠀⠀⠑⣤⠊⠀⠀⠈$(BLUE)⣧⠀⠀⠙⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  $(RED)⠀⢸$(ORANGE)⠘⣿⡔$(YELLOW)⠆         ⣄⣀$(ORANGE)⡹⣾⣿⡇⠀$(END)⠀⠀⠀⠀⠀"
	@echo "	⠀$(PINK)⠀⠸⣼$(BLUE)⢸$(CYAN)⠟⠑⠺⡉⠈⢑⠆⠠⠐⢻$(BLUE)⡄⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠸$(YELLOW)⣿ $(CYAN)DRACARYS$(ORANGE) $(YELLOW)⢶⣟$(ORANGE)⣿⣳⡏⠀$(END)⠀⠀⠀⠀⠀⠀"
	@echo "	⠀⠀$(PINK)⠀⡟$(BLUE)⣸$(CYAN)⡀⠀⠀⣈⣶⡁⠀⠀⠀⢠$(BLUE)⢻⡄⠀⠀⠀⠑⠤⣄⡀⠀⠀⠀⠀⠀⠀$(RED)⢀⣀⡀⠀⠀$(ORANGE)⢠$(YELLOW)⣿⡇   $(CYAN)IS $(YELLOW)   ⠈⠳ $(ORANGE)⣿⢿⠋$(RED)⢤$(END)⠀⠀⠀"
	@echo "	⠀⠀$(PINK)⢰⠁$(BLUE)⣿$(CYAN)⡿⠟⢏⠁⠀⢈⠖⠒⠊⠉⠉⠹$(BLUE)⣄⠀⠀⠀⠀⠀⠈⠑⠢⡀⠀⠀⠀$(RED)⢿⣧$(ORANGE)⣀⣀⣤⣿⡿$(YELLOW)⠂ $(CYAN) BACK $(YELLOW)⣀⣠⣡⠀$(ORANGE)⢺⡿⡇⠀$(RED)⢀⠀$(END)⠀"
	@echo "	⠀$(PINK)⣀⠟$(BLUE)⢰$(CYAN)⡇⠀⠀⠈⢢⡴⠊⠀⠀⠀⠀⠀⣸⢙$(BLUE)⣷⢄⣀⡠⠤⠤⠒⠒⠚⠀⠀⠀$(ORANGE)⠈⠻⣿⢿⣻⣽$(YELLOW)⡑        ⠀$(ORANGE)⠛⢿⣻⣦⣼⢷⡇⠀$(RED)⠘⠆⠀$(END)⠀"
	@echo "	$(PINK)⠘⠹⠤$(BLUE)⠛$(CYAN)⠛⠲⢤⠐⠊⠈⠂⢤⢀⠠⠔⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⣀⠀⠀$(ORANGE)⠿⢻⣿⣻$(YELLOW)⡿⡇⠀⢨⠊⢵⡄⣁⠢⣍⠶⣄$(ORANGE)⢹⣟⣽⣿⠀⠀⠀$(RED)⣤⠀⠀$(END)"
	@echo "	⠀⠀⠀⠀⠀⠀⠀$(CYAN)⠣⢀⡀⠔⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(RED)⠈⢀⣠⠀$(ORANGE)⢸⣿⠋⣿$(YELLOW)⢧⡀⠺⣥⣴⣖⣉⣿⢿⣄⡚$(ORANGE)⢸⣯⡿⣾⡷⣶⣶$(RED)⣿⠀⠀$(END)⠀"
	@echo "				    $(RED)⠈⠁⠀⠀⠛⠷$(ORANGE)⠙⠿⠿⠿⢯⣿⡏$(YELLOW)⢻⣯⢻⣯⠉$(ORANGE)⢸⣷⠀⠈⠙⠛⠊⠁⠀⠀$(END)"
	@echo "	$(GREEN)  CUB3D BONUS DONE$(END)   	          ⠀   ⠀$(RED)⠐⠛⠃$(ORANGE)⣼⣿$(YELLOW)⡿⣟⣗$(ORANGE)⠈⠿⣷⣤⣠⣤⣦$(RED)⣶⣄$(END)⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⢻⡿⣽⣾$(YELLOW)⢿⣷⣦⣶⢾$(ORANGE)⣯⠗⠉⠀$(RED)⠙$(END)"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⠈⠑⠉⠛⠾⠽⠋⠛⠊⠉⠀$(END)⠀⠀⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠐⠆⢀⡀⠀⠀⠀$(END)"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠈⠛⠁⠀⠀⠀⠀$(END)⠀⠀"
	@echo ""

clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)$(NC)$(END)"

fclean: #clean 
	@${RM} ${OBJDIR}
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)"
	@${RM} ${NAME}
	@make -C libs/Libft fclean --no-print-directory
	@echo "$(RED)CUB3D EXEC DELETED$(END)$(END)"
	@echo "$(ORANGE)"
	@echo "	⠀⠀⠀⠀⠀⠀⢱⣆⠀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⠈⣿⣷⡀⠀"
	@echo "	⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣧⠀⠀⠀"
	@echo "	⠀⠀⠀⠀⡀⢠⣿$(END)$(YELLOW)⡟⣿$(END)$(ORANGE)⣿⣿⡇⠀"
	@echo "	⠀⠀⠀⠀⣳⣼⣿$(END)$(YELLOW)⡏⢸$(END)$(ORANGE)⣿⣿⣿⢀⠀"
	@echo "	⠀⠀⠀⣰⣿⣿$(END)$(YELLOW)⡿⠁⢸$(END)$(ORANGE)⣿⣿⡟⣼⡆"
	@echo "	⢰⢀⣾⣿$(END)$(YELLOW)⣿⠟⠀⠀⣾⢿$(END)$(ORANGE)⣿⣿⣿⣿"
	@echo "	⢸⣿⣿$(END)$(YELLOW)⣿⡏⠀⠀⠀⠃⠸⣿$(END)$(ORANGE)⣿⣿⡿"
	@echo "	⢳⣿⣿$(END)$(YELLOW)⣿⠀⠀⠀⠀⠀⠀⢹⣿$(END)$(ORANGE)⡿⡁"
	@echo "	⠀⠹⣿$(END)$(YELLOW)⣿⡄⠀⠀⠀⠀⠀⢠⣿$(END)$(ORANGE)⡞⠁"
	@echo "	⠀⠀⠈⠛$(END)$(YELLOW)⢿⣄⠀⠀⠀⣠⠞$(END)$(ORANGE)⠋⠀⠀"
	@echo "	⠀⠀⠀⠀⠀$(END)$(YELLOW)⠉ "
	@echo "$(END)"

re: fclean all
	@echo "CUB3D RE DONE"

re_bonus: fclean bonus
	@echo "CUB3D_BONUS RE DONE"

.PHONY: all clean fclean re⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
