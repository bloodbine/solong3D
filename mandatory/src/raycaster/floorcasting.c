/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 16:51:13 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	init_flr(t_cubdata *data, t_raycaster_floor *flr)
{
	flr->y = data->mlx->height / 2;
	flr->ray_l.x = data->player->dir.x - data->player->cam_plane.x;
	flr->ray_l.y = data->player->dir.y - data->player->cam_plane.y;
	flr->ray_r.x = data->player->dir.x + data->player->cam_plane.x;
	flr->ray_r.y = data->player->dir.y + data->player->cam_plane.y;
	flr->posZ = 0.5 * data->mlx->height;
}

void	update_flr_data_x(t_raycaster_floor *flr, mlx_texture_t *tex)
{
	flr->cell.x = (int)(flr->floor.x);
	flr->cell.y = (int)(flr->floor.y);
	flr->tex.x = (int)(tex->width * (flr->floor.x - flr->cell.x));
	if (flr->tex.x >= (int)tex->width || flr->tex.x < 0)
		flr->tex.x = 0;
	flr->tex.y = (int)(tex->height * (flr->floor.y - flr->cell.y));
	if (flr->tex.y >= (int)tex->height || flr->tex.y < 0)
		flr->tex.y = 0;
	flr->tex_pixel = &tex->pixels[(tex->width * flr->tex.y + flr->tex.x) * 4];
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

void	flr(void *param)
{
	t_raycaster_floor	flr;
	t_cubdata			*data;

	data = (t_cubdata *)param;
	init_flr(data, &flr);
	while (flr.y < data->mlx->height)
	{
		update_flr_data_y(data, &flr);
		while (flr.x < data->mlx->width)
		{
			flr.floor.x += flr.floor_step.x;
			flr.floor.y += flr.floor_step.y;
			update_flr_data_x(&flr, data->floor);
			mlx_put_pixel(data->image[0], flr.x, flr.y, \
							convert_to_rgba(flr.tex_pixel));
			update_flr_data_x(&flr, data->roof);
			mlx_put_pixel(data->image[0], flr.x, data->mlx->height - flr.y - 1, \
							convert_to_rgba(flr.tex_pixel));
			flr.x++;
		}
		flr.y++;
	}
}
