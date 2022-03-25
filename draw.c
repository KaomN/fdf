/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:25 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/25 12:48:31 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_helper(t_fdf *fdf)
{
	void	*mlx;
	void	*win;
	int		x;

	mlx = fdf->mlx.mlx;
	win = fdf->mlx.win;
	x = fdf->winsize.w - 260;
	mlx_string_put(mlx, win, x - 20, 20, 0xFFFFFF, "Usage");
	mlx_string_put(mlx, win, x, 50, 0xFFFFFF, "Move            Arrowkeys");
	mlx_string_put(mlx, win, x, 75, 0xFFFFFF, "Move            W A S D");
	mlx_string_put(mlx, win, x, 100, 0xFFFFFF, "Height          + -");
	mlx_string_put(mlx, win, x, 125, 0xFFFFFF, "Zoom in         I");
	mlx_string_put(mlx, win, x, 150, 0xFFFFFF, "Zoom out        O");
	mlx_string_put(mlx, win, x, 175, 0xFFFFFF, "Projection      P");
	mlx_string_put(mlx, win, x, 200, 0xFFFFFF, "Colortheme      C");
}

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
	draw_helper(fdf);
	mlx_key_hook(fdf->mlx.win, &events, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, &exit_fdf, fdf);
	mlx_loop(fdf->mlx.mlx);
}
