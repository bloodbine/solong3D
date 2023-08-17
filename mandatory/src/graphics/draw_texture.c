/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/17 05:22:54 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

//maybe calculate before gamestart in parsing 
uint32_t	convert_to_rgba(uint8_t *pixels)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	r = *pixels;
	g = *(pixels + 1);
	b = *(pixels + 2);
	a = *(pixels + 3);
	color = ((uint32_t)r << 24) | ((uint32_t)g << 16) | \
				((uint32_t)b << 8) | (uint32_t)a;
	return (color);
}

void	put_line(t_cupData *data, t_lineData *l, t_raycaster *rc)
{
	int		i;
	int		tex_pixel;

	i = 0;
	while (i < data->mlx->height)
	{
		if (i < l->drawStart)
			mlx_put_pixel(data->image[0], rc->x_cam, i, rc->ceiling);
		else if (i > l->drawEnd)
			mlx_put_pixel(data->image[0], rc->x_cam, i, rc->floor);
		else
		{
			tex_pixel = (int)(l->y) * data->tex[rc->side]->width + l->x_tex;
			l->y += l->yinc;
			mlx_put_pixel(data->image[0], rc->x_cam, i, \
				convert_to_rgba(&(data->tex[rc->side]->pixels[tex_pixel * 4])));
		}
		i++;
	}
}

void	init_line(t_cupData *data, t_lineData *l, t_raycaster *rc)
{
	l->lineHeight = (int)(data->mlx->height / rc->camPlane2wallDist);
	l->drawStart = (-l->lineHeight + data->mlx->height) / 2;
	l->drawEnd = (l->lineHeight + data->mlx->height) / 2;
	if (l->drawStart < 0)
	{
		l->drawStart = 0;
		l->y = (l->lineHeight - data->mlx->height) / 2 / data->mlx->height * data->tex[rc->side]->height;
	}
	printf("lineheigth: %d ly: %f	l->yinc: \n", l->lineHeight, l->y);
	if (l->drawEnd >= data->mlx->height)
		l->drawEnd = data->mlx->height - 1;
	l->x_tex = round(rc->tilePos * data->tex[rc->side]->width);
	if (rc->side < 2)
		l->x_tex = round((1 - rc->tilePos) * data->tex[rc->side]->width);
	l->yinc = (double) data->tex[rc->side]->height \
				/ (l->drawEnd - l->drawStart + 1);
	if (l->yinc < 1)
		l->yinc = 1/l->yinc;
	l->y = -l->yinc;
}

void	draw_line(void *param)
{
	t_cupData *data;
	t_lineData	line;

	data = (t_cupData *)param;
	init_line(data, &line, data->rc);
	put_line(data, &line, data->rc);
}

