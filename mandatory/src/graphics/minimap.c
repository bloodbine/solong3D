/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 17:59:14 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_tile(t_cubdata *data, int y, int x, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = (int)(x * 10 - (int)(fmod(data->player->pos.x, 1) * 10.0));
	y = (int)(y * 10 - (int)(fmod(data->player->pos.y, 1) * 10.0));
	while (j < 10)
	{
		while (i < 10)
		{
			if ((i + x) >= 0 && (j + y) >= 0 && (i + x) < 240 && (j + y) < 240)
				mlx_put_pixel(data->image[1], i + x, j + y, color);
			i++;
		}
		i = 0;
		j++;
	}
}

void	draw_player(t_cubdata *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	dir;

	i = 0;
	j = 0;
	while (j < 22)
	{
		while (i < 22)
		{
			dir = -data->player->dir.x / fabs(data->player->dir.x);
			x = roundf(((i - 10.5) * cos(acos(data->player->dir.y) * dir) \
				- (j - 10.5) * sin(acos(data->player->dir.y) * dir)) + 10.5);
			y = roundf(((i - 10.5) * sin(acos(data->player->dir.y) * dir) \
				+ (j - 10.5) * cos(acos(data->player->dir.y) * dir)) + 10.5);
			mlx_put_pixel(data->image[2], x + 4, y + 4, \
					convert_to_rgba(&(data->tex[4]->pixels[(j * 22 + i) * 4])));
			i++;
		}
		i = 0;
		j++;
	}
}

int	check_limits(t_cubdata *data, int x, int y)
{
	int			x_start;
	int			y_start;

	x_start = (int)data->player->pos.x - 12;
	y_start = (int)data->player->pos.y - 12;
	if ((y_start + y) < data->parser->mapsizes.y \
			&& (x_start + x) < data->parser->mapsizes.x \
			&& (y_start + y) >= 0 && (x_start + x) >= 0)
		return (1);
	return (0);
}

uint32_t	get_color(t_cubdata *data, int x, int y)
{
	int			x_start;
	int			y_start;

	x_start = (int)data->player->pos.x - 12;
	y_start = (int)data->player->pos.y - 12;
	if (data->worldmap[y_start + y][x_start + x] == '1')
		return (0x00a0a0ff);
	else if (data->worldmap[y_start + y][x_start + x] == '0' \
				|| data->worldmap[y_start + y][x_start + x] == 'O')
		return (0xaff0f0ff);
	else if (data->worldmap[y_start + y][x_start + x] == 'D')
		return (0xcc6600ff);
	else if (data->worldmap[y_start + y][x_start + x] == 'P')
		return (0xff33ffff);
	else
		return (0x00000000);
}

void	ft_minimap(void *param)
{
	t_cubdata	*data;
	int			y;
	int			x;

	data = (t_cubdata *)param;
	x = 0;
	y = 0;
	ft_memset(data->image[1]->pixels, 0, data->image[1]->width \
					* (data->image[1]->height) * sizeof(int32_t));
	while (y <= 24)
	{
		if (check_limits(data, x, y))
			draw_tile(data, y, x, get_color(data, x, y));
		while (x <= 24)
		{
			if (check_limits(data, x, y))
				draw_tile(data, y, x, get_color(data, x, y));
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(data);
}
