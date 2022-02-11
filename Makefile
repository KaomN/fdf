# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:30:11 by conguyen          #+#    #+#              #
#    Updated: 2022/02/11 09:42:31 by conguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -Wall -Werror -Wextra

CFILES += main.c

OBJ = $(CFILES:.c=.o)

all: $(NAME)

$(NAME):
#	$(CC) -c $(CFLAGS) -I includes $(CFILES)
	$(CC) $(CFILES) -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -L./libft -lft -lm

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
