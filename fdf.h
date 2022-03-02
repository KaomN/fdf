/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:43 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/02 11:47:05 by conguyen         ###   ########.fr       */
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
	double	x;
	double	y;
}	t_pos;

typedef struct s_winsize
{
	int		width;
	int		height;
}	t_winsize;

typedef struct s_linedata
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	dx;
	double	dy;
}	t_linedata;

typedef struct s_flags
{
	int		height_flag;
	double	zoom_flag;
	int		vert;
	int		hori;
}	t_flags;

typedef struct s_fdf
{
	t_data		mlx;
	t_map		map;
	t_winsize	win_size;
	t_flags		flags;
	t_linedata	pixel;
}	t_fdf;



/* 
** events.c
*/

int		esc_key(int keycode, t_fdf *fdf);
int		mouse_event(int mouse_button, t_fdf *fdf);
int		exit_fdf();

/*
** draw_line.c
*/

void	draw_line_dx(t_data data, t_linedata pixel, int check, int color);
void	draw_line_dy(t_data data, t_linedata pixel, int check, int color);

/*
** main.c
*/

void	render_image(t_fdf *fdf);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif