/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/02/28 12:52:05 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_image(t_fdf *fdf, int height, int width)
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_linedata	pixel;
	int			y = 0;
	double		zoom = 1;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1250, 800, "fdf");
	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&pixel, sizeof(t_linedata));
	data.mlx = mlx;
	data.win = win;
	data.img = mlx_new_image(mlx, 1250, 800);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	for (int x = 0; x < fdf->map.height; x++)
	{
		for (y = 0; y < fdf->map.width - 1; y++)
		{
			if (y == 0)
			{
				pixel.x1 = ((y * 35 + 450) - (x * 40)) * zoom;
				pixel.y1 = ((x * 35 + 50) + (y * 20)) * zoom;
			}
			if (fdf->map.map[x][y] < fdf->map.map[x][y + 1])
			{
				pixel.x2 = (((y + 1) * 35 + 450) - (x * 40)) * zoom;
				pixel.y2 = (((x * 35 + 50) + ((y + 1) * 20)) - (fdf->map.map[x][y + 1] * 4)) * zoom;
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FF0000);
				else
					draw_line_dy(data, pixel, 1, 0x00FF0000);
				printf("from: %d,%d to: %d,%d\n", pixel.x1, pixel.y1, pixel.x2, pixel.y2);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else if (fdf->map.map[x][y] > fdf->map.map[x][y + 1])
			{
				pixel.x2 = (((y + 1) * 35 + 450) - (x * 40)) * zoom;
				pixel.y2 = ((x * 35 + 50) + ((y + 1) * 20)) * zoom;
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FF0000);
				else
					draw_line_dy(data, pixel, 1, 0x00FF0000);
				printf("from: %d,%d to: %d,%d\n", pixel.x1, pixel.y1, pixel.x2, pixel.y2);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else
			{
				pixel.x2 = (((y + 1) * 35 + 450) - (x * 40)) * zoom;
				pixel.y2 = pixel.y1 + (20 * zoom);
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FFFFFF);
				else
					draw_line_dy(data, pixel, 1, 0x00FFFFFF);
				printf("from: %d,%d to: %d,%d\n", pixel.x1, pixel.y1, pixel.x2, pixel.y2);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
		}
	}
	y = 0;
	for (int x = 0; x < fdf->map.width; x++)
	{
		for (y = 0; y < fdf->map.height - 1; y++)
		{
			if (y == 0)
			{
				pixel.x1 = ((x * 35 + 450) - (y * 40)) * zoom;
				pixel.y1 = ((y * 35 + 50) + (x * 20)) * zoom;
			}
			if (fdf->map.map[y][x] < fdf->map.map[y + 1][x])
			{
				pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * zoom;
				pixel.y2 = (((y + 1) * 35 + 50) + (x * 20) - (fdf->map.map[y + 1][x] * 4)) * zoom;
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FF0000);
				else
					draw_line_dy(data, pixel, 1, 0x00FF0000);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else if (fdf->map.map[y][x] > fdf->map.map[y + 1][x])
			{
				pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * zoom;
				pixel.y2 = (((y + 1) * 35 + 50) + (x * 20)) * zoom;
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FF0000);
				else
					draw_line_dy(data, pixel, 1, 0x00FF0000);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else
			{
				pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * zoom;
				pixel.y2 = pixel.y1 + (35 * zoom);
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FFFFFF);
				else
					draw_line_dy(data, pixel, 1, 0x00FFFFFF);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
		}
	}
	mlx_put_image_to_window(data.mlx , data.win, data.img, 0, 0);
	mlx_key_hook(win, &esc_key, &data);
	mlx_mouse_hook(win, &mouse_event, 0);
	mlx_hook(win, 17, 0, exit_fdf, 0); // exit 'x' button on top right
	mlx_loop(mlx);
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

	size = 100;
	lines_arr = ft_strsplit(lines, ' ');
	int_arr = (int *)malloc(sizeof(int) * size);
	x = 1;
	while (lines_arr[x] != NULL)
	{
		int_arr[x] = ft_atoi(lines_arr[x]);
		x++;
	}
	//int_arr[0] = x - 1; // Saving the length of the line in elem[0]
	free_str_arr(lines_arr);
	return (int_arr);
}

void	initialize_fdf(t_fdf *fdf)
{
	fdf->win_size.width = 1400;
	fdf->win_size.height = 1000;
}

int	main(void)
{
	int		fd;
	char	*lines;
	t_fdf	fdf;
	int		x;
	size_t	size;
	int		len;

	size = 100;
	fd = open("42.fdf", O_RDONLY);
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
	fdf.map.height = x;
	render_image(&fdf, x, len);
	return (0);
}
