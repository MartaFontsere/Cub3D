# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/03/29 15:23:39 by yanaranj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

END = \033[0m
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

# Files by directory
BASE_FILES = cub3D.c render.c

INIT_FILES = initialitations.c init_map_minimap_params.c init_player_and_vision_params.c init_print_params.c init_mlx_params.c
FOV_FILES = calculate_fov.c calculate_ray.c calculate_ray_utils.c 
MOVE_FILES = press_or_release_key.c move_player.c rotate_player.c check_collisions.c
PRINT_FILES = print_map.c print_walls.c print_utils.c textures.c
PARSE_FILES = parse_map.c parse_utils.c
READ_FILES = read_fd.c read_fd_utils.c read_colors.c get_map.c
ERROR_FILES = free_errors.c msg_errors.c
GNL_FILES = get_next_line.c get_next_line_utils.c

#----------------------BONUS FILES---------------------------#
B_BASE_FILES = cub3D_bonus.c #render_bonus.c

B_INIT_FILES = init_map_minimap_params_bonus.c init_print_params_bonus.c
B_PARSE_FILES = parse_map_bonus.c parse_utils_bonus.c parse_utils2_bonus.c
B_READ_FILES = read_fd_bonus.c read_fd_utils_bonus.c read_fd_utils2_bonus.c read_colors_bonus.c read_colors_utils_bonus.c get_map_bonus.c
B_ERROR_FILES = free_errors_bonus.c msg_errors_bonus.c

# Directories
INIT_DIR = initialitations/
FOV_DIR = fov/
MOVE_DIR = movements/
PRINT_DIR = print_map/
PRINT_MINI_DIR = print_minimap/
PARSE_DIR = parsing/
READ_DIR = read/
ERROR_DIR = error/
GNL_DIR = ../libs/get_next_line/

INIT_SRCS = $(addprefix $(INIT_DIR), $(INIT_FILES))
FOV_SRCS = $(addprefix $(FOV_DIR), $(FOV_FILES))
MOVE_SRCS = $(addprefix $(MOVE_DIR), $(MOVE_FILES))
PRINT_SRCS = $(addprefix $(PRINT_DIR), $(PRINT_FILES))
PRINT_MINI_SRCS = $(addprefix $(PRINT_MINI_DIR), $(PRINT_MINI_FILES))
PARSE_SRCS = $(addprefix $(PARSE_DIR), $(PARSE_FILES))
READ_SRCS = $(addprefix $(READ_DIR), $(READ_FILES))
ERROR_SRCS = $(addprefix $(ERROR_DIR), $(ERROR_FILES))
GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FILES))

#todos los files con su respectivo path
FILES = $(BASE_FILES) $(INIT_SRCS) $(FOV_SRCS) $(MOVE_SRCS) $(PRINT_SRCS) \
		$(PRINT_MINI_SRCS) $(PARSE_SRCS) $(READ_SRCS) $(ERROR_SRCS) $(GNL_SRCS)

SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

#-------------------------------BONUS SRCS-------------------------------#
B_INIT_SRCS = $(addprefix $(INIT_DIR), $(B_INIT_FILES))
B_PARSE_SRCS = $(addprefix $(PARSE_DIR), $(B_PARSE_FILES))
B_READ_SRCS = $(addprefix $(READ_DIR), $(B_READ_FILES))
B_ERROR_SRCS = $(addprefix $(ERROR_DIR), $(B_ERROR_FILES))

B_FILES = $(B_BASE_FILES) $(B_INIT_SRCS) $(B_PARSE_SRCS) $(B_READ_SRCS) \
		$(B_ERROR_SRCS) $(GNL_SRCS)

B_SRCDIR = src_bonus/
B_SRCS = $(addprefix $(B_SRCDIR), $(B_FILES))

B_OBJDIR = obj_bonus/
B_OBJS = $(patsubst $(B_SRCDIR)%.c, $(B_OBJDIR)%.o, $(B_SRCS))

INCLUDES = -I ./libs/Libft -I ./inc -I ./libs/get_next_line/

NAME = cub3D

HEADER = inc/cub3D.h libs/get_next_line/get_next_line.h inc/cub3D_bonus.h
CC = cc
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS += #-Ofast 

MLXDIR = libs/MLX42
LIBS = libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"
# aqui reglas de BONUS
$(B_OBJDIR)%.o: $(B_SRCDIR)%.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos
all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all --no-print-directory
	@cmake $(MLXDIR) -DDEBUG=1 -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 --no-print-directory

ifndef BONUS
${NAME}: ${OBJS} ${LIBS} dragon
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
else
${NAME}: ${B_OBJS} ${LIBS} dragon
	@$(CC) $(CFLAGS) ${B_OBJS} ${LIBS} -o $(NAME)
endif
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
	@${RM} ${OBJDIR} ${B_OBJDIR}
	@make -C libs/Libft clean --no-print-directory
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)"

fclean:
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)"
	@${RM} ${OBJDIR} ${B_OBJDIR}
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

.PHONY: all clean fclean re