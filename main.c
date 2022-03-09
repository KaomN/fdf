/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/09 12:37:27 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	image_border(t_data data, t_fdf *fdf)
{
	for (int y = 0; y < fdf->winsize.h; y++)
		my_mlx_pixel_put(fdf, 0, y, 0x00FFFFFF);
	for (int y = 0; y < fdf->winsize.w; y++)
		my_mlx_pixel_put(fdf, y, 0, 0x00FFFFFF);
	for (int y = 0; y < fdf->winsize.h; y++)
		my_mlx_pixel_put(fdf, fdf->winsize.w - 1, y, 0x00FFFFFF);
	for (int y = 0; y < fdf->winsize.w; y++)
		my_mlx_pixel_put(fdf, y, fdf->winsize.h - 1, 0x00FFFFFF);
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
	image_border(fdf->mlx, fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}

void	initialize_mlx(t_fdf *fdf)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, fdf->winsize.w, fdf->winsize.h, "fdf");
	fdf->mlx.mlx = mlx;
	fdf->mlx.win = win;
	fdf->mlx.img = mlx_new_image(mlx, fdf->winsize.w, fdf->winsize.h);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel,
			&fdf->mlx.line_length, &fdf->mlx.endian);
	mlx_key_hook(fdf->mlx.win, &events, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, &exit_fdf, fdf);
	render_image(fdf);
	mlx_loop(fdf->mlx.mlx = mlx);
}

void	initialize_fdf(t_fdf *fdf)
{
	fdf->flag.zoom = 1;
	fdf->winsize.w = 1200;
	fdf->winsize.h = 1000;
	fdf->px.pad = 150;
	fdf->flag.h_modifier = 0.25;
	fdf->flag.h = fdf->flag.h_modifier;
	fdf->flag.hori = 0;
	fdf->flag.vert = 0;
}

int	main(void)
{
	int		fd;
	char	*lines;
	t_fdf	fdf;
	int		x;
	size_t	size;

	size = 300;
	fd = open("42.fdf", O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (0);
	}
	x = 0;
	fdf.map.map = (int **)malloc(sizeof(int *) * size);
	while (get_next_line(fd, &lines))
	{
		fdf.map.map[x] = transform_array(lines, &fdf);
		free(lines);
		x++;
	}
	initialize_fdf(&fdf);
	fdf.map.height = x;
	initialize_mlx(&fdf);
	return (0);
}
