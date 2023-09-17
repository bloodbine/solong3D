/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/17 18:34:42 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	init_raycaster(t_cupData *data)
{
	//-1 to 1 (scales the planevector to get the xpos in cam_plane for calculating the ray-directions with 0 scaling the ray-direction = player_direction)
	data->rc->planeScaling = 2 * (float)data->rc->x_cam \
								/ (float)data->mlx->width - 1;
	data->rc->ray.x = data->player->dir.x + data->player->cam_plane.x \
												* data->rc->planeScaling;
	data->rc->ray.y = data->player->dir.y + data->player->cam_plane.y \
												* data->rc->planeScaling;
	data->rc->map.x = (int)data->player->pos.x;
	data->rc->map.y = (int)data->player->pos.y;
	data->rc->hit = 0;
	data->rc->side = 0;
	data->rc->deltaDist.x = (float)fabs(1 / data->rc->ray.x);
	data->rc->deltaDist.y = (float)fabs(1 / data->rc->ray.y);
}

void	init_flr(t_cupData *data, t_raycaster_floor *flr)
{
	flr->x = 0;
	flr->curr_line = flr->y - data->mlx->height / 2;
	flr->ray_l.x = data->player->dir.x - data->player->cam_plane.x;
    flr->ray_l.y = data->player->dir.y - data->player->cam_plane.y;
    flr->ray_r.x = data->player->dir.x + data->player->cam_plane.x;
    flr->ray_r.y = data->player->dir.y + data->player->cam_plane.y;
	flr->posZ = 0.5 * data->mlx->height;
	flr->row_dist = flr->posZ / flr->curr_line;
	flr->floor_step.x = flr->row_dist * (flr->ray_r.x - flr->ray_l.x) / data->mlx->width;
	flr->floor_step.y = flr->row_dist * (flr->ray_r.y - flr->ray_l.y) / data->mlx->width;
	flr->floor.x = data->player->pos.x + flr->row_dist * flr->ray_l.x;
	flr->floor.y = data->player->pos.y + flr->row_dist * flr->ray_l.y;
	
}

void flr(t_cupData *data)
{
	t_raycaster_floor flr;

	flr.y = data->mlx->height / 2;
	while (flr.y < data->mlx->height)
    {
		init_flr(data, &flr);
    	while(flr.x < data->mlx->width)
      	{
        	flr.cell.x = (int)(flr.floor.x);
        	flr.cell.y = (int)(flr.floor.y);
       		flr.tex.x = (int)(data->tex[0]->width * (flr.floor.x - flr.cell.x)) & (data->tex[0]->width - 1);
       		flr.tex.y = (int)(data->tex[0]->height * (flr.floor.y - flr.cell.y)) & (data->tex[0]->width - 1);
        	flr.floor.x += flr.floor_step.x;
        	flr.floor.y += flr.floor_step.y;
	        int floorTexture = 0;
    	    int ceilingTexture = 0;
		    flr.tex_pixel = &data->tex[floorTexture]->pixels[(data->tex[floorTexture]->width * flr.tex.y + flr.tex.x) * 4];
			mlx_put_pixel(data->image[0], flr.x, flr.y, \
						convert_to_rgba(flr.tex_pixel));
			// flr.tex.x = (int)(data->tex[0]->width * (flr.floor.x - flr.cell.x)) & (data->tex[0]->width - 1);
       		// flr.tex.y = (int)(data->tex[0]->height * (flr.floor.y - flr.cell.y)) & (data->tex[0]->height - 1);
			flr.tex_pixel = &data->tex[ceilingTexture]->pixels[(data->tex[ceilingTexture]->width * flr.tex.y + flr.tex.x) * 4];
			mlx_put_pixel(data->image[0], flr.x, data->mlx->height - flr.y - 1, \
						convert_to_rgba(flr.tex_pixel));
			flr.x++;
      }
	  flr.y++;
    }
}

void	ft_raycast(void *param)
{
	t_cupData	*data;

	data = (t_cupData *)param;
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
	// ft_memset(data->image[1]->pixels, 255, data->image[1]->width * (data->image[1]->height) * sizeof(int32_t));
}
