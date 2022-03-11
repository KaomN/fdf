/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:25 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/11 09:37:12 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int	*dst;

	dst = (int *)fdf->mlx.addr;
	dst[y * fdf->winsize.w + x] = color;
}

void	clear_image(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->winsize.w)
	{
		y = 0;
		while (y < fdf->winsize.h)
		{
			my_mlx_pixel_put(fdf, x, y, 0x00000000);
			++y;
		}
		++x;
	}
}

void	render_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	clear_image(fdf);
	draw_image(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
