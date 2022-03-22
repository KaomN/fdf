/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:12:42 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/22 16:02:53 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	map_color(t_fdf *fdf, int mod, int distance)
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

static int	get_color_max(t_fdf *fdf, int map_height)
{
	if (map_height >= fdf->map.max * 0.90)
		return (0xFFFFFF);
	if (map_height >= fdf->map.max * 0.80)
		return (0xEAE0E0);
	if (map_height >= fdf->map.max * 0.70)
		return (0xDEC0C0);
	if (map_height >= fdf->map.max * 0.60)
		return (0xD2A0A0);
	if (map_height >= fdf->map.max * 0.50)
		return (0xC68080);
	if (map_height >= fdf->map.max * 0.40)
		return (0xBA6060);
	if (map_height >= fdf->map.max * 0.30)
		return (0xAE4040);
	if (map_height >= fdf->map.max * 0.20)
		return (0xA22020);
	if (map_height >= fdf->map.max * 0.10)
		return (0x9B0000);
	if (map_height >= 0)
		return (0x009B00);
}

static int	get_color_min(t_fdf *fdf, int map_height)
{
	if (map_height >= fdf->map.min * 0.10)
		return (0x00FCF9);
	if (map_height >= fdf->map.min * 0.20)
		return (0x00E0EE);
	if (map_height >= fdf->map.min * 0.30)
		return (0x00C4E3);
	if (map_height >= fdf->map.min * 0.40)
		return (0x00A8D8);
	if (map_height >= fdf->map.min * 0.50)
		return (0x008CCD);
	if (map_height >= fdf->map.min * 0.60)
		return (0x0070C2);
	if (map_height >= fdf->map.min * 0.70)
		return (0x0054B7);
	if (map_height >= fdf->map.min * 0.80)
		return (0x0038AC);
	if (map_height >= fdf->map.min * 0.90)
		return (0x001CA1);
	if (map_height >= fdf->map.min)
		return (0x00009B);
}

static int	fade_color(t_fdf *fdf, int mod, int distance)
{
	if (fdf->map.curr_h >= 0)
		fdf->px.curr_color = get_color_max(fdf, fdf->map.curr_h);
	else
		fdf->px.curr_color = get_color_min(fdf, fdf->map.curr_h);
	if (fdf->map.next_h >= 0)
		fdf->px.next_color = get_color_max(fdf, fdf->map.next_h);
	else
		fdf->px.next_color = get_color_min(fdf, fdf->map.next_h);
	return (map_color(fdf, mod, distance));
}

int	color_flag(t_fdf *fdf, int mod, int distance)
{
	if (!fdf->flag.color)
		return (map_color(fdf, mod, distance));
	else
		return (fade_color(fdf, mod, distance));
}
