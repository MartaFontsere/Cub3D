# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2025/01/07 19:55:57 by mfontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

NC = \033[0m
GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \e[1;93m

#------------------------------------------------VARIABLES---------------------------------------------------#

#DUDAS:
	#Makefile con dependencias
	#No tener que poner el nombre de la carpeta cada vez que ponga un archivo dentro de ella.

FILES =  cub3D.c




SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc

NAME = cub3D

HEADER = inc/cub3D.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LDFLAGS = -lreadline

LIBS = libs/Libft/libft.a $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile libs/Libft/libft.a  
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos

all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all

${NAME}: ${OBJS}
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME)
	
clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)$(NC)$(END)"

fclean:
	@${RM} ${OBJDIR}
	@echo "$(RED)CUB3D OBJECTS DELETED$(END)"
	@${RM} ${NAME}
	@make -C libs/Libft fclean
	@echo "$(RED) CUB3D EXEC DELETED$(END)$(NC)$(END)"

re: fclean all
	@echo "CUB3D RE DONE"

.PHONY: all clean fclean re
