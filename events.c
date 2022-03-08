/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/08 15:38:32 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	events(int keycode, t_fdf *fdf)
{
	keyboard_event(keycode, fdf);
	zoom_event(keycode, fdf);
	return (0);
}

int	keyboard_event(int keycode, t_fdf *fdf)
{
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
	{
		if (keycode == 119)
			fdf->flag.vert -= 20;
		else if (keycode == 115)
			fdf->flag.vert += 20;
		else if (keycode == 97)
			fdf->flag.hori -= 20;
		else
			fdf->flag.hori += 20;
		render_image(fdf);
		return (0);
	}
	if (keycode == 43 || keycode == 45)
	{
		if (keycode == 43 && fdf->flag.h < 20)
				fdf->flag.h += 0.5;
		if (keycode == 45 && fdf->flag.h > 0)
				fdf->flag.h -= 0.5;
		render_image(fdf);
	}
	if (keycode == 65307)
		exit_fdf(fdf);
	return (0);
}

int	zoom_event(int keycode, t_fdf *fdf)
{
	if (keycode == 105 || keycode == 111)
	{
		if (keycode == 105 && fdf->flag.zoom < 5)
		{
			fdf->flag.zoom += 1;
			fdf->winsize.h *= fdf->flag.zoom;
			fdf->winsize.w *= fdf->flag.zoom;
			fdf->px.pad *= fdf->flag.zoom;
			render_image(fdf);
		}
		else if (keycode == 111 && fdf->flag.zoom > 1)
		{
			fdf->flag.zoom -= 1;
			fdf->winsize.h /= fdf->flag.zoom;
			fdf->winsize.w /= fdf->flag.zoom;
			fdf->px.pad /= fdf->flag.zoom;
			render_image(fdf);
		}
	}
	return (0);
}

int	exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	exit (0);
}
