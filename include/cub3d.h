/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/14 21:56:51 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include "player.h"
# include "parser.h"
# include "raycaster.h"
# include "movement.h"
# include "graphics.h"

#define screenWidth 960
#define screenHeight 640

typedef struct s_cupData
{
	mlx_t			*mlx;
	mlx_image_t		*image[3];
	t_parse			*parser;
	t_player		*player;
	t_raycaster		*rc;
	mlx_texture_t	*tex[6]; //{N,E,S,W,D}
	char			**worldMap;
	int				x_mouse;
	int				y_mouse;
}			t_cupData;

typedef struct s_lineData
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	x_tex;
	float	y;
	float	yinc;
	
}			t_lineData;


#endif