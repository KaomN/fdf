/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/05 13:34:30 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keyb_event(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit_fdf(fdf);
	//printf("%d\n", keycode);
	if (keycode == 105 || keycode == 111)
	{
		if (keycode == 105 && fdf->flags.zoom_flag < 2.5)
		{
			fdf->flags.zoom_flag += 0.1;
			fdf->win_size.height *= 1.1;
			fdf->win_size.width *= 1.1;
			fdf->pixel.padding *= 1.1;
			zoom_image(fdf);
		}
		else if (keycode == 111 && fdf->flags.zoom_flag > 0.3)
		{
			fdf->flags.zoom_flag -= 0.1;
			fdf->win_size.height *= 0.9;
			fdf->win_size.width *= 0.9;
			fdf->pixel.padding *= 0.9;
			zoom_image(fdf);
		}
		return (0);
	}
	if (keycode == 119 || keycode == 115)
	{
		if (keycode == 119)
			fdf->flags.vert += 20 * fdf->flags.zoom_flag;
		else
			fdf->flags.vert -= 20 * fdf->flags.zoom_flag;
		move_image(fdf);
		return (0);
	}
	if (keycode == 97 || keycode == 100)
	{
		if (keycode == 97)
			fdf->flags.hori += 20 * fdf->flags.zoom_flag;
		else
			fdf->flags.hori -= 20 * fdf->flags.zoom_flag;
		move_image(fdf);
		return (0);
	}
	if (keycode == 43) // zoom in
		if (fdf->flags.height_flag < 10)
			fdf->flags.height_flag += 1;
	if (keycode == 45) // Zoom out
		if (fdf->flags.height_flag > 0)
			fdf->flags.height_flag -= 1;
	render_image(fdf);
	return (0);
}

// int	mouse_event(int mouse_button, t_fdf *fdf)
// {
// 	if (mouse_button == 4) // zoom in
// 		printf("Zoom in\n");
// 		// if (fdf->flags.zoom_flag < 1)
// 		// 	fdf->flags.zoom_flag += 0.1;
// 	if (mouse_button == 5) // zoom out
// 	{
// 		printf("Zoom out\n");
// 		// if (fdf->flags.zoom_flag > 0.1)
// 		// 	fdf->flags.zoom_flag -= 0.05;
// 	}

// 	//draw_window(fdf);
// }

int	exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	exit (0);
}
