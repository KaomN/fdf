/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:37:44 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/09 10:45:57 by conguyen         ###   ########.fr       */
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

static int	ft_abs(int num1, int num2)
{
	if (num1 > num2)
		return (num1 - num2);
	return (num2 - num1);
}

static void	calc_line_horizontal(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = (fdf->winsize.w * 0.37) - (5 * y) * fdf->flag.zoom;
		fdf->px.y1 = ((2.5 * y) * fdf->flag.zoom + fdf->px.pad) - fdf->map.map[y][x] * fdf->flag.h;
	}
	fdf->px.z = (fdf->map.map[y][x] - fdf->map.map[y][x + 1]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 + (5 * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (2.5 * fdf->flag.zoom);
	fdf->px.dx = ft_abs(fdf->px.x2, fdf->px.x1);
	fdf->px.dy = ft_abs(fdf->px.y2, fdf->px.y1);
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
		fdf->px.x1 = (fdf->winsize.w * 0.37) + (5 * y) * fdf->flag.zoom;
		fdf->px.y1 = ((2.5 * y) * fdf->flag.zoom + fdf->px.pad) - fdf->map.map[x][y] * fdf->flag.h;
	}
	fdf->px.z = (fdf->map.map[x][y] - fdf->map.map[x + 1][y]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 - (5 * fdf->flag.zoom);
	fdf->px.y2 = fdf->px.z + fdf->px.y1 + (2.5 * fdf->flag.zoom);
	fdf->px.dx = ft_abs(fdf->px.x2, fdf->px.x1);
	fdf->px.dy = ft_abs(fdf->px.y2, fdf->px.y1);
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
