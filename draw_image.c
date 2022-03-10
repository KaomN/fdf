/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:37:44 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/10 14:42:58 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_color(t_fdf *fdf, int x, int y, int check)
{
	if (check == 0)
	{
		if (fdf->map.map[x][y] < fdf->map.map[x][y + 1])
			return (0x00FF0000);
		else if (fdf->map.map[x][y] > fdf->map.map[x][y + 1])
			return (0x00FF0000);
	}
	else
	{
		if (fdf->map.map[x][y] < fdf->map.map[x + 1][y])
			return (0x00FF0000);
		else if (fdf->map.map[x][y] > fdf->map.map[x + 1][y])
			return (0x00FF0000);
	}
	return (0x00FFFFFF);
}

static void	calc_delta(t_fdf *fdf)
{
	fdf->px.dx = fdf->px.x1 - fdf->px.x2;
	if (fdf->px.dx < 0)
		fdf->px.dx = -fdf->px.dx;
	fdf->px.dy = fdf->px.y1 - fdf->px.y2;
	if (fdf->px.dy < 0)
		fdf->px.dy = -fdf->px.dy;
}

static void	calc_line_horizontal(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = (fdf->winsize.w * 0.37) - fdf->px.pad_w - (fdf->flag.proj_x * y)
			* fdf->flag.zoom;
		fdf->px.y1 = ((fdf->flag.proj_y * y) * fdf->flag.zoom + fdf->px.pad_h
				- fdf->flag.zoom * 20) - fdf->map.map[y][x] * fdf->flag.h;
	}
	fdf->px.z = (fdf->map.map[y][x] - fdf->map.map[y][x + 1]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 + (fdf->flag.isom_x * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (fdf->flag.para_y * fdf->flag.zoom);
	// fdf->px.y2 = fdf->px.z + fdf->px.y1;
	calc_delta(fdf);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, 0, get_color(fdf, y, x, 0));
	else
		draw_line_dy(fdf, 1, get_color(fdf, y, x, 0));
	fdf->px.y1 = fdf->px.y2;
	fdf->px.x1 = fdf->px.x2;
}

static void	calc_line_vertical(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = (fdf->winsize.w * 0.37) - fdf->px.pad_w + (fdf->flag.isom_x * y)
			* fdf->flag.zoom;
		fdf->px.y1 = ((fdf->flag.para_y * y) * fdf->flag.zoom + (fdf->px.pad_h
				- fdf->flag.zoom * 20)) - fdf->map.map[x][y] * fdf->flag.h;
		// fdf->px.y1 = (((fdf->px.pad - fdf->flag.zoom * 20)) - fdf->map.map[x][y] * fdf->flag.h);
	}
	fdf->px.z = (fdf->map.map[x][y] - fdf->map.map[x + 1][y]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 - (fdf->flag.proj_x * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (fdf->flag.proj_y * fdf->flag.zoom);
	calc_delta(fdf);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, 0, get_color(fdf, x, y, 1));
	else
		draw_line_dy(fdf, 1, get_color(fdf, x, y, 1));
	fdf->px.y1 = fdf->px.y2;
	fdf->px.x1 = fdf->px.x2;
}

void	draw_image(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width - 1)
		{
			calc_line_horizontal(fdf, y, x);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < fdf->map.width)
	{
		x = 0;
		while (x < fdf->map.height - 1)
		{
			calc_line_vertical(fdf, y, x);
			x++;
		}
		y++;
	}
}
