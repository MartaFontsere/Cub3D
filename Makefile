# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/03/18 16:03:19 by yanaranj         ###   ########.fr        #
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

# Directories
INIT_DIR = initialitations/
VISION_ANGLE_DIR = vision_angle/ 
FOV_DIR = fov/
MOVE_DIR = movements/
PRINT_DIR = print_map/
PARSE_DIR = parsing/
READ_DIR = read/
ERROR_DIR = error/
GNL_DIR = ../libs/get_next_line/

# Files by directory
BASE_FILES = cub3D.c render.c 
INIT_FILES = initialitations.c init_map_minimap_params.c init_player_and_vision_params.c init_print_params.c init_mlx_params.c
VISION_ANGLE_FILES = calculate_vision_angle.c 
FOV_FILES = calculate_fov.c calculate_ray.c calculate_ray_utils.c 
MOVE_FILES = press_or_release_key.c move_player.c rotate_player.c check_collisions.c
PRINT_FILES = print_map.c print_walls.c print_utils.c textures.c
PARSE_FILES = parse_map.c parse_utils.c
READ_FILES = read_fd.c read_fd_utils.c read_colors.c get_map.c
ERROR_FILES = free_errors.c msg_errors.c
GNL_FILES = get_next_line.c get_next_line_utils.c

INIT_SRCS = $(addprefix $(INIT_DIR), $(INIT_FILES))
VISION_ANGLE_SRCS = $(addprefix $(VISION_ANGLE_DIR), $(VISION_ANGLE_FILES))
FOV_SRCS = $(addprefix $(FOV_DIR), $(FOV_FILES))
MOVE_SRCS = $(addprefix $(MOVE_DIR), $(MOVE_FILES))
PRINT_SRCS = $(addprefix $(PRINT_DIR), $(PRINT_FILES))
PRINT_MINI_SRCS = $(addprefix $(PRINT_MINI_DIR), $(PRINT_MINI_FILES))
PARSE_SRCS = $(addprefix $(PARSE_DIR), $(PARSE_FILES))
READ_SRCS = $(addprefix $(READ_DIR), $(READ_FILES))
ERROR_SRCS = $(addprefix $(ERROR_DIR), $(ERROR_FILES))
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))
BONUS_SRCS = $(addprefix $(BONUS_DIR), $(BONUS_FILES))

#todos los files con su respectivo path
FILES = $(BASE_FILES) $(INIT_SRCS) $(FOV_SRCS) $(MOVE_SRCS) $(PRINT_SRCS) \
		$(PRINT_MINI_SRCS) $(PARSE_SRCS) $(READ_SRCS) $(ERROR_SRCS) $(GNL_SRCS) \
		$(BONUS_SRCS)

		
SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc -I ./libs/get_next_line/

NAME = cub3D

HEADER = inc/cub3D.h libs/get_next_line/get_next_line.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CFLAGS += -Ofast

MLXDIR = libs/MLX42
LIBS = libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos

all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all --no-print-directory
	@cmake $(MLXDIR) -DDEBUG=1 -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 --no-print-directory

ifndef BONUS
${NAME}: ${OBJS} dragon
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
else
${NAME}: ${OBJS_BONUS} dragon
	@$(CC) $(CFLAGS) ${OBJS_BONUS} $(LIBS) -o $(NAME)
endif

dragon :
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
	@echo "	$(GREEN)     CUB3D DONE$(END)	      ⠀   ⠀⠀⠀⠀⠀   ⠀⠀⠀⠀⠀$(RED)⠐⠛⠃$(ORANGE)⣼⣿$(YELLOW)⡿⣟⣗$(ORANGE)⠈⠿⣷⣤⣠⣤⣦$(RED)⣶⣄$(END)⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⢻⡿⣽⣾$(YELLOW)⢿⣷⣦⣶⢾$(ORANGE)⣯⠗⠉⠀$(RED)⠙$(END)"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(ORANGE)⠀⠈⠑⠉⠛⠾⠽⠋⠛⠊⠉⠀$(END)⠀⠀⠀"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠐⠆⢀⡀⠀⠀⠀$(END)"
	@echo "				    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(RED)⠈⠛⠁⠀⠀⠀⠀$(END)⠀⠀"
	@echo ""

bonus: 
	@$(MAKE) BONUS=42

clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)$(NC)$(END)"

fclean: clean
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

.PHONY: all clean fclean re⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
