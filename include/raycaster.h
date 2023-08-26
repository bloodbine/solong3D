/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/26 15:26:14 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>
# include "player.h"

typedef struct s_raycaster
{
	t_double_vector	ray;
	t_double_vector	sidedist;
	t_double_vector	deltadist;
	t_int_vector	map;
	int				hit;
	int				side;
	int				stepx;
	int				stepy;
	int				x_cam;
	double			camplane2walldist;
	double			planescaling;
	double			tilepos;
	uint32_t		floor;
	uint32_t		ceiling;
}				t_raycaster;

void	ft_raycast(void *param);
void	calc_dist_next_side(t_player *player, t_raycaster *rc);
void	calc_raydist(void *param);
void	calc_raydist_perp(t_raycaster *rc);
void	get_tilepos(t_player *player, t_raycaster *rc);

#endif