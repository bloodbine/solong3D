/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 16:17:06 by ffederol         ###   ########.fr       */
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

void	init_flr(t_cubdata *data, t_raycaster_floor *flr)
{
	flr->y = data->mlx->height / 2;
	flr->ray_l.x = data->player->dir.x - data->player->cam_plane.x;
	flr->ray_l.y = data->player->dir.y - data->player->cam_plane.y;
	flr->ray_r.x = data->player->dir.x + data->player->cam_plane.x;
	flr->ray_r.y = data->player->dir.y + data->player->cam_plane.y;
	flr->posZ = 0.5 * data->mlx->height;
	
}

void	update_flr_data_x(t_cubdata *data, t_raycaster_floor *flr)
{
	//int floortexture = 3;
	flr->cell.x = (int)(flr->floor.x);
	flr->cell.y = (int)(flr->floor.y);
	flr->tex.x = (int)(data->tex[0]->width * (flr->floor.x - flr->cell.x));
	if (flr->tex.x >= (int)data->tex[0]->width || flr->tex.x < 0)
		flr->tex.x = 0;
	flr->tex.y = (int)(data->tex[0]->height * (flr->floor.y - flr->cell.y));
	if (flr->tex.y >= (int)data->tex[0]->height  || flr->tex.y < 0)
		flr->tex.y = 0;
	flr->floor.x += flr->floor_step.x;
	flr->floor.y += flr->floor_step.y;
	flr->tex_pixel = &data->roof->pixels[(data->roof->width * flr->tex.y + flr->tex.x) * 4];
}

void	update_flr_data_y(t_cubdata *data, t_raycaster_floor *flr)
{
	flr->x = 0;
	flr->curr_line = flr->y - data->mlx->height / 2;
	flr->row_dist = flr->posZ / flr->curr_line;
	flr->floor_step.x = flr->row_dist * (flr->ray_r.x - flr->ray_l.x) \
							/ data->mlx->width;
	flr->floor_step.y = flr->row_dist * (flr->ray_r.y - flr->ray_l.y) \
							/ data->mlx->width;
	flr->floor.x = data->player->pos.x + flr->row_dist * flr->ray_l.x;
	flr->floor.y = data->player->pos.y + flr->row_dist * flr->ray_l.y;
}

void	flr(t_cubdata *data)
{
	t_raycaster_floor	flr;

	flr.y = data->mlx->height / 2;
	init_flr(data, &flr);
	while (flr.y < data->mlx->height)
	{
		update_flr_data_y(data, &flr);
		while (flr.x < data->mlx->width)
		{
			update_flr_data_x(data, &flr);
			mlx_put_pixel(data->image[0], flr.x, flr.y, \
							convert_to_rgba(flr.tex_pixel));
			flr.tex_pixel = &data->roof->pixels[(data->roof->width * flr.tex.y + flr.tex.x) * 4];
			mlx_put_pixel(data->image[0], flr.x, data->mlx->height - flr.y - 1, \
							convert_to_rgba(flr.tex_pixel));
			flr.x++;
		}
		flr.y++;
	}
}

void	ft_raycast(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	data->rc->x_cam = 0;
	//flr(data);
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
