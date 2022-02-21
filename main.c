/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/02/21 12:52:27 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_image(int **int_array, int height, int length)
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_linedata	pixel;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1150, 1000, "fdf");
	data.mlx = mlx;
	data.win = win;
	data.img = mlx_new_image(mlx, 1150, 1000);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < length - 1; y++)
		{
			if (y == 0)
			{
				pixel.x1 = (y * 35 + 450) - (x * 40);
				pixel.y1 = (x * 35 + 50) + (y * 20);
			}
			if (int_array[x][y] < int_array[x][y + 1])
			{
				pixel.x2 = ((y + 1) * 35 + 450) - (x * 40);
				pixel.y2 = ((x * 35 + 50) + ((y + 1) * 20)) - (int_array[x][y + 1] * 4);
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FF0000);
				else
					draw_line_dy(data, pixel, 1, 0x00FF0000);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else if (int_array[x][y] > int_array[x][y + 1])
			{
				pixel.x2 = ((y + 1) * 35 + 450) - (x * 40);
				pixel.y2 = ((x * 35 + 50) + ((y + 1) * 20));
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
				pixel.x2 = ((y + 1) * 35 + 450) - (x * 40);
				pixel.y2 = pixel.y1 + 20;
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
	for (int x = 0; x < length; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			if (y == 0)
			{
				pixel.x1 = (x * 35 + 450) - (y * 40);
				pixel.y1 = (y * 35 + 50) + (x * 20);
			}
			if (int_array[y][x] < int_array[y + 1][x])
			{
				pixel.x2 = (x * 35 + 450) - ((y + 1) * 40);
				pixel.y2 = ((y + 1) * 35 + 50) + (x * 20) - (int_array[y + 1][x] * 4);
				pixel.dx = abs(pixel.x2 - pixel.x1);
				pixel.dy = abs(pixel.y2 - pixel.y1);
				if (pixel.dx > pixel.dy)
					draw_line_dx(data, pixel, 0, 0x00FFFFFF);
				else
					draw_line_dy(data, pixel, 1, 0x00FFFFFF);
				pixel.x1 = pixel.x2;
				pixel.y1 = pixel.y2;
			}
			else if (int_array[y][x] > int_array[y + 1][x])
			{
				pixel.x2 = (x * 35 + 450) - ((y + 1) * 40);
				pixel.y2 = (((y + 1) * 35 + 50) + (x * 20));
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
				pixel.x2 = (x * 35 + 450) - ((y + 1) * 40);
				pixel.y2 = pixel.y1 + 35;
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
	mlx_put_image_to_window(mlx, win, data.img, 0, 0);
	mlx_key_hook(win, &esc_key, 0);
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
	{
		if (ft_isdigit(line[x]))
			len++;
		x++;
	}
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
	x = 0;
	while (lines_arr[x] != NULL)
	{
		int_arr[x] = ft_atoi(lines_arr[x]);
		x++;
	}
	free_str_arr(lines_arr);
	return (int_arr);
}

int	main(void)
{
	int		fd;
	char	*lines;
	int		**int_arr;
	int		x;
	size_t	size;
	int		len;

	size = 100;
	fd = open("42.fdf", O_RDONLY);
	x = 0;
	int_arr = (int **)malloc(sizeof(int *) * size);
	while (get_next_line(fd, &lines))
	{
		if (x == 0)
			len = get_length(lines);
		int_arr[x] = transform_array(lines);
		free(lines);
		x++;
	}
	// for (int y = 0; y < x; y++)
	// {
	// 	for (int z = 0; z <= len; z++)
	// 	{
	// 		printf("%d", int_arr[y][z]);
	// 	}
	// 	printf("\n");
	// }
	// printf("%d\n", len);
	render_image(int_arr, x, len);
	return (0);
}
