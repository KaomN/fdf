/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/07 09:35:30 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

double	double_abs(double num1, double num2)
{
	if (num1 > num2)
		return (num1 - num2);
	return (num2 - num1);
}

void	draw_image(t_fdf *fdf)
{
	int	y = 0;
	double	pair1 = 0.3;
	for (int x = 0; x < fdf->map.height; x++)
	{
		for (y = 0; y < fdf->map.width - 1; y++)
		{
			if (y == 0)
			{
				fdf->pixel.x1 = (((fdf->win_size.width * 0.45) - (x * (fdf->win_size.width * 0.4 / fdf->map.height))));
				fdf->pixel.y1 = (((x * (fdf->win_size.height * pair1) / fdf->map.height)) + fdf->pixel.padding  - (fdf->map.map[x][y] * fdf->flags.height_flag));
			}
			fdf->pixel.x2 = fdf->pixel.x1 + ((fdf->win_size.width * 0.5 / fdf->map.width));
			fdf->pixel.y2 = ((x * (fdf->win_size.height * pair1) / fdf->map.height) + fdf->pixel.padding) + ((y + 1) * fdf->win_size.height * 0.3 / fdf->map.width) - (fdf->map.map[x][y + 1] * fdf->flags.height_flag);
			fdf->pixel.dx = double_abs(fdf->pixel.x2, fdf->pixel.x1);
			fdf->pixel.dy = double_abs(fdf->pixel.y2, fdf->pixel.y1);
			if (fdf->pixel.dx > fdf->pixel.dy)
				draw_line_dx(fdf->mlx, fdf->pixel, 0, get_color(fdf, x, y, 0));
			else
				draw_line_dy(fdf->mlx, fdf->pixel, 1, get_color(fdf, x, y, 0));
			fdf->pixel.x1 = fdf->pixel.x2;
			fdf->pixel.y1 = fdf->pixel.y2;
		}
	}
	y = 0;
	for (int x = 0; x < fdf->map.width; x++)
	{
		for (y = 0; y < fdf->map.height - 1; y++)
		{
			if (y == 0)
			{
				fdf->pixel.x1 = ((x * ((fdf->win_size.height * 0.6) / fdf->map.width)) + (fdf->win_size.width * 0.45));
				fdf->pixel.y1 = (x * ((fdf->win_size.height * 0.3) / fdf->map.width) + fdf->pixel.padding - (fdf->map.map[y][x] * fdf->flags.height_flag));
			}
			fdf->pixel.x2 = ((fdf->win_size.width * 0.45) + (x * (fdf->win_size.width * 0.5 / fdf->map.width))) - ((y + 1) * (fdf->win_size.width * 0.4 / fdf->map.height));
			fdf->pixel.y2 = (((y + 1) * (fdf->win_size.height * 0.3) / fdf->map.height) + fdf->pixel.padding) + (x * fdf->win_size.height * 0.3 / fdf->map.width) - (fdf->map.map[y + 1][x] * fdf->flags.height_flag);
			fdf->pixel.dx = double_abs(fdf->pixel.x2, fdf->pixel.x1);
			fdf->pixel.dy = double_abs(fdf->pixel.y2, fdf->pixel.y1);
			if (fdf->pixel.dx > fdf->pixel.dy)
				draw_line_dx(fdf->mlx, fdf->pixel, 0, get_color(fdf, y, x, 1));
			else
				draw_line_dy(fdf->mlx, fdf->pixel, 1, get_color(fdf, y, x, 1));
			fdf->pixel.x1 = fdf->pixel.x2;
			fdf->pixel.y1 = fdf->pixel.y2;
		}
	}
}

void	image_border(t_data data, t_fdf *fdf)
{
	for (int y = 0; y < fdf->win_size.height; y++)
		my_mlx_pixel_put(&data, 0, y, 0x00FFFFFF);
		
	for (int y = 0; y < fdf->win_size.width; y++)
		my_mlx_pixel_put(&data, y, 0, 0x00FFFFFF);

	for (int y = 0; y < fdf->win_size.height; y++)
		my_mlx_pixel_put(&data, fdf->win_size.width - 1, y, 0x00FFFFFF);
		
	for (int y = 0; y < fdf->win_size.width; y++)
		my_mlx_pixel_put(&data, y, fdf->win_size.height - 1, 0x00FFFFFF);
}

void	clear_image(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	while (x < fdf->win_size.width)
	{
		y = 0;
		while (y < fdf->win_size.height)
		{
			my_mlx_pixel_put(&fdf->mlx, x, y, 0x00000000);
			++y;
		}
		++x;
	}
}

void	zoom_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	//free(fdf->mlx.addr);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->win_size.width, fdf->win_size.height);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel,
			&fdf->mlx.line_length, &fdf->mlx.endian);
	draw_image(fdf);
	image_border(fdf->mlx, fdf);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, fdf->flags.hori, fdf->flags.vert);
}

void	move_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, fdf->flags.hori, fdf->flags.vert);
}

void	render_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	clear_image(fdf);
	draw_image(fdf);
	image_border(fdf->mlx, fdf);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, fdf->flags.hori, fdf->flags.vert);
}

void	initialize_mlx(t_fdf *fdf)
{
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, fdf->win_size.width, fdf->win_size.height, "fdf");
	fdf->mlx.mlx = mlx;
	fdf->mlx.win = win;
	fdf->mlx.img = mlx_new_image(mlx, fdf->win_size.width, fdf->win_size.height);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel,
			&fdf->mlx.line_length, &fdf->mlx.endian);
	mlx_key_hook(fdf->mlx.win, &keyb_event, fdf);
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
	fdf->win_size.width = 1200;
	fdf->win_size.height = 1000;
	fdf->pixel.padding = 150;
	fdf->flags.zoom_flag = 1.0;
	fdf->flags.height_flag = 4;
	fdf->flags.hori = 0;
	fdf->flags.vert = 0;
}

int	main(void)
{
	int		fd;
	char	*lines;
	t_fdf	fdf;
	int		x;
	size_t	size;

	size = 300;
	fd = open("100-6.fdf", O_RDONLY);
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
	printf("%d", fdf.map.map[0][18]);
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
