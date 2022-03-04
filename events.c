/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/04 08:33:10 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	esc_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 43)
		if (fdf->flags.zoom_flag < 2)
			fdf->flags.zoom_flag += 0.1;
	if (keycode == 45)
		if (fdf->flags.zoom_flag > 0.2)
			fdf->flags.zoom_flag -= 0.1;
	if (keycode == 119 || keycode == 119)
		fdf->flags.vert -= 20;
	if (keycode == 97 || keycode == 97)
		fdf->flags.hori -= 20;
	if (keycode == 115 || keycode == 115)
		fdf->flags.vert += 20;
	if (keycode == 100 || keycode == 100)
		fdf->flags.hori += 20;
	render_image(fdf);
}

int	mouse_event(int mouse_button, t_fdf *fdf)
{
	if (mouse_button == 4)
		printf("Zoom in\n");
	if (mouse_button == 5)
		printf("Zoom out\n");
}

int	exit_fdf(void)
{
	exit (0);
}
