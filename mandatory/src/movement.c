/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/17 00:30:18 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate(t_player *player, int id)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(0.05 * id) - player->dir.y * sin(0.05 * id);
    player->dir.y = oldDirX * sin(0.05 * id) + player->dir.y * cos(0.05 * id);
    double oldPlaneX = player->cam_plane.x;
    player->cam_plane.x = player->cam_plane.x * cos(0.05 * id) - player->cam_plane.y * sin(0.05 * id);
  	player->cam_plane.y = oldPlaneX * sin(0.05 * id) + player->cam_plane.y * cos(0.05 * id);
}

void	move_straight(t_player *player, int id)
{
	float movespeed = 0.1;
	if (!worldMap[(int)(player->pos.y)][(int)(player->pos.x + player->dir.x * movespeed * id)])
		player->pos.x += player->dir.x * movespeed * id;
	if (!worldMap[(int)(player->pos.y + player->dir.y * movespeed * id)][(int)(player->pos.x)])
		player->pos.y += player->dir.y * movespeed * id;
}

void	move_side(t_player *player, int id)
{
	float movespeed = 0.1;
	if (!worldMap[(int)(player->pos.y)][(int)(player->pos.x + player->dir.y * movespeed * id)])
		player->pos.x += player->dir.y * movespeed * id;
	if (!worldMap[(int)(player->pos.y + player->dir.x * movespeed * -id)][(int)(player->pos.x)])
		player->pos.y -= player->dir.x * movespeed * id;
}
