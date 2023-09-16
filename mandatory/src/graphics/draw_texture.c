/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/16 14:51:44 by gpasztor         ###   ########.fr       */
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

void	put_line(t_cubdata *data, t_linedata *l, t_raycaster *rc)
{
	int				tex_pixel;
	mlx_texture_t	*tex;
	int				i;

	i = -1;
	while (++i < data->mlx->height)
	{
		if (i < l->drawstart)
			mlx_put_pixel(data->image[0], rc->x_cam, i, data->parser->roof);
		else if (i > l->drawend)
			mlx_put_pixel(data->image[0], rc->x_cam, i, data->parser->floor);
		else
		{
			if (data->rc->hit == 2)
				tex = data->tex[4];
			else if (data->rc->hit == 3)
				tex = data->ptex[data->prot];
			else
				tex = data->tex[rc->side];
			tex_pixel = (int)(l->y) * data->tex[rc->side]->width + l->x_tex;
			l->y += l->yinc;
			mlx_put_pixel(data->image[0], rc->x_cam, i, \
				convert_to_rgba(&(tex->pixels[tex_pixel * 4])));
		}
	}
}

void	init_line(t_cubdata *data, t_linedata *l, t_raycaster *rc)
{
	l->lineheight = (int)(data->mlx->height / rc->camplane2walldist);
	l->drawstart = -l->lineheight / 2 + data->mlx->height / 2;
	l->drawend = l->lineheight / 2 + data->mlx->height / 2;
	if (l->drawstart < 0)
	{
		l->drawstart = 0;
		l->y = (l->lineheight - data->mlx->height) \
		/ 2 / data->mlx->height * data->tex[rc->side]->height;
	}
	if (l->drawend >= data->mlx->height)
		l->drawend = data->mlx->height - 1;
	l->x_tex = round(rc->tilepos * data->tex[rc->side]->width);
	if (rc->side < 2)
		l->x_tex = round((1 - rc->tilepos) * data->tex[rc->side]->width);
	l->yinc = (double)data->tex[rc->side]->height / (l->lineheight + 1);
	l->y = (l->drawstart - data->mlx->height / 2 + l->lineheight / 2) * l->yinc;
}

void	draw_line(void *param)
{
	t_cubdata	*data;
	t_linedata	line;

	data = (t_cubdata *)param;
	init_line(data, &line, data->rc);
	put_line(data, &line, data->rc);
}
