/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:12:42 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/21 13:50:42 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	coloring(t_fdf *fdf, int mod, int distance)
{
	if (fdf->flag.color == 0)
		return (color_fade(fdf, mod, distance));
	//if (fdf->flag.color == 1)

	//if (fdf->flag.color == 3)
	return (0);
}