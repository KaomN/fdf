/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:19 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/09 12:24:01 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	get_size(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
		x++;
	return (x);
}

int	*transform_array(char *lines, t_fdf *fdf)
{
	int		*int_arr;
	char	**lines_arr;
	int		x;
	size_t	size;

	lines_arr = ft_strsplit(lines, ' ');
	size = get_size(lines_arr);
	fdf->map.width = size;
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
