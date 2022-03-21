/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:42:04 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/21 13:30:18 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	increment_decrement(t_fdf *fdf, char ch)
{
	if (ch == 'x')
	{
		if (fdf->px.x1 < fdf->px.x2)
			fdf->px.x1 += 1;
		else
			fdf->px.x1 -= 1;
	}
	if (ch == 'y')
	{
		if (fdf->px.y1 < fdf->px.y2)
			fdf->px.y1 += 1;
		else
			fdf->px.y1 -= 1;
	}
}

static void	decider_dx(t_fdf *fdf, int check, int color)
{
	if (check == 0)
	{
		if (fdf->px.x1 + fdf->flag.hori < fdf->winsize.w
			&& fdf->px.y1 + fdf->flag.vert < fdf->winsize.h
			&& fdf->px.x1 + fdf->flag.hori >= 0
			&& fdf->px.y1 + fdf->flag.vert >= 0)
			my_mlx_pixel_put(fdf, fdf->px.x1 + fdf->flag.hori, fdf->px.y1
				+ fdf->flag.vert, color);
	}	
	else if (check == 1)
	{
		if (fdf->px.y1 + fdf->flag.hori < fdf->winsize.w
			&& fdf->px.x1 + fdf->flag.vert < fdf->winsize.h
			&& fdf->px.x1 + fdf->flag.vert >= 0
			&& fdf->px.y1 + fdf->flag.hori >= 0)
			my_mlx_pixel_put(fdf, fdf->px.y1 + fdf->flag.hori, fdf->px.x1
				+ fdf->flag.vert, color);
	}
}

static void	decider_dy(t_fdf *fdf, int check, int color)
{
	if (check == 0)
	{
		if (fdf->px.y1 + fdf->flag.hori < fdf->winsize.w
			&& fdf->px.x1 + fdf->flag.vert < fdf->winsize.h
			&& fdf->px.x1 + fdf->flag.vert >= 0
			&& fdf->px.y1 + fdf->flag.hori >= 0)
			my_mlx_pixel_put(fdf, fdf->px.y1 + fdf->flag.hori, fdf->px.x1
				+ fdf->flag.vert, color);
	}
	else if (check == 1)
	{
		if (fdf->px.x1 + fdf->flag.hori < fdf->winsize.w
			&& fdf->px.y1 + fdf->flag.vert < fdf->winsize.h
			&& fdf->px.x1 + fdf->flag.hori >= 0
			&& fdf->px.y1 + fdf->flag.vert >= 0)
			my_mlx_pixel_put(fdf, fdf->px.x1 + fdf->flag.hori, fdf->px.y1
				+ fdf->flag.vert, color);
	}
}

int	color_fade(t_fdf *fdf, int mod, int distance)
{
	t_color	current;
	t_color	next;
	int		red;
	int		green;
	int		blue;

	current.r = (fdf->px.curr_color & 0xFF0000) >> 16;
	next.r = (fdf->px.next_color & 0xFF0000) >> 16;
	current.g = (fdf->px.curr_color & 0x00FF00) >> 8;
	next.g = (fdf->px.next_color & 0x00FF00) >> 8;
	current.b = (fdf->px.curr_color & 0x0000FF);
	next.b = (fdf->px.next_color & 0x0000FF);
	red = current.r + ((double)(next.r - current.r) / distance) * mod;
	green = current.g + ((double)(next.g - current.g) / distance) * mod;
	blue = current.b + ((double)(next.b - current.b) / distance) * mod;
	return ((red << 16) + (green << 8) + blue);
}

void	draw_line_dx(t_fdf *fdf, int check)
{
	int	pk;
	int	i;

	pk = 2 * fdf->px.dy - fdf->px.dx;
	i = -1;
	while (++i < fdf->px.dx)
	{
		increment_decrement(fdf, 'x');
		if (pk < 0)
		{
			decider_dx(fdf, check, color_fade(fdf, i, fdf->px.dx));
			pk = pk + 2 * fdf->px.dy;
		}
		else
		{
			increment_decrement(fdf, 'y');
			decider_dx(fdf, check, color_fade(fdf, i, fdf->px.dx));
			pk = pk + 2 * fdf->px.dy - 2 * fdf->px.dx;
		}
	}
}

void	draw_line_dy(t_fdf *fdf, int check)
{
	int	pk;
	int	i;

	pk = 2 * fdf->px.dx - fdf->px.dy;
	i = -1;
	while (++i < fdf->px.dy)
	{
		increment_decrement(fdf, 'y');
		if (pk < 0)
		{
			decider_dy(fdf, check, color_fade(fdf, i, fdf->px.dy));
			pk = pk + 2 * fdf->px.dx;
		}
		else
		{
			increment_decrement(fdf, 'x');
			decider_dy(fdf, check, color_fade(fdf, i, fdf->px.dy));
			pk = pk + 2 * fdf->px.dx - 2 * fdf->px.dy;
		}
	}
}
