/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:42:04 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/04 08:22:26 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	increment_decrement(t_linedata pixel, char ch)
{
	if (ch == 'x')
	{
		if (pixel.x1 < pixel.x2)
			pixel.x1++;
		else
			pixel.x1--;
		return (pixel.x1);
	}
	if (ch == 'y')
	{
		if (pixel.y1 < pixel.y2)
			pixel.y1++;
		else
			pixel.y1--;
		return (pixel.y1);
	}
	return (0);
}

static void	decider_dx(t_data data, t_linedata pixel, int check, int color)
{
	if (check == 0)
		my_mlx_pixel_put(&data, pixel.x1, pixel.y1, color);
	else
		my_mlx_pixel_put(&data, pixel.y1, pixel.x1, color);
}

static void	decider_dy(t_data data, t_linedata pixel, int check, int color)
{
	if (check == 0)
		my_mlx_pixel_put(&data, pixel.y1, pixel.x1, color);
	else
		my_mlx_pixel_put(&data, pixel.x1, pixel.y1, color);
}

void	draw_line_dx(t_data data, t_linedata pixel, int check, int color)
{
	int	pk;
	int	i;

	pk = 2 * pixel.dy - pixel.dx;
	i = -1;
	while (++i <= pixel.dx)
	{
		pixel.x1 = increment_decrement(pixel, 'x');
		if (pk < 0)
		{
			decider_dx(data, pixel, check, color);
			pk = pk + 2 * pixel.dy;
		}
		else
		{
			pixel.y1 = increment_decrement(pixel, 'y');
			decider_dx(data, pixel, check, color);
			pk = pk + 2 * pixel.dy - 2 * pixel.dx;
		}
	}
}

void	draw_line_dy(t_data data, t_linedata pixel, int check, int color)
{
	int	pk;
	int	i;

	pk = 2 * pixel.dx - pixel.dy;
	i = -1;
	while (++i <= pixel.dy)
	{
		pixel.y1 = increment_decrement(pixel, 'y');
		if (pk < 0)
		{
			decider_dy(data, pixel, check, color);
			pk = pk + 2 * pixel.dx;
		}
		else
		{
			pixel.x1 = increment_decrement(pixel, 'x');
			decider_dy(data, pixel, check, color);
			pk = pk + 2 * pixel.dx - 2 * pixel.dy;
		}
	}
}
