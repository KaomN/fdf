/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:43 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/22 10:58:59 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx_linux/mlx.h"
# include <mlx.h>
/* include "key_define_macschool.h" */
# include "key_define.h"
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>
# include <math.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	int	**map;
	int	**color;
	int	width;
	int	height;
}	t_map;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_winsize
{
	int		w;
	int		h;
}	t_winsize;

typedef struct s_linedata
{
	double	x1;
	double	y1;
	double	z;
	double	x2;
	double	y2;
	double	dx;
	double	dy;
	int		pad_h;
	int		pad_w;
	int		curr_color;
	int		next_color;
}	t_linedata;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_flags
{
	double	h;
	double	h_modifier;
	int		zoom;
	int		vert;
	int		hori;
	double	proj_y;
	double	proj_x;
	double	para_y;
	double	isom_x;
	double	pad_modifier;
	int		projection;
	int		color;
}	t_flags;

typedef struct s_fdf
{
	t_data		mlx;
	t_map		map;
	t_winsize	winsize;
	t_flags		flag;
	t_linedata	px;
}	t_fdf;

/* 
** draw.c
*/

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void	clear_image(t_fdf *fdf);
void	render_image(t_fdf *fdf);

/* 
** events.c
*/

int		events(int keycode, t_fdf *fdf);

/*
** draw_image.c
*/

void	draw_image(t_fdf *fdf);

/*
** draw_line.c
*/

void	draw_line_dx(t_fdf *fdf, int check);
void	draw_line_dy(t_fdf *fdf, int check);

/*
** parser.c
*/

void	transform_array(char *lines, t_fdf *fdf);

/*
** parser_check.c
*/

void	free_str_arr(char **arr);
void	check_line(char **line);
void	check_width(char **lines_arr, t_fdf *fdf, int x);

/*
** color_parser.c
*/

int		check_color_line(char *line, t_fdf *fdf, int x);

/*
** color.c
*/

int		color_fade(t_fdf *fdf, int mod, int distance);
int		coloring(t_fdf *fdf, int mod, int distance);

/*
** exit.c
*/

int		exit_fdf(t_fdf *fdf);
void	error_exit(char **lines);

#endif