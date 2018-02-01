# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 16:33:21 by tvisenti          #+#    #+#              #
#    Updated: 2018/02/01 11:44:41 by tvisenti         ###   ########.fr        #
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

all : ft_lib serveur client

serveur: $(OBJ_S) $(OBJ_L)
	@echo "\033[1;34mft_p:serveur\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_S) $(OBJ_L) $(HEADERS) $(LIBFT)

client: $(OBJ_C) $(OBJ_L)
	@echo "\033[1;34mft_p:client\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_C) $(OBJ_L) $(HEADERS) $(LIBFT)

ft_lib:
	@make -C libft

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
	@rm -rf $(OBJ_S) $(OBJ_C) $(OBJ_L) $(NAME_S) $(NAME_C)
	@echo "\033[1;34mft_p\t\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"


fclean: clean
	@make fclean -C libft
	@rm -rf $(O_DIR)
	@echo "\033[1;34mft_p\t\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"

re: fclean all

norme:
	@make norme -C libft
	@norminette client_src/*.c server_src/*.c lib/*.c inc/*.h 
	@echo "\033[1;34mft_p\t\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"

.PHONY: re fclean clean all norme
