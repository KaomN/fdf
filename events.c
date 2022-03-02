/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/02 09:14:14 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	esc_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 43) // zoom in
		if (fdf->flags.zoom_flag < 2)
			fdf->flags.zoom_flag += 0.1;
	if (keycode == 45) // Zoom out
		if (fdf->flags.zoom_flag > 0.2)
			fdf->flags.zoom_flag -= 0.1;
	if (keycode == 119 || keycode == 119)
		printf("Up\n");
	if (keycode == 97 || keycode == 97)
		printf("Left\n");
	if (keycode == 115 || keycode == 115)
		printf("Down\n");
	if (keycode == 100 || keycode == 100)
		printf("Right\n");
	render_image(fdf);
}

int	mouse_event(int mouse_button, t_fdf *fdf)
{
	if (mouse_button == 4) // zoom in
		printf("Zoom in\n");
		// if (fdf->flags.zoom_flag < 1)
		// 	fdf->flags.zoom_flag += 0.1;
	if (mouse_button == 5) // zoom out
	{
		printf("Zoom out\n");
		// if (fdf->flags.zoom_flag > 0.1)
		// 	fdf->flags.zoom_flag -= 0.05;
	}

	//draw_window(fdf);
}

int	exit_fdf()
{
	exit (0);
}
