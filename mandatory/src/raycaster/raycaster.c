/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 18:33:17 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

//-1 to 1 (scales the planevector to get the xpos in cam_plane for calculating
// the ray-directions with 0 scaling the ray-direction = player_direction)
void	init_raycaster(t_cubdata *data)
{
	data->rc->planescaling = 2 * (float)data->rc->x_cam \
								/ (float)data->mlx->width - 1;
	data->rc->ray.x = data->player->dir.x + data->player->cam_plane.x \
												* data->rc->planescaling;
	data->rc->ray.y = data->player->dir.y + data->player->cam_plane.y \
												* data->rc->planescaling;
	data->rc->map.x = (int)data->player->pos.x;
	data->rc->map.y = (int)data->player->pos.y;
	data->rc->hit = 0;
	data->rc->side = 0;
	data->rc->deltadist.x = (float)fabs(1 / data->rc->ray.x);
	data->rc->deltadist.y = (float)fabs(1 / data->rc->ray.y);
}

void	ft_raycast(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	data->rc->x_cam = 0;
	flr(data);
	while (data->rc->x_cam < data->mlx->width)
	{
		init_raycaster(data);
		calc_dist_next_side(data->player, data->rc);
		calc_raydist(data);
		calc_raydist_perp(data->rc);
		get_tilepos(data->player, data->rc);
		draw_line(data);
		data->rc->x_cam++;
	}
}
