/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:11:50 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/02 13:58:33 by conguyen         ###   ########.fr       */
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

void	draw_image(t_fdf *fdf)
{
	int	y = 0;
	for (int x = 0; x < fdf->map.height; x++)
	{
		for (y = 0; y < fdf->map.width -1; y++)
		{
			if (y == 0)
			{
				fdf->pixel.x1 = ((fdf->win_size.width * 0.50) - (x * (fdf->win_size.width * 0.5 / fdf->map.height))) * fdf->flags.zoom_flag;
				fdf->pixel.y1 = ((x * 35) + 100) * fdf->flags.zoom_flag;
			}
			if (fdf->map.map[x][y] < fdf->map.map[x][y + 1])
			{
				fdf->pixel.x2 = fdf->pixel.x1 + (fdf->win_size.width * 0.45 / fdf->map.height) * fdf->flags.zoom_flag;
				//(((y + 1) * 45 + (fdf->win_size.width * 0.50)) - (x * (fdf->win_size.width * 0.5 / fdf->map.height))) * fdf->flags.zoom_flag;
				// fdf->pixel.y2 = fdf->pixel.y1 + (((y + 1) * ((fdf->win_size.height * 0.3) / fdf->map.width)) - (fdf->map.map[x][y + 1] * 4)) * fdf->flags.zoom_flag;
				fdf->pixel.y2 = fdf->pixel.y1 + ((fdf->win_size.height * 0.38 / fdf->map.width) - (fdf->map.map[x][y + 1] * 4)) * fdf->flags.zoom_flag;
			}
			else if (fdf->map.map[x][y] > fdf->map.map[x][y + 1])
			{
				fdf->pixel.x2 = fdf->pixel.x1 + (fdf->win_size.width * 0.45 / fdf->map.height) * fdf->flags.zoom_flag;
				//(((y + 1) * 45 + (fdf->win_size.width * 0.50)) - (x * (fdf->win_size.width * 0.5 / fdf->map.height))) * fdf->flags.zoom_flag;
				fdf->pixel.y2 = fdf->pixel.y1 + (3 * (fdf->win_size.height * 0.38 / fdf->map.width) - (fdf->map.map[x][y + 1] * 4)) * fdf->flags.zoom_flag;
				//fdf->pixel.y2 = ((x * 35 + 100) + ((y + 1) * 20) - (fdf->map.map[x][y + 1] * 4)) * fdf->flags.zoom_flag;
			}
			else
			{
				fdf->pixel.x2 = fdf->pixel.x1 + (fdf->win_size.width * 0.45 / fdf->map.height) * fdf->flags.zoom_flag;
				// fdf->pixel.y2 = fdf->pixel.y1 + (20) * fdf->flags.zoom_flag;
				fdf->pixel.y2 = fdf->pixel.y1 + (fdf->win_size.height * 0.38 / fdf->map.width) * fdf->flags.zoom_flag;
			}
			fdf->pixel.dx = abs(fdf->pixel.x2 - fdf->pixel.x1);
			fdf->pixel.dy = abs(fdf->pixel.y2 - fdf->pixel.y1);
			if (fdf->pixel.dx > fdf->pixel.dy)
				draw_line_dx(fdf->mlx, fdf->pixel, 0, get_color(fdf, x, y, 0));
			else
				draw_line_dy(fdf->mlx, fdf->pixel, 1, get_color(fdf, x, y, 0));
			fdf->pixel.x1 = fdf->pixel.x2;
			fdf->pixel.y1 = fdf->pixel.y2;
		}
	}
	// y = 0;
	// for (int x = 0; x < fdf->map.width; x++)
	// {
	// 	for (y = 0; y < fdf->map.height - 1; y++)
	// 	{
	// 		if (y == 0)
	// 		{
	// 			if (((x * 35 + 450) - (y * 40)) * fdf->flags.zoom_flag < 1200)
	// 				fdf->pixel.x1 = ((x * 35 + 450) - (y * 40)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.x1 = 1199;
	// 			if (((y * 35 + 50) + (x * 20)) * fdf->flags.zoom_flag < 1000)
	// 				fdf->pixel.y1 = ((y * 35 + 50) + (x * 20)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.y1 = 999;
	// 		}
	// 		if (fdf->map.map[y][x] < fdf->map.map[y + 1][x])
	// 		{
	// 			if (((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag < 1200)
	// 				fdf->pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.x2 = 1199;
	// 			if ((((y + 1) * 35 + 50) + (x * 20) - (fdf->map.map[y + 1][x] * 4)) * fdf->flags.zoom_flag < 1000)
	// 				fdf->pixel.y2 = (((y + 1) * 35 + 50) + (x * 20) - (fdf->map.map[y + 1][x] * 4)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.y2 = 999;
	// 		}
	// 		else if (fdf->map.map[y][x] > fdf->map.map[y + 1][x])
	// 		{
	// 			if (((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag < 1200)
	// 				fdf->pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.x2 = 1199;
	// 			if ((((y + 1) * 35 + 50) + (x * 20)) * fdf->flags.zoom_flag < 1000)
	// 				fdf->pixel.y2 = (((y + 1) * 35 + 50) + (x * 20) - (fdf->map.map[y + 1][x] * 4)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.y2 = 999;
	// 		}
	// 		else
	// 		{
	// 			if (((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag < 1200)
	// 				fdf->pixel.x2 = ((x * 35 + 450) - ((y + 1) * 40)) * fdf->flags.zoom_flag;
	// 			else
	// 				fdf->pixel.x2 = 1199;
	// 			if (fdf->pixel.y1 + (35 * fdf->flags.zoom_flag) < 1000)
	// 				fdf->pixel.y2 = fdf->pixel.y1 + (35 * fdf->flags.zoom_flag);
	// 			else
	// 				fdf->pixel.y2 = 999;
	// 		}
	// 		if ((fdf->pixel.x1 != 1199 && fdf->pixel.x2 != 1199))
	// 		{
	// 			if ((fdf->pixel.y1 != 999 && fdf->pixel.y2 != 999))
	// 			{
	// 				fdf->pixel.dx = abs(fdf->pixel.x2 - fdf->pixel.x1);
	// 				fdf->pixel.dy = abs(fdf->pixel.y2 - fdf->pixel.y1);
	// 				if (fdf->pixel.dx > fdf->pixel.dy)
	// 					draw_line_dx(fdf->mlx, fdf->pixel, 0, get_color(fdf, y, x, 1));
	// 				else
	// 					draw_line_dy(fdf->mlx, fdf->pixel, 1, get_color(fdf, y, x, 1));
	// 			}
	// 		}
	// 		fdf->pixel.x1 = fdf->pixel.x2;
	// 		fdf->pixel.y1 = fdf->pixel.y2;
	// 	}
	// }
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

void	render_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	clear_image(fdf);
	draw_image(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx , fdf->mlx.win, fdf->mlx.img, fdf->flags.hori, fdf->flags.vert);
}

void	initialize_mlx(t_fdf *fdf, int height, int width)
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
	mlx_key_hook(fdf->mlx.win, &esc_key, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, exit_fdf, fdf); // exit 'x' button on top right
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
	fdf->win_size.width = 1200;
	fdf->win_size.height = 1000;
	fdf->flags.zoom_flag = 0.8;
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
	int		len;

	size = 300;
	fd = open("42.fdf", O_RDONLY);
	x = 0;
	//ft_bzero(&fdf, sizeof(t_fdf));
	fdf.map.map = (int **)malloc(sizeof(int *) * size);
	while (get_next_line(fd, &lines))
	{
		if (x == 0)
			fdf.map.width = get_length(lines);
		fdf.map.map[x] = transform_array(lines);
		free(lines);
		x++;
	}
	initialize_fdf(&fdf);
	fdf.map.height = x;
	initialize_mlx(&fdf, x, len);
	return (0);
}
