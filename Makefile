# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 16:33:21 by tvisenti          #+#    #+#              #
#    Updated: 2018/01/31 10:47:30 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S	= serveur
NAME_C	= client

SRC_DIR_S	= ./server_src
SRC_DIR_C	= ./client_src
SRC_DIR_L	= ./lib

SRC_S = server.c \
		cmd_server.c \
		cmd_put_server.c \
		cmd_get_server.c \

SRC_C =	client.c \
		cmd_client.c \
		cmd_put_client.c \
		cmd_get_client.c \

SRC_L = display.c \
		handle_file.c \

O_DIR	= ./obj
OBJ_S	= $(addprefix $(O_DIR)/,$(SRC_S:.c=.o))
OBJ_C	= $(addprefix $(O_DIR)/,$(SRC_C:.c=.o))
OBJ_L	= $(addprefix $(O_DIR)/,$(SRC_L:.c=.o))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

HEADERS = -I inc/

LIBFT = -Llibft -lft

all : serveur client

serveur: $(OBJ_S) $(OBJ_L)
	@echo "\033[31m==> COMPILING in progress ...\033[0m"
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ $(OBJ_S) $(OBJ_L) $(HEADERS) $(LIBFT)
	@echo "\033[32m==> SUCCESS !\033[0m"

client: $(OBJ_C) $(OBJ_L)
	@echo "\033[31m==> COMPILING in progress ...\033[0m"
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ $(OBJ_C) $(OBJ_L) $(HEADERS) $(LIBFT)
	@echo "\033[32m==> SUCCESS !\033[0m"

$(O_DIR)/%.o: $(SRC_DIR_S)/%.c
	@mkdir $(O_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(O_DIR)/%.o: $(SRC_DIR_C)/%.c
	@mkdir $(O_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(O_DIR)/%.o: $(SRC_DIR_L)/%.c
	@mkdir $(O_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	@echo "\033[35m==> CLEANING in progress ...\033[0m"
	@rm -rf $(OBJ_S) $(OBJ_C) $(OBJ_L) $(NAME_S) $(NAME_C)

fclean: clean
	@make fclean -C libft
	@rm -rf $(O_DIR)
	@echo "\033[35m==> CLEANING test files ...\033[0m"

re: fclean all

norme:
	@echo "\n"----------------------- NORMINETTE LIBFT --------------------------"\n"
	@norminette libft/lib/*.c libft/ft_printf/src/*.c libft/ft_printf/lib/*.c libft/inc/*.h
	@echo "\n"------------------------ NORMINETTE FT_P --------------------------"\n"
	@norminette client_src/*.c server_src/*.c inc/*.h
	@echo "\n"--------------------------- END -----------------------------------"\n"

.PHONY: re fclean clean all norme
