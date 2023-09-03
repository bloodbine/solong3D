/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/03 12:13:26 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	calc_dist_next_side(t_player *player, t_raycaster *rc)
{
	if (rc->ray.x < 0)
	{
		rc->stepx = -1;
		rc->sidedist.x = (player->pos.x - rc->map.x) * rc->deltadist.x;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedist.x = (rc->map.x - player->pos.x + 1) * rc->deltadist.x;
	}
	if (rc->ray.y < 0)
	{
		rc->stepy = -1;
		rc->sidedist.y = (player->pos.y - rc->map.y) * rc->deltadist.y;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedist.y = (rc->map.y - player->pos.y + 1) * rc->deltadist.y;
	}
}

void	calc_raydist(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	while (!data->rc->hit)
	{
		if (data->rc->sidedist.x < data->rc->sidedist.y)
		{
			data->rc->sidedist.x += data->rc->deltadist.x;
			data->rc->map.x += data->rc->stepx;
			data->rc->side = 3;
			if (data->rc->stepx < 0)
				data->rc->side = 1;
		}
		else
		{
			data->rc->sidedist.y += data->rc->deltadist.y;
			data->rc->map.y += data->rc->stepy;
			data->rc->side = 0;
			if (data->rc->stepy < 0)
				data->rc->side = 2;
		}
		if (data->parser->worldmap[data->rc->map.y][data->rc->map.x] == '1')
			data->rc->hit = 1;
		if (data->parser->worldmap[data->rc->map.y][data->rc->map.x] == 'D')
		{
			data->rc->hit = 1;
			data->rc->side = 4;
		}
	}
}

void	calc_raydist_perp(t_raycaster *rc)
{
	if (rc->side % 2)
		rc->camplane2walldist = (rc->sidedist.x - rc->deltadist.x);
	else
		rc->camplane2walldist = (rc->sidedist.y - rc->deltadist.y);
}

void	get_tilepos(t_player *player, t_raycaster *rc)
{	
	if (rc->side % 2)
		rc->tilepos = \
			fmod(player->pos.y + rc->ray.y * rc->camplane2walldist, 1);
	else
		rc->tilepos = \
			fmod(player->pos.x + rc->ray.x * rc->camplane2walldist, 1);
}
