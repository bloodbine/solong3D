/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/15 01:36:24 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

#include <math.h>
#include "player.h"


typedef struct s_raycaster
{
	t_double_vector	ray;
	t_double_vector	sideDist;
	t_double_vector	deltaDist;
	t_int_vector	map;
	int				hit;
	int				side;
	int				stepX;
	int				stepY;
	int				x_cam;
	double 			camPlane2wallDist;
	double			planeScaling;
	double			tilePos;
	mlx_texture_t* 	texture;
}				t_raycaster;

void	ft_raycast(void* param);
void	calc_dist_next_side(t_player *player, t_raycaster *rc);
void	calc_rayDist_euclidean(t_raycaster *rc);
void	calc_raydist_perp(t_raycaster *rc);
void	get_tilePos(t_player *player, t_raycaster *rc);


#endif