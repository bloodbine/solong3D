/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/14 21:54:14 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_wall(t_cupData *data, int y, int x, uint32_t color)
{
	int i = 0;
	int j = 0;

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

void	draw_player(t_cupData *data)
{
	int i = 0;
	int j = 0;
	int tex_pixel;
	int x;
	int y;
	int dir;

	while (j < 22)
	{
		while (i < 22)
		{
			tex_pixel = j * 22 + i;
			dir = -1;
			if (data->player->dir.x < 0)
				 dir = 1;
			x = (int)roundf(((i - 10.5) * cos(acos(data->player->dir.y) * dir) - (j - 10.5) * sin(acos(data->player->dir.y) * dir)) + 10.5);
			y = (int)roundf(((i - 10.5) * sin(acos(data->player->dir.y) * dir) + (j - 10.5) * cos(acos(data->player->dir.y) * dir)) + 10.5);
			mlx_put_pixel(data->image[2], x + 4, y + 4, \
					convert_to_rgba(&(data->tex[4]->pixels[tex_pixel * 4])));
			i++;
		}
		i = 0;
		j++;
	}
}


void	ft_minimap(void *param)
{
	t_cupData	*data;

	data = (t_cupData *)param;
	int	x_start;
	int y_start;
	int	y = 0;
	int x = 0;

	x_start = (int)data->player->pos.x - 12;
	y_start = (int)data->player->pos.y - 12;
	ft_memset(data->image[1]->pixels, 0, data->image[1]->width * (data->image[1]->height) * sizeof(int32_t));
	while (y <= 24)
	{
		if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldMap[y_start + y][x_start + x] == '1')
			draw_wall(data, y, x, 0x00a0a0ff);
		else if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldMap[y_start + y][x_start + x] == '0')
			draw_wall(data, y, x, 0xaff0f0ff);
		else
			draw_wall(data, y, x, 0xff000000);
		while (x <= 24)
		{
			if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldMap[y_start + y][x_start + x] == '1')
				draw_wall(data, y, x, 0x00a0a0ff);
			else if ((y_start + y) < data->parser->mapsizes.y && (x_start + x) < data->parser->mapsizes.x && (y_start + y) >= 0 && (x_start + x) >= 0 && data->worldMap[y_start + y][x_start + x] == '0')
				draw_wall(data, y, x, 0xaff0f0ff);
			else
				draw_wall(data, y, x, 0xff000000);
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(data);
}
