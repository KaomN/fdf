/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 07:54:06 by conguyen          #+#    #+#             */
/*   Updated: 2022/03/14 14:41:54 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	color_error(void)
{
	ft_putstr("Error color Hex\n");
	return (-1);
}

static int	hex_to_dec(char c)
{
	if (c >= 65 && c <= 70)
		return (c - 55);
	else
		return (c - 48);
}

static void	get_color(char *line, t_fdf *fdf, int x, int len)
{
	int	power;

	power = 0;
	fdf->map.color[fdf->map.height][x] = 0;
	while (line[--len] != 'x')
	{
		fdf->map.color[fdf->map.height][x] += hex_to_dec(line[len])
			* ((unsigned int)pow(16, (double)power));
		power++;
	}
}

int	check_color_line(char *line, t_fdf *fdf, int x)
{
	int	c;

	c = 1;
	if (line[0] != '0' || line[1] != 'x')
		return (color_error());
	while (line[++c] != '\0')
		if (!(line[c] >= 65 && line[c] <= 70)
			&& !(line[c] >= 48 && line[c] <= 57))
			return (color_error());
	get_color(line, fdf, x, c);
	return (1);
}
