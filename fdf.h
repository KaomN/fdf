/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:43 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/08 16:43:04 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx_linux/mlx.h"
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
	int	x1;
	int	y1;
	int z;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	pad;
}	t_linedata;

typedef struct s_flags
{
	double		h;
	double		zoom;
	int		vert;
	int		hori;
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
** pixel_put.c
*/

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);

/* 
** events.c
*/

int		events(int keycode, t_fdf *fdf);
int		keyboard_event(int keycode, t_fdf *fdf);
int		zoom_event(int keycode, t_fdf *fdf);
int		exit_event(int keycode, t_fdf *fdf);
int		exit_fdf(t_fdf *fdf);

/*
** draw_line.c
*/

void	draw_image(t_fdf *fdf);

/*
** draw_line.c
*/

void	free_str_arr(char **arr);
int		get_length(char *line);
int	*transform_array(char *lines);

/*
** draw_line.c
*/

void	draw_line_dx(t_fdf *fdf, int check, int color);
void	draw_line_dy(t_fdf *fdf, int check, int color);
void	draw_line_dx2(t_fdf *fdf, int check, int color);
void	draw_line_dy2(t_fdf *fdf, int check, int color);

/*
** main.c
*/

void	render_image(t_fdf *fdf);
void	zoom_image(t_fdf *fdf);
void	move_image(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);

#endif