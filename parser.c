/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:19 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/22 10:58:45 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_width(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
		x++;
	return (x);
}

static char	*get_color_line(char *line)
{
	int	x;

	x = 0;
	while (1)
	{
		if (*line == ',')
			break ;
		line++;
	}
	line++;
	while (line[x] != '\0')
	{
		if (line[x] == 'X')
			line[x] = line[x] + 32;
		if (ft_isalpha(line[x]))
			if (ft_islower(line[x]))
				if (line[x] != 'x')
					line[x] = line[x] - 32;
		x++;
	}
	return (line);
}

static int	check_line_for_color(char *line, t_fdf *fdf, int x)
{
	int	c;

	c = 0;
	fdf->map.color[fdf->map.height][x] = 0xFFFFFF;
	while (line[c] != '\0')
	{
		if (line[c] == ',')
			return (1);
		c++;
	}
	return (0);
}

void	transform_array(char *lines, t_fdf *fdf)
{
	char	**lines_arr;
	int		x;

	lines_arr = ft_strsplit(lines, ' ');
	check_line(lines_arr);
	if (fdf->map.width == 0)
		fdf->map.width = get_width(lines_arr);
	x = -1;
	fdf->map.map[fdf->map.height] = (int *)malloc(sizeof(int) * fdf->map.width);
	fdf->map.color[fdf->map.height] = (int *)malloc(sizeof(int)
			* fdf->map.width);
	while (lines_arr[++x] != NULL)
	{
		fdf->map.map[fdf->map.height][x] = ft_atoi(lines_arr[x]);
		if (check_line_for_color(lines_arr[x], fdf, x))
			if (!check_color_line(get_color_line(lines_arr[x]), fdf, x))
				error_exit(lines_arr);
	}
	check_width(lines_arr, fdf, x);
	free_str_arr(lines_arr);
}
