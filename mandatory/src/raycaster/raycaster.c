/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/17 04:03:02 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	init_raycaster(t_cupData *data)
{
	//-1 to 1 (scales the planevector to get the xpos in cam_plane for calculating the ray-directions with 0 scaling the ray-direction = player_direction)
	data->rc->planeScaling = 2 * (double)data->rc->x_cam \
								/ (double)data->mlx->width - 1;
	data->rc->ray.x = data->player->dir.x + data->player->cam_plane.x \
												* data->rc->planeScaling;
	data->rc->ray.y = data->player->dir.y + data->player->cam_plane.y \
												* data->rc->planeScaling;
	data->rc->map.x = (int)data->player->pos.x;
	data->rc->map.y = (int)data->player->pos.y;
	data->rc->hit = 0;
	data->rc->side = 0;
	data->rc->deltaDist.x = fabs(1 / data->rc->ray.x);
	data->rc->deltaDist.y = fabs(1 / data->rc->ray.y);
	data->rc->floor = 0x7a00c80f;
	data->rc->ceiling = 0x7a70c83f;
}

void	ft_raycast(void *param)
{
	t_cupData	*data;

	data = (t_cupData *)param;
	data->rc->x_cam = 0;
	while (data->rc->x_cam < data->mlx->width)
	{
		init_raycaster(data);
		calc_dist_next_side(data->player, data->rc);
		calc_raydist(data->rc);
		calc_raydist_perp(data->rc);
		get_tilepos(data->player, data->rc);
		draw_line(data);
		data->rc->x_cam++;
	}
	// ft_memset(data->image[1]->pixels, 255, data->image[1]->width * (data->image[1]->height) * sizeof(int32_t));
}