/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/16 07:35:14 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	calc_dist_next_side(t_player *player, t_raycaster *rc)
{
	if (rc->ray.x < 0)
	{
		rc->stepX = -1;
		rc->sideDist.x = (player->pos.x - rc->map.x) * rc->deltaDist.x;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDist.x = (rc->map.x - player->pos.x + 1) * rc->deltaDist.x;
	}
	if (rc->ray.y < 0)
	{
		rc->stepY = -1;
		rc->sideDist.y = (player->pos.y - rc->map.y) * rc->deltaDist.y;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDist.y = (rc->map.y - player->pos.y + 1) * rc->deltaDist.y;
	}
}

void	calc_raydist_euclidean(t_raycaster *rc)
{
	while (!rc->hit)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->map.x += rc->stepX;
			rc->side = 3;
			if (rc->stepX < 0)
				rc->side = 1;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->map.y += rc->stepY;
			rc->side = 0;
			if (rc->stepY < 0)
				rc->side = 2;
		}
		if (worldMap[rc->map.y][rc->map.x] == 1)
			rc->hit = 1;
	}
}

void	calc_raydist_perp(t_raycaster *rc)
{
	if (rc->side % 2)
		rc->camPlane2wallDist = (rc->sideDist.x - rc->deltaDist.x);
	else
		rc->camPlane2wallDist = (rc->sideDist.y - rc->deltaDist.y);
}

void	get_tilepos(t_player *player, t_raycaster *rc)
{	
	if (rc->side % 2)
		rc->tilePos = \
			fmod(player->pos.y + rc->ray.y * rc->camPlane2wallDist, 1);
	else
		rc->tilePos = \
			fmod(player->pos.x + rc->ray.x * rc->camPlane2wallDist, 1);
}
