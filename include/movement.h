/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/09/17 23:53:06 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include <math.h>
# include "player.h"
# include "cub3d.h"

void	rotate(t_player *player, float id);
void	move_straight(t_player *player, int id, char **worldmap);
void	move_side(t_player *player, int id, char **worldmap);
void	interact(mlx_key_data_t keydata, void *param);
char	get_dir(t_player *player);

#endif