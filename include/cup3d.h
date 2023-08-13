/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/13 04:06:05 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "raycaster.h"
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_player 
{
	t_vector	*pos;
	t_vector	*dir; // N = (0|1), O = (1|0), S = (0|-1), W = (-1|0)
	t_vector	*cam_plane;
	int			hp;
	mlx_t		*mlx;
}			t_player;

#endif