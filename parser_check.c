/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:31:51 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/14 14:07:48 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_str_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] != NULL)
	{
		free(arr[x++]);
	}
	free(arr);
}

void	check_line(char **line)
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

int	check_width(char **lines_arr, t_fdf *fdf, int x)
{
	if (fdf->map.width != x)
	{
		ft_putstr("Error\n");
		free_str_arr(lines_arr);
		exit (0);
	}
}
