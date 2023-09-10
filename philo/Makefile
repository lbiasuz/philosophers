# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 10:03:39 by lbiasuz           #+#    #+#              #
#    Updated: 2023/09/10 14:20:11 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g3 -fsanitize=thread

SRC_DIR	=	src
HEAD_DIR=	include
OBJ_DIR	=	bin

SRC		=	$(SRC_DIR)/input.c $(SRC_DIR)/main.c $(SRC_DIR)/helpers.c
HEAD	=	$(HEAD_DIR)/philosophers.h
OBJ		=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(HEAD_DIR:%=-I%/)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(@:$(SRC_DIR)=$(OBJ_DIR)) $(HEAD_DIR:%=-I%/)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: all
	valgrind -s --leak-check=full --show-leak-kinds=all \
			--log-fd=10 ./$(NAME) $(ARGS) 10>helgrind.log

helgrind: all
	valgrind --tool="helgrind" ./$(NAME) \
			--log-fd=11 ./$(NAME) $(ARGS) 11>helgrind.log

drd: all
	valgrind --tool="drd" ./$(NAME) \
			--log-fd=12 ./$(NAME) 12>helgrind.log

.PHONY: all clean fclean re valgridn helgrind drd