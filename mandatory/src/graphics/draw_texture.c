/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/17 16:29:42 by ffederol         ###   ########.fr       */
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

	i = l->drawStart;
	//i = 0;
	while (i <= l->drawEnd)
	{
		// if (i < l->drawStart)
		// 	mlx_put_pixel(data->image[0], rc->x_cam, i, data->parser->roof);
		// else if (i > l->drawEnd)
		// 	mlx_put_pixel(data->image[0], rc->x_cam, i, data->parser->floor);
		// else
		//{
			tex_pixel = (int)(l->y) * data->tex[rc->side]->width + l->x_tex;
			l->y += l->yinc;
			mlx_put_pixel(data->image[0], rc->x_cam, i, \
				convert_to_rgba(&(data->tex[rc->side]->pixels[tex_pixel * 4])));
	//	}
		i++;
	}
}

void	init_line(t_cupData *data, t_lineData *l, t_raycaster *rc)
{
	l->lineHeight = (int)(data->mlx->height / rc->camPlane2wallDist);
	l->drawStart = -l->lineHeight / 2 + data->mlx->height / 2;
	l->drawEnd = l->lineHeight / 2 + data->mlx->height / 2;
	if (l->drawStart < 0)
	{
		l->drawStart = 0;
		l->y = (l->lineHeight - data->mlx->height) / 2 / data->mlx->height * data->tex[rc->side]->height;
	}
	if (l->drawEnd >= data->mlx->height)
		l->drawEnd = data->mlx->height - 1;
	l->x_tex = roundf(rc->tilePos * data->tex[rc->side]->width);
	if (rc->side < 2)
		l->x_tex = roundf((1 - rc->tilePos) * data->tex[rc->side]->width);
	l->yinc = (float)data->tex[rc->side]->height / (l->lineHeight + 1);
	l->y = (l->drawStart - data->mlx->height / 2 + l->lineHeight / 2) * l->yinc;
}

void	draw_line(void *param)
{
	t_cupData *data;
	t_lineData	line;

	data = (t_cupData *)param;
	init_line(data, &line, data->rc);
	put_line(data, &line, data->rc);
}

