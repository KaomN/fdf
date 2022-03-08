/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/08 15:38:39 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int	*dst;

	dst = (int *)fdf->mlx.addr;
	dst[y * fdf->winsize.w + x] = color;
}

int	get_color(t_fdf *fdf, int x, int y, int check)
{
	if (check == 0)
	{
		if (fdf->map.map[x][y] < fdf->map.map[x][y + 1])
			return (0x00FF0000);
		else if (fdf->map.map[x][y] > fdf->map.map[x][y + 1])
			return (0x00FF0000);
	}
	else
	{
		if (fdf->map.map[x][y] < fdf->map.map[x + 1][y])
			return (0x00FF0000);
		else if (fdf->map.map[x][y] > fdf->map.map[x + 1][y])
			return (0x00FF0000);
	}
	return (0x00FFFFFF);
}

int	double_abs(int num1, int num2)
{
	if (num1 > num2)
		return (num1 - num2);
	return (num2 - num1);
}

void	calc_z(t_fdf *fdf, int y, int x)
{
	fdf->px.z = fdf->map.map[y][x] - fdf->map.map[y][x + 1];
	printf("%d\n", fdf->px.z);
}

void	calc_line_vertical(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = (fdf->winsize.w * 0.37) - 40 * y;
		fdf->px.y1 = (20 * y + fdf->px.pad) - fdf->map.map[y][x] * fdf->flag.h;
	}
	fdf->px.z = (fdf->map.map[y][x] - fdf->map.map[y][x + 1]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 + 40;
	fdf->px.y2 = fdf->px.z + (fdf->px.y1 + 20);
	fdf->px.dx = double_abs(fdf->px.x2, fdf->px.x1);
	fdf->px.dy = double_abs(fdf->px.y2, fdf->px.y1);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, 0, get_color(fdf, y, x, 0));
	else
		draw_line_dy(fdf, 1, get_color(fdf, y, x, 0));
	fdf->px.y1 = fdf->px.y2;
	fdf->px.x1 = fdf->px.x2;
}

void calc_line_horizontal(t_fdf *fdf, int y, int x)
{
	if (x == 0)
	{
		fdf->px.x1 = (fdf->winsize.w * 0.37) + 40 * y;
		fdf->px.y1 = (20 * y + fdf->px.pad) - fdf->map.map[x][y] * fdf->flag.h;
	}
	fdf->px.z = (fdf->map.map[x][y] - fdf->map.map[x + 1][y]) * fdf->flag.h;
	fdf->px.x2 = fdf->px.x1 - 40;
	fdf->px.y2 = fdf->px.z + (fdf->px.y1 + 20);
	fdf->px.dx = double_abs(fdf->px.x2, fdf->px.x1);
	fdf->px.dy = double_abs(fdf->px.y2, fdf->px.y1);
	if (fdf->px.dx > fdf->px.dy)
		draw_line_dx(fdf, 0, get_color(fdf, x, y, 1));
	else
		draw_line_dy(fdf, 1, get_color(fdf, x, y, 1));
	fdf->px.y1 = fdf->px.y2;
	fdf->px.x1 = fdf->px.x2;
}

void	draw_image(t_fdf *fdf)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width - 1)
		{
			calc_line_vertical(fdf, y, x);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < fdf->map.width)
	{
		x = 0;
		while (x < fdf->map.height - 1)
		{
			calc_line_horizontal(fdf, y, x);
			x++;
		}
		y++;
	}
}

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
	int x;
	int y;

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

void	zoom_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->winsize.w, fdf->winsize.h);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel,
			&fdf->mlx.line_length, &fdf->mlx.endian);
	draw_image(fdf);
	image_border(fdf->mlx, fdf);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, 0, 0);
}

void	render_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	clear_image(fdf);
	draw_image(fdf);
	image_border(fdf->mlx, fdf);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, 0, 0);
}

void	initialize_mlx(t_fdf *fdf)
{
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, fdf->winsize.w, fdf->winsize.h, "fdf");
	fdf->mlx.mlx = mlx;
	fdf->mlx.win = win;
	fdf->mlx.img = mlx_new_image(mlx, fdf->winsize.w, fdf->winsize.h);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel,
			&fdf->mlx.line_length, &fdf->mlx.endian);
	mlx_key_hook(fdf->mlx.win, &events, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, &exit_fdf, fdf); // exit 'x' button on top right
	render_image(fdf);
	mlx_loop(fdf->mlx.mlx = mlx);
}

void	free_str_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}

int	get_length(char *line)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	while (line[x] != '\0')
		if (ft_isdigit(line[x++]))
			len++;
	return (len);
}

int	*transform_array(char *lines)
{
	int		*int_arr;
	char	**lines_arr;
	int		x;
	size_t	size;

	size = 300;
	lines_arr = ft_strsplit(lines, ' ');
	int_arr = (int *)malloc(sizeof(int) * size);
	x = 0;
	while (lines_arr[x] != NULL)
	{
		int_arr[x] = ft_atoi(lines_arr[x]);
		x++;
	}
	free_str_arr(lines_arr);
	return (int_arr);
}

void	initialize_fdf(t_fdf *fdf)
{
	fdf->flag.zoom = 1;
	fdf->winsize.w = 1200;
	fdf->winsize.h = 1000;
	fdf->px.pad = 150;
	fdf->flag.h = 0.5;
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
		if (x == 0)
			fdf.map.width = get_length(lines);
		fdf.map.map[x] = transform_array(lines);
		free(lines);
		x++;
	}
	// for (int c = 0; c < x; c++)
	// {
	// 	for (int y = 0; y < fdf.map.width; y++)
	// 	{
	// 		printf("[%d]", fdf.map.map[c][y]);
	// 	}
	// 	printf("\n");
	// }
	initialize_fdf(&fdf);
	fdf.map.height = x;
	initialize_mlx(&fdf);
	return (0);
}
