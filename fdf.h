/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:43 by conguyen          #+#    #+#             */
/*   Updated: 2022/02/14 12:44:56 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_F
# define FDF_F

#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include "libft/libft.h"

/* DELETE!*/
#include <stdio.h>
#include <math.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_linedata
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	double	dx;
	double	dy;
}				t_linedata;

/* events.c */
int	esc_key(int keycode, void *param);

/* draw_line.c */
void	draw_line_dx(t_data data, t_linedata pixel, int check, int color);
void	draw_line_dy(t_data data, t_linedata pixel, int check, int color);

/* main.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
