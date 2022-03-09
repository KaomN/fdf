# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:30:11 by conguyen          #+#    #+#              #
#    Updated: 2022/03/09 10:39:30 by conguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LEAK = -fsanitize=leak

CFILES += main.c
CFILES += events.c
CFILES += draw_line.c
CFILES += draw_image.c
CFILES += pixel_put.c
CFILES += parser.c

OBJ = $(CFILES:.c=.o)

all: $(NAME)

$(NAME):
#	$(CC) -c $(CFLAGS) -I includes $(CFILES)
# 	$(CC) $(CFILES) -L./mlx_linux -lmlx_Linux -framework OpenGL -framework AppKit -L. libft/libft.a
	$(CC) $(CFILES) -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -L. libft/libft.a -lm 

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
