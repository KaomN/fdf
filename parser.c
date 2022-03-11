/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:19 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/11 08:12:11 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_str_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
	{
		free(arr[x++]);
	}
	free(arr);
}

static int	get_width(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
		x++;
	return (x);
}

static void	check_line(char **line)
{
	int	x;

	x = 0;
	while (line[x] != NULL)
	{
		if (line[x][0] == '-' && !ft_isdigit(line[x][1]))
		{
			free_str_arr(line);
			ft_putstr("Error map contains char that is not a digit\n");
			exit (0);
		}
		if (line[x][0] != '-' && !ft_isdigit(line[x][0]))
		{
			free_str_arr(line);
			ft_putstr("Error map contains char that is not a digit\n");
			exit (0);
		}
		x++;
	}
}

void	transform_array(char *lines, t_fdf *fdf)
{
	char	**lines_arr;
	int		x;

	lines_arr = ft_strsplit(lines, ' ');
	check_line(lines_arr);
	if (fdf->map.width == 0)
		fdf->map.width = get_width(lines_arr);
	x = 0;
	fdf->map.map[fdf->map.height] = (int *)malloc(sizeof(int) * fdf->map.width);
	while (lines_arr[x] != NULL)
	{
		fdf->map.map[fdf->map.height][x] = ft_atoi(lines_arr[x]);
		x++;
	}
	if (fdf->map.width != x)
	{
		ft_putstr("Error\n");
		free_str_arr(lines_arr);
		exit (0);
	}
	free_str_arr(lines_arr);
}
