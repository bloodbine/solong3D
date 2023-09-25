/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/25 12:08:24 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>
# include "player.h"

typedef struct s_raycaster
{
	t_float_vector	ray;
	t_float_vector	sidedist;
	t_float_vector	deltadist;
	t_int_vector	map;
	int				hit;
	int				side;
	int				stepx;
	int				stepy;
	int				x_cam;
	float			camplane2walldist;
	float			planescaling;
	float			tilepos;
}				t_raycaster;

typedef struct s_raycaster_floor
{
	t_float_vector	ray_l;
	t_float_vector	ray_r;
	t_float_vector	floor_step;
	t_float_vector	floor;
	t_int_vector	cell;
	t_int_vector	tex;
	uint8_t			*tex_pixel;
	int				curr_line;
	int				x;
	int				y;
	float			posz;
	float			row_dist;
}				t_raycaster_floor;

void	ft_raycast(void *param);
void	calc_dist_next_side(t_player *player, t_raycaster *rc);
void	calc_raydist(void *param);
void	calc_raydist_perp(t_raycaster *rc);
void	get_tilepos(t_player *player, t_raycaster *rc);
void	flr(void *param);

#endif