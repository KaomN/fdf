/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/10 08:59:25 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	events(int keycode, t_fdf *fdf)
{
	// printf("%d\n", keycode);
	move_event(keycode, fdf);
	zoom_event(keycode, fdf);
	height_event(keycode, fdf);
	return (0);
}

int	move_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_W || keycode == KEY_UP)
			fdf->flag.vert -= 20 + fdf->flag.zoom;
		else if (keycode == KEY_S || keycode == KEY_DOWN)
			fdf->flag.vert += 20 + fdf->flag.zoom;
		else if (keycode == KEY_A || keycode == KEY_LEFT)
			fdf->flag.hori -= 20 + fdf->flag.zoom;
		else
			fdf->flag.hori += 20 + fdf->flag.zoom;
	}
	render_image(fdf);
	return (0);
}

int	height_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS || keycode == KEY_PLUS_PAD
		|| keycode == KEY_MINUS_PAD)
	{
		if ((keycode == KEY_PLUS || keycode == KEY_PLUS_PAD)
			&& fdf->flag.h < 5 * fdf->flag.zoom)
		{
			fdf->flag.h_modifier += 0.25;
			fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
		}
		if ((keycode == KEY_MINUS || keycode == KEY_MINUS_PAD)
			&& fdf->flag.h > -5 * fdf->flag.zoom)
		{
			fdf->flag.h_modifier -= 0.25;
			fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
		}
	}
	if (keycode == KEY_ESC)
		exit_fdf(fdf);
	render_image(fdf);
	return (0);
}

int	zoom_event(int keycode, t_fdf *fdf)
{
	if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
	{
		if (keycode == ZOOM_IN && fdf->flag.zoom < 20)
		{
			fdf->flag.zoom += 1;
			fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
		}
		else if (keycode == ZOOM_OUT && fdf->flag.zoom > 1)
		{
			fdf->flag.zoom -= 1;
			fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
		}
	}
	render_image(fdf);
	return (0);
}

int	exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	exit (0);
}
