/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/22 11:18:35 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	initialize_mlx(t_fdf *fdf)
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

static void	initialize_fdf(t_fdf *fdf)
{
	fdf->flag.zoom = 3;
	fdf->winsize.w = 1400;
	fdf->winsize.h = 1000;
	fdf->px.pad_h = 250;
	fdf->px.pad_w = 0;
	fdf->flag.h_modifier = 1;
	fdf->flag.h = fdf->flag.h_modifier * fdf->flag.zoom;
	fdf->flag.color = 0;
	fdf->flag.hori = 0;
	fdf->flag.vert = 0;
	fdf->flag.proj_y = 1;
	fdf->flag.proj_x = 2;
	fdf->flag.para_y = 1;
	fdf->flag.isom_x = 2;
	fdf->flag.projection = 0;
}

static int	**inc_size(int **old_arr, int old_size, int new_size, int width)
{
	int	**new_arr;
	int	x;

	new_arr = (int **)malloc(sizeof(int *) * new_size);
	x = 0;
	while (x < old_size)
	{
		new_arr[x] = (int *)malloc(sizeof(int) * width);
		ft_memcpy(new_arr[x], old_arr[x], width * sizeof(int));
		free(old_arr[x]);
		x++;
	}
	free(old_arr);
	return (new_arr);
}

static void	get_line(t_fdf *fdf, int fd, size_t size)
{
	char	*lines;

	while (get_next_line(fd, &lines))
	{
		if (size == (unsigned int)fdf->map.height)
		{
			size *= 2;
			fdf->map.map = inc_size(fdf->map.map, size / 2,
					size, fdf->map.width);
			fdf->map.color = inc_size(fdf->map.color, size / 2,
					size, fdf->map.width);
		}
		transform_array(lines, fdf);
		free(lines);
		fdf->map.height++;
	}
	free(lines);
}

int	main(void)
{
	int		fd;
	t_fdf	fdf;
	size_t	size;

	size = 32;
	fd = open("42.fdf", O_RDONLY);
	ft_bzero(&fdf, sizeof(t_fdf));
	if (fd < 0)
		ft_putstr("Error\n");
	if (fd < 0)
		return (0);
	fdf.map.map = (int **)malloc(sizeof(int *) * size);
	fdf.map.color = (int **)malloc(sizeof(int *) * size);
	get_line(&fdf, fd, size);
	initialize_fdf(&fdf);
	initialize_mlx(&fdf);
	return (0);
}
