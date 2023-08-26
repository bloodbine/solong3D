/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/26 14:30:09 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_wall(t_cubdata *data, int y, int x, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = (int)(x * 10 - (int)(fmod(data->player->pos.x, 1) * 10.0));
	y = (int)(y * 10 - (int)(fmod(data->player->pos.y, 1) * 10.0)) ;
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

void	draw_player(t_cubdata *data, int y, int x, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 10)
	{
		while (i < 10)
		{
			mlx_put_pixel(data->image[1], i + x * 10 - 5, \
			j + y * 10 - 5, color);
			i++;
		}
		i = 0;
		j++;
	}
}

void	ft_minimap(void *param)
{
	t_cubdata	*data;
	int			x_start;
	int			y_start;
	int			y;
	int			x;

	data = (t_cubdata *)param;
	x_start = (int)data->player->pos.x - 12;
	y_start = (int)data->player->pos.y - 12;
	x = 0;
	y = 0;
	ft_memset(data->image[1]->pixels, 0, data->image[1]->width * (data->image[1]->height) * sizeof(int32_t));
	while (y <= 24)
	{
		if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldmap[y_start + y][x_start + x] == '1')
			draw_wall(data, y, x, 0x00a0a0ff);
		else if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldmap[y_start + y][x_start + x] == '0')
			draw_wall(data, y, x, 0xaff0f0ff);
		else
			draw_wall(data, y, x, 0xff000000);
		while (x <= 24)
		{
			if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldmap[y_start + y][x_start + x] == '1')
				draw_wall(data, y, x, 0x00a0a0ff);
			else if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldmap[y_start + y][x_start + x] == '0')
				draw_wall(data, y, x, 0xaff0f0ff);
			else
				draw_wall(data, y, x, 0xff000000);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(data, 12, 12, 0xff8000ff);
}
