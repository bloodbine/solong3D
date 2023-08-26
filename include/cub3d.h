/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/26 15:19:52 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include "player.h"
# include "parser.h"
# include "raycaster.h"
# include "movement.h"
# include "graphics.h"

# define SCREENWIDTH 960
# define SCREENHEIGHT 640

typedef struct s_cubdata
{
	mlx_t			*mlx;
	mlx_image_t		*image[2];
	t_parse			*parser;
	t_player		*player;
	t_raycaster		*rc;
	mlx_texture_t	*tex[5];
	char			**worldmap;
	int				x_mouse;
	int				y_mouse;
}			t_cubdata;

typedef struct s_lineData
{
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		x_tex;
	double	y;
	double	yinc;
}			t_lineData;

#endif