/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:08 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include <math.h>
# include "player.h"
# include "cub3d.h"

void	rotate(t_player *player, int id);
void	move_straight(t_player *player, int id, char **worldmap);
void	move_side(t_player *player, int id, char **worldmap);
void	open_close(mlx_key_data_t keydata, void* param);

#endif