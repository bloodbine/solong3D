/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/16 15:42:12 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include "player.h"
# include "parser.h"
# include "raycaster.h"
# include "movement.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 960
#define screenHeight 640

extern int worldMap[mapHeight][mapWidth];

typedef struct s_cupData
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_parse			*parser;
	t_player		*player;
	t_raycaster		*rc;
	mlx_texture_t	*tex[5]; //{N,E,S,W,D}
	int				x_mouse;
	int				y_mouse;
}			t_cupData;

typedef struct s_lineData
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int	x_tex;
	double	y;
	double	yinc;
	
}			t_lineData;

int		manage_graphics(t_cupData *data);
void	draw_line(t_cupData *data);

#endif