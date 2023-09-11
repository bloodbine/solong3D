/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:41:09 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/10 13:29:00 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTAL_H
# define PORTAL_H
# include "cub3d.h"

typedef struct s_portal
{
	mlx_texture_t	*tex[6];
	t_int_vector	pos[2];
	int				count;
}				t_portal;

#endif