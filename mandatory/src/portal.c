/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:25:04 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/14 15:05:05 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	teleport(t_cubdata *data, t_int_vector ppos, char dir)
{
	if (dir == 'N' && data->worldmap[ppos.y - 1][ppos.x] == '0')
	{
		data->player->pos.x = ppos.x + 0.5;
		data->player->pos.y = ppos.y - 0.5;
	}
	else if (dir == 'S' && data->worldmap[ppos.y + 1][ppos.x] == '0')
	{
		data->player->pos.x = ppos.x + 0.5;
		data->player->pos.y = ppos.y + 1.5;
	}
	else if (dir == 'E' && data->worldmap[ppos.y][ppos.x + 1] == '0')
	{
		data->player->pos.x = ppos.x + 1.5;
		data->player->pos.y = ppos.y + 0.5;
	}
	else if (dir == 'W' && data->worldmap[ppos.y][ppos.x - 1] == '0')
	{
		data->player->pos.x = ppos.x - 0.5;
		data->player->pos.y = ppos.y + 0.5;
	}
}

void	second_teleport_check(t_cubdata *data, int x, int y, char dir)
{
	t_player		*player;

	player = data->player;
	if (x == data->parser->ppos[0].x && y == data->parser->ppos[0].y)
		teleport(data, data->parser->ppos[1], dir);
	else if (x == data->parser->ppos[1].x && y == data->parser->ppos[1].y)
		teleport(data, data->parser->ppos[0], dir);
}

void	teleport_check(t_cubdata *data, t_player *player, char dir)
{
	if (dir == '0' || data->parser->pcount < 2)
		return ;
	if (dir == 'N')
		second_teleport_check(data, player->pos.x, player->pos.y - 1, dir);
	else if (dir == 'S')
		second_teleport_check(data, player->pos.x, player->pos.y + 1, dir);
	else if (dir == 'E')
		second_teleport_check(data, player->pos.x + 1, player->pos.y, dir);
	else if (dir == 'W')
		second_teleport_check(data, player->pos.x - 1, player->pos.y, dir);
}
