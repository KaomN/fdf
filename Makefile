# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:30:11 by conguyen          #+#    #+#              #
#    Updated: 2022/03/22 11:18:26 by conguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LEAK = -fsanitize=leak
LIBFT = libft/
INCLUDES = -I ./includes

CFILES += main.c
CFILES += events.c
CFILES += draw_line.c
CFILES += draw_image.c
CFILES += draw.c
CFILES += parser.c
CFILES += color_parser.c
CFILES += parser_check.c
CFILES += color.c
CFILES += exit.c

OBJ = $(CFILES:.c=.o)

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
#	$(CC) -c $(CFLAGS) -I includes $(CFILES)
#	Compile on Mac
#	$(CC) $(CFILES) $(CFLAGS) -L/usr/local/lib/ -lmlx -Llibft -lft -framework OpenGL -framework AppKit
#	Compile on Linux
#	$(CC) $(CFILES) $(CFLAGS) -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -L. libft/libft.a -lm 
	$(CC) -c $(CFLAGS) $(INCLUDES) $(CFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES) -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -L. libft/libft.a -lm

clean:
	/bin/rm -f $(OBJ)
	make -C $(LIBFT) clean
	
fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
