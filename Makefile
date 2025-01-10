# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 17:24:49 by yanaranj          #+#    #+#              #
#    Updated: 2025/01/10 19:38:02 by yanaranj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

END = \033[0m
GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;93m
ORANGE = \033[38;5;214m
BLUE = \033[1;94m


FILES = cub3D.c parsing.c

SRCDIR = src/
SRCS = $(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc -I ./src/get_next_line/

NAME = cub3D

HEADER = inc/tcub3D.h src/get_next_line/get_next_line.h
CC = cc -g #-fsanitize=address
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LDFLAGS = -lreadline

#MLXDIR = libs/MLX42
LIBS = libs/Libft/libft.a #$(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) $(LIBS) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"
	
all: make_libs $(NAME)

make_libs:
	@make -C libs/Libft all
	
$(NAME): ${OBJS} $(HEADER)
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
	@echo "$(GREEN)"
	@echo " "
	@echo "      ⣰⠂⠀⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣀⠀⠀⠀⠀⠀⠀⠀"
	@echo "      ⡟⢆⢠⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡘⡇⠹⢦⠀⠀⠀⠀⠀⠀"
	@echo "      ⠹⣦⣹⢸⡖⠤⢀⠀⠘⢿⠛⢔⠢⡀⠃⠣⠀⠇⢡⠀⠀⠀⠀⠀"
	@echo "        ⠹⠀⡷⣄⠠⡈⠑⠢⢧⠀⢢⠰⣼⢶⣷⣾⠀⠃⠀⠀ "
	@echo "       ⠤⢖⡆⠰⡙⢕⢬⡢⣄⠀⠑⢼⠀⠚⣿⢆⠀⠱⣸⠀⠀⠀⠀"
	@echo "     ⢀⣤⡶⠮⢧⡀⠑⡈⢢⣕⡌⢶⠀⠀⣱⣠⠉⢺⡄⠀⢹⠀⠀⠀⠀"
	@echo "      ⢀⡸⠀⠈⡗⢄⡈⢆⠙⠿⣶⣿⠿⢿⣷⣴⠉⠹⢶⢾⡆⠀⠀⠀"
	@echo "   ⢠⠶⠿⡉⠉⠉⠙⢻⣮⡙⢦⣱⡐⣌⠿⡄⢁⠄⠑⢤⣀⠐⢻⡇⠀"
	@echo "   ⢀⣠⠾⠖⠛⢻⠟⠁⢘⣿⣆⠹⢷⡏⠀⠈⢻⣤⡆⠀⠑⢴⠉⢿⣄⠀"
	@echo "  ⢠⠞⢃⢀⣠⡴⠋⠀⠈⠁⠉⢻⣷⣤⠧⡀$(END) $(RED)⠦$(END) $(GREEN)⠈⢻⠿⣿⡀⡀⣸⠀⠀"
	@echo "  ⢀⠔⠋⠁⡰⠁⠀⢀⠠⣤⣶⠞⢻⡙⠀⠙⢦⠀⠈⠓⢾⡟⡖⠊⡏⡟⠀⠀ "
	@echo "  ⣋⢀⣠⡞⠁⠀⠔⣡⣾⠋⠉⢆⡀⢱⡀⠀⠀⠀⠀⠀⠀⢿⡄⠀⢇⠇⠀⠀"
	@echo " ⠎⣴⠛⢡⠃⠀⠀⣴⡏⠈⠢⣀⣸⣉⠦⣬⠦⣀⠀⣄⠀⠀⠈⠃⠀⠀⠙⡀⠀"
	@echo " ⡸⡁⣠⡆⠀⠀⣾⠋⠑⢄⣀⣠⡤⢕⡶⠁⠀⠀⠁⢪⠑⠤⡀⠀⢰⡐⠂⠑⢀"
	@echo " ⠏⡼⢋⠇⠀⣸⣟⣄⠀⠀⢠⡠⠓⣿⠇⠀⠀⠀⠀⠀⠑⢄⡌⠆⢰⣷⣀⡀⢸"
	@echo " ⣸⠁⢸⠀⢀⡿⡀⠀⠈⢇⡀⠗⢲⡟⠀⠀⠀⠀⠀⠀⠀⠀⠹⡜⠦⣈⠀⣸⡄"
	@echo " ⣧⠤⣼⠀⢸⠇⠉⠂⠔⠘⢄⣀⢼⠃⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠚⠳⠋⠀   🔥  🔥  🔥  🔥	"
	@echo " ⠐⠇⣰⢿⠀⣾⢂⣀⣀⡸⠆⠁⠀⣹⠀⢡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀🔥              🔥"
	@echo " ⢀⡏⣸⠀⣟⠁⠀⠙⢄⠼⠁⠈⢺⠀⠘⡆⠀	   $(END)  $(RED)🔥 DRACARYS IS BACK 🔥 $(END) $(GREEN)"
	@echo " ⠈⡏⣸⢰⡯⠆⢤⠔⠊⢢⣀⣀⡼⡇⠀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 🔥              🔥"
	@echo " ⢠⢻⢸⡇⠀⠀⠑⣤⠊⠀⠀⠈⣧⠀⠀⠙⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    🔥  🔥  🔥  🔥"
	@echo " ⠸⣼⢸⠟⠑⠺⡉⠈⢑⠆⠠⠐⢻⡄⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "  ⡟⣸⡀⠀⠀⣈⣶⡁⠀⠀⠀⢠⢻⡄⠀⠀⠀⠑⠤⣄⡀⠀⠀⠀⠀⠀⠀"
	@echo " ⢰⠁⣿⡿⠟⢏⠁⠀⢈⠖⠒⠊⠉⠉⠹⣄⠀⠀⠀⠀⠀⠈⠑⠢⡀⠀⠀⠀"
	@echo " ⣀⠟⢰⡇⠀⠀⠈⢢⡴⠊⠀⠀⠀⠀⠀⣸⢙⣷⠄⢀⠀⠠⠄⠐⠒⠚⠀⠀⠀"
	@echo " ⠘⠹⠤⠛⠛⠲⢤⠐⠊⠈⠂⢤⢀⠠⠔⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo " ⠀⠀⠀⠀⠀⠣⢀⡀⠔⠃⠀⠀⠀⠀⠀"
	@echo "$(END)"
	@echo "$(BLUE)	CUB_3D DONE$(END)"

clean:
	@$(RM) ${OBJDIR}
	@make -C libs/Libft clean --no-print-directory
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)$(END)"

fclean: clean
	@$(RM) $(NAME)
	@make -C libs/Libft fclean --no-print-directory
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
	@echo "$(RED) CUB3D EXEC DELETED$(END)$(END)"

re: fclean all

.PHONY: all clean fclean re
