/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/25 12:48:09 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	move_zoom_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		fdf->flag.vert -= 20 + fdf->flag.zoom;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		fdf->flag.vert += 20 + fdf->flag.zoom;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		fdf->flag.hori -= 20 + fdf->flag.zoom;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		fdf->flag.hori += 20 + fdf->flag.zoom;
	if (keycode == ZOOM_IN && fdf->flag.zoom < 20)
	{
		fdf->flag.zoom += 1;
		fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
	}
	if (keycode == ZOOM_OUT && fdf->flag.zoom > 1)
	{
		fdf->flag.zoom -= 1;
		fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
	}
	return (0);
}

static int	color_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_C)
		fdf->flag.color = !fdf->flag.color;
	return (0);
}

static int	height_event(int keycode, t_fdf *fdf)
{
	if ((keycode == KEY_PLUS || keycode == KEY_PLUS_PAD)
		&& fdf->flag.h < 30 * fdf->flag.zoom)
	{
		fdf->flag.h_modifier += 1;
		fdf->flag.h = (fdf->flag.h_modifier * fdf->flag.zoom);
	}
	if ((keycode == KEY_MINUS || keycode == KEY_MINUS_PAD)
		&& fdf->flag.h > -30 * fdf->flag.zoom)
	{
		fdf->flag.h_modifier -= 1;
		fdf->flag.h = (fdf->flag.h_modifier * fdf->flag.zoom);
	}
	return (0);
}

static int	projection_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_P)
	{
		fdf->flag.projection = !fdf->flag.projection;
		if (fdf->flag.projection)
		{
			fdf->flag.para_y = 0;
			fdf->flag.proj_x = -2;
			fdf->px.pad_w = fdf->flag.pad_modifier;
		}
		else
		{
			fdf->flag.para_y = 1;
			fdf->flag.proj_x = 2;
			fdf->px.pad_w = fdf->flag.pad_modifier * -1;
		}
	}
	render_image(fdf);
	return (0);
}

int	events(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		exit_fdf(fdf);
	move_zoom_event(keycode, fdf);
	color_event(keycode, fdf);
	height_event(keycode, fdf);
	projection_event(keycode, fdf);
	return (0);
}
