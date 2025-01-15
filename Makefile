# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/01/15 16:11:43 by yanaranj         ###   ########.fr        #
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

#DUDAS:
	#Makefile con dependencias
	#No tener que poner el nombre de la carpeta cada vez que ponga un archivo dentro de ella.

#FILES =  cub3D.c initialitations.c pseudoparsing.c print_minimap.c render.c error.c
FILES = cub3D.c parsing.c 

SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc -I ./src/get_next_line/

NAME = cub3D

HEADER = inc/cub3D.h src/get_next_line/get_next_line.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

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
	@make -C libs/Libft all
	@cmake $(MLXDIR) -DDEBUG=1 -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

${NAME}: ${OBJS}
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
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

clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean --no-print-directory
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)$(NC)$(END)"

fclean:
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
