/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 18:28:44 by gpasztor         ###   ########.fr       */
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
	long long		tex_pixel;
	int				i;

	i = l->drawstart;
	while (i <= l->drawend)
	{
		tex_pixel = (int)(l->y) * l->tex->width + l->x_tex;
		mlx_put_pixel(data->image[0], rc->x_cam, i, \
			convert_to_rgba(&(l->tex->pixels[tex_pixel * 4])));
		l->y += l->yinc;
		i++;
	}
}

void	init_line(t_cubdata *data, t_linedata *l, t_raycaster *rc)
{
	if (data->rc->hit == 2)
		l->tex = data->door;
	else if (data->rc->hit == 3)
		l->tex = data->ptex[data->prot];
	else
		l->tex = data->tex[rc->side];
	l->lineheight = (int)(data->mlx->height / rc->camplane2walldist);
	l->drawstart = -l->lineheight / 2 + data->mlx->height / 2;
	l->drawend = l->lineheight / 2 + data->mlx->height / 2;
	if (l->drawstart < 0)
	{
		l->drawstart = 0;
		l->y = (l->lineheight - data->mlx->height) / 2 \
				/ data->mlx->height * l->tex->height;
	}
	if (l->drawend >= data->mlx->height)
		l->drawend = data->mlx->height - 1;
	l->x_tex = roundf(rc->tilepos * l->tex->width);
	if (rc->side < 2)
		l->x_tex = roundf((1 - rc->tilepos) * l->tex->width);
	l->yinc = (float)l->tex->height / (l->lineheight + 1);
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

void	texture_free(t_cubdata *data)
{
	if (data->tex[0] != NULL)
		mlx_delete_texture(data->tex[0]);
	if (data->tex[1] != NULL)
		mlx_delete_texture(data->tex[1]);
	if (data->tex[2])
		mlx_delete_texture(data->tex[2]);
	if (data->tex[3])
		mlx_delete_texture(data->tex[3]);
	if (data->tex[4])
		mlx_delete_texture(data->tex[4]);
	if (data->ptex[0])
		mlx_delete_texture(data->ptex[0]);
	if (data->ptex[1])
		mlx_delete_texture(data->ptex[1]);
	if (data->ptex[2])
		mlx_delete_texture(data->ptex[2]);
	if (data->ptex[3])
		mlx_delete_texture(data->ptex[3]);
	if (data->ptex[4])
		mlx_delete_texture(data->ptex[4]);
	if (data->ptex[5])
		mlx_delete_texture(data->ptex[5]);
	if (data->parser->doortex != NULL && data->door != NULL)
		mlx_delete_texture(data->door);
	if (data->parser->floortex != NULL && data->floor != NULL)
		mlx_delete_texture(data->floor);
	if (data->parser->rooftex != NULL && data->roof != NULL)
		mlx_delete_texture(data->roof);
}
