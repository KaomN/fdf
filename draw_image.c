/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:37:44 by conguyen          #+#    #+#             */
/*   Updated: 2022/06/24 19:07:11 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calc_delta(t_fdf *fdf)
{
	fdf->px.dx = abs((int)fdf->px.x1 - (int)fdf->px.x2);
	fdf->px.dy = abs((int)fdf->px.y1 - (int)fdf->px.y2);
}

static void	get_max_min(t_fdf *fdf, int y, int x)
{
	if (fdf->map.max < fdf->map.map[y][x])
		fdf->map.max = fdf->map.map[y][x];
	if (fdf->map.min > fdf->map.map[y][x])
		fdf->map.min = fdf->map.map[y][x];
	fdf->map.curr_h = fdf->map.map[y][x];
	fdf->map.next_h = fdf->map.map[y][x + 1];
}

static void	calc_line_horizontal(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = 400 - fdf->px.pad_w
			- (fdf->flag.proj_x * y) * fdf->flag.zoom;
		fdf->px.y1 = ((fdf->flag.proj_y * y) * fdf->flag.zoom + fdf->px.pad_h
				- fdf->flag.zoom * 20) - fdf->map.map[y][x] * fdf->flag.h / 10;
	}
	fdf->px.z = (fdf->map.map[y][x] - fdf->map.map[y][x + 1])
		* fdf->flag.h / 10;
	fdf->px.x2 = fdf->px.x1 + (fdf->flag.isom_x * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (fdf->flag.para_y * fdf->flag.zoom);
	if (y == 0 && x == fdf->map.width - 2)
		fdf->flag.pad_modifier = (fdf->px.x2 - 400) / 2;
	fdf->px.dx = fdf->px.x1 - fdf->px.x2;
	fdf->px.curr_color = fdf->map.color[y][x];
	fdf->px.next_color = fdf->map.color[y][x + 1];
	calc_delta(fdf);
	get_max_min(fdf, y, x);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, fdf->px, 0);
	else
		draw_line_dy(fdf, fdf->px, 1);
	fdf->px.y1 = fdf->px.y2;
	fdf->px.x1 = fdf->px.x2;
}

static void	calc_line_vertical(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = 401 - fdf->px.pad_w
			- (fdf->flag.proj_x * y) * fdf->flag.zoom;
		fdf->px.y1 = ((fdf->flag.proj_y * y) * fdf->flag.zoom + fdf->px.pad_h
				- fdf->flag.zoom * 20) - fdf->map.map[y][x] * fdf->flag.h / 10;
	}
	fdf->px.z = (fdf->map.map[y][x] - fdf->map.map[y + 1][x])
		* fdf->flag.h / 10;
	fdf->px.x2 = fdf->px.x1 - (fdf->flag.proj_x * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (fdf->flag.proj_y * fdf->flag.zoom);
	fdf->px.curr_color = fdf->map.color[y][x];
	fdf->px.next_color = fdf->map.color[y + 1][x];
	fdf->map.curr_h = fdf->map.map[y][x];
	fdf->map.next_h = fdf->map.map[y + 1][x];
	calc_delta(fdf);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, fdf->px, 0);
	else
		draw_line_dy(fdf, fdf->px, 1);
}

void	draw_image(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (y != fdf->map.height - 1)
				calc_line_vertical(fdf, y, x);
			if (x != fdf->map.width - 1)
				calc_line_horizontal(fdf, y, x);
			x++;
		}
		y++;
	}
}
