# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsiguret <bsiguret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 20:22:27 by bsiguret          #+#    #+#              #
#    Updated: 2017/11/27 14:45:20 by bsiguret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRC =	 main.c \
		func.c \
		func2.c \
		list.c \
		reader.c \
		solver.c \
		tetrimino.c \
		map.c

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO)
	gcc -o $(NAME) $(FLAGS) $(SRCO)

%.o: %.c
	@echo "Building : $<"
	@gcc $(FLAGS) -I fillit.h -c $<

clean:
	rm -f $(SRCO)

fclean: 
	make clean
	rm -f $(NAME)

re: 
	make fclean
	make

.PHONY: all clean fclean re
