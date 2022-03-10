/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:19 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/10 10:11:21 by conguyen         ###   ########.fr       */
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

void	transform_array(char *lines, t_fdf *fdf)
{
	int		*int_arr;
	char	**lines_arr;
	int		x;

	lines_arr = ft_strsplit(lines, ' ');
	fdf->map.width = get_width(lines_arr);
	x = 0;
	fdf->map.map[fdf->map.height] = (int *)malloc(sizeof(int) * fdf->map.width);
	while (lines_arr[x] != NULL)
	{
		fdf->map.map[fdf->map.height][x] = ft_atoi(lines_arr[x]);
		x++;
	}
	free_str_arr(lines_arr);
}
