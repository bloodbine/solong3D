/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/08 12:51:40 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate(t_player *player, int id)
{
	double	olddirx;

	olddirx = player->dir.x;
	player->dir.x = player->dir.x * cos(0.05 * id) - player->dir.y * sin(0.05 * id);
	player->dir.y = olddirx * sin(0.05 * id) + player->dir.y * cos(0.05 * id);
	if (player->dir.x > 1.0)
		player->dir.x = 1.0;
	if (player->dir.y < -1.0)
		player->dir.y = -1.0;
	double oldPlaneX = player->cam_plane.x;
	player->cam_plane.x = player->cam_plane.x * cos(0.05 * id) - player->cam_plane.y * sin(0.05 * id);
	player->cam_plane.y = oldPlaneX * sin(0.05 * id) + player->cam_plane.y * cos(0.05 * id);
}

void	move_straight(t_player *player, int id, char **worldmap)
{
	float	movespeed;

	movespeed = 0.1;
	if (worldmap[(int)(player->pos.y)] \
	[(int)(player->pos.x + player->dir.x * movespeed * id)] == '0')
		player->pos.x += player->dir.x * movespeed * id;
	if (worldmap[(int)(player->pos.y + player->dir.y * movespeed * id)] \
	[(int)(player->pos.x)] == '0')
		player->pos.y += player->dir.y * movespeed * id;
	if (worldmap[(int)(player->pos.y)] \
	[(int)(player->pos.x + player->dir.x * movespeed * id)] == 'O')
		player->pos.x += player->dir.x * movespeed * id;
	if (worldmap[(int)(player->pos.y + player->dir.y * movespeed * id)] \
	[(int)(player->pos.x)] == 'O')
		player->pos.y += player->dir.y * movespeed * id;
}

void	move_side(t_player *player, int id, char **worldmap)
{
	float	movespeed;

	movespeed = 0.1;
	if (worldmap[(int)(player->pos.y)] \
	[(int)(player->pos.x + player->dir.y * movespeed * id)] == '0')
		player->pos.x += player->dir.y * movespeed * id;
	if (worldmap[(int)(player->pos.y + player->dir.x * movespeed * -id)] \
	[(int)(player->pos.x)] == '0')
		player->pos.y -= player->dir.x * movespeed * id;
	if (worldmap[(int)(player->pos.y)] \
	[(int)(player->pos.x + player->dir.y * movespeed * id)] == 'O')
		player->pos.x += player->dir.y * movespeed * id;
	if (worldmap[(int)(player->pos.y + player->dir.x * movespeed * -id)] \
	[(int)(player->pos.x)] == 'O')
		player->pos.y -= player->dir.x * movespeed * id;
}
