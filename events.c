/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:21:38 by conguyen          #+#    #+#             */
/*   Updated: 2022/02/28 09:14:54 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	esc_key(int keycode, void *param)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 43)
		printf("Zoom in\n");
	if (keycode == 45)
		printf("Zoom out\n");
	if (keycode == 119 || keycode == 119)
		printf("Up\n");
	if (keycode == 97 || keycode == 97)
		printf("Left\n");
	if (keycode == 115 || keycode == 115)
		printf("Down\n");
	if (keycode == 100 || keycode == 100)
		printf("Right\n");
}

int	mouse_event(int mouse_button, int x, int y, void *param)
{
	if (mouse_button == 4)
		printf("Zoom in\n");
	if (mouse_button == 5)
		printf("Zoom out\n");
}

int	exit_fdf()
{
	exit (1);
}
