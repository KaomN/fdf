/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:42:04 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/09 14:37:29 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	increment_decrement(t_linedata px, char ch)
{
	if (ch == 'x')
	{
		if (px.x1 < px.x2)
			return (++px.x1);
		return (--px.x1);
	}
	if (ch == 'y')
	{
		if (px.y1 < px.y2)
			return (++px.y1);
		return (--px.y1);
	}
	return (0);
}

static void	decider_dx(t_fdf *fdf, t_linedata px, int check, int color)
{
	if (check == 0)
	{
		px.x1 += fdf->flag.hori;
		px.y1 += fdf->flag.vert;
		if (px.x1 < fdf->winsize.w && px.y1 < fdf->winsize.h
			&& px.x1 >= 0 && px.y1 >= 0)
			my_mlx_pixel_put(fdf, px.x1, px.y1, color);
	}	
	else if (check == 1)
	{
		px.y1 += fdf->flag.hori;
		px.x1 += fdf->flag.vert;
		if (px.y1 < fdf->winsize.w && px.x1 < fdf->winsize.h
			&& px.x1 >= 0 && px.y1 >= 0)
			my_mlx_pixel_put(fdf, px.y1, px.x1, color);
	}
}

static void	decider_dy(t_fdf *fdf, t_linedata px, int check, int color)
{
	if (check == 0)
	{
		px.y1 += fdf->flag.hori;
		px.x1 += fdf->flag.vert;
		if (px.y1 < fdf->winsize.w && px.x1 < fdf->winsize.h
			&& px.x1 >= 0 && px.y1 >= 0)
			my_mlx_pixel_put(fdf, px.y1, px.x1, color);
	}
	else if (check == 1)
	{
		px.x1 += fdf->flag.hori;
		px.y1 += fdf->flag.vert;
		if (px.x1 < fdf->winsize.w && px.y1 < fdf->winsize.h
			&& px.x1 >= 0 && px.y1 >= 0)
			my_mlx_pixel_put(fdf, px.x1, px.y1, color);
	}
}

void	draw_line_dx(t_fdf *fdf, int check, int color)
{
	int	pk;
	int	i;

	pk = 2 * fdf->px.dy - fdf->px.dx;
	i = -1;
	while (++i < fdf->px.dx)
	{
		fdf->px.x1 = increment_decrement(fdf->px, 'x');
		if (pk < 0)
		{
			decider_dx(fdf, fdf->px, check, color);
			pk = pk + 2 * fdf->px.dy;
		}
		else
		{
			fdf->px.y1 = increment_decrement(fdf->px, 'y');
			decider_dx(fdf, fdf->px, check, color);
			pk = pk + 2 * fdf->px.dy - 2 * fdf->px.dx;
		}
	}
}

void	draw_line_dy(t_fdf *fdf, int check, int color)
{
	int	pk;
	int	i;

	pk = 2 * fdf->px.dx - fdf->px.dy;
	i = -1;
	while (++i < fdf->px.dy)
	{
		fdf->px.y1 = increment_decrement(fdf->px, 'y');
		if (pk < 0)
		{
			decider_dy(fdf, fdf->px, check, color);
			pk = pk + 2 * fdf->px.dx;
		}
		else
		{
			fdf->px.x1 = increment_decrement(fdf->px, 'x');
			decider_dy(fdf, fdf->px, check, color);
			pk = pk + 2 * fdf->px.dx - 2 * fdf->px.dy;
		}
	}
}
