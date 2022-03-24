/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:42:04 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/24 09:38:26 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	increment_decrement(t_linedata *px, char ch)
{
	if (ch == 'x')
	{
		if (px->x1 < px->x2)
			px->x1 += 1;
		else
			px->x1 -= 1;
	}
	if (ch == 'y')
	{
		if (px->y1 < px->y2)
			px->y1 += 1;
		else
			px->y1 -= 1;
	}
}

static void	decider_dx(t_fdf *fdf, t_linedata px, int check, int color)
{
	if (check == 0)
	{
		if (px.x1 + fdf->flag.hori < fdf->winsize.w
			&& px.y1 + fdf->flag.vert < fdf->winsize.h
			&& px.x1 + fdf->flag.hori >= 0
			&& px.y1 + fdf->flag.vert >= 0)
			my_mlx_pixel_put(fdf, px.x1 + fdf->flag.hori, px.y1
				+ fdf->flag.vert, color);
	}	
	else if (check == 1)
	{
		if (px.y1 + fdf->flag.hori < fdf->winsize.w
			&& px.x1 + fdf->flag.vert < fdf->winsize.h
			&& px.x1 + fdf->flag.vert >= 0
			&& px.y1 + fdf->flag.hori >= 0)
			my_mlx_pixel_put(fdf, px.y1 + fdf->flag.hori, px.x1
				+ fdf->flag.vert, color);
	}
}

static void	decider_dy(t_fdf *fdf, t_linedata px, int check, int color)
{
	if (check == 0)
	{
		if (px.y1 + fdf->flag.hori < fdf->winsize.w
			&& px.x1 + fdf->flag.vert < fdf->winsize.h
			&& px.x1 + fdf->flag.vert >= 0
			&& px.y1 + fdf->flag.hori >= 0)
			my_mlx_pixel_put(fdf, px.y1 + fdf->flag.hori, px.x1
				+ fdf->flag.vert, color);
	}
	else if (check == 1)
	{
		if (px.x1 + fdf->flag.hori < fdf->winsize.w
			&& px.y1 + fdf->flag.vert < fdf->winsize.h
			&& px.x1 + fdf->flag.hori >= 0
			&& px.y1 + fdf->flag.vert >= 0)
			my_mlx_pixel_put(fdf, px.x1 + fdf->flag.hori, px.y1
				+ fdf->flag.vert, color);
	}
}

void	draw_line_dx(t_fdf *fdf, t_linedata px, int check)
{
	int	pk;
	int	i;

	pk = 2 * px.dy - px.dx;
	i = -1;
	while (++i < px.dx)
	{
		increment_decrement(&px, 'x');
		if (pk < 0)
		{
			decider_dx(fdf, px, check, color_flag(fdf, i, fdf->px.dx));
			pk = pk + 2 * px.dy;
		}
		else
		{
			increment_decrement(&px, 'y');
			decider_dx(fdf, px, check, color_flag(fdf, i, fdf->px.dx));
			pk = pk + 2 * px.dy - 2 * px.dx;
		}
	}
}

void	draw_line_dy(t_fdf *fdf, t_linedata px, int check)
{
	int	pk;
	int	i;

	pk = 2 * px.dx - px.dy;
	i = -1;
	while (++i < px.dy)
	{
		increment_decrement(&px, 'y');
		if (pk < 0)
		{
			decider_dy(fdf, px, check, color_flag(fdf, i, fdf->px.dy));
			pk = pk + 2 * px.dx;
		}
		else
		{
			increment_decrement(&px, 'x');
			decider_dy(fdf, px, check, color_flag(fdf, i, fdf->px.dy));
			pk = pk + 2 * px.dx - 2 * px.dy;
		}
	}
}
