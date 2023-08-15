/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/15 02:56:39 by ffederol         ###   ########.fr       */
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
# include "player.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 960
#define screenHeight 640

extern int worldMap[mapHeight][mapWidth];
typedef struct s_cupData
{
	mlx_t		*mlx;
	t_player	*player;
	t_raycaster	*rc;
}			t_cupData;

#endif