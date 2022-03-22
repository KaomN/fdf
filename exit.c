/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:56:18 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/22 10:58:48 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	exit (0);
}

void	error_exit(char **lines)
{
	int	x;

	x = 0;
	while (lines[x] != NULL)
	{
		free(lines[x++]);
	}
	free(lines);
	exit (0);
}