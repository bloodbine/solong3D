/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:25:04 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/12 19:23:10 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	teleport(t_cubdata *data, t_player *player, int x, int y)
{
	if (x == data->parser->ppos[0].x && y == data->parser->ppos[0].y)
	{
		player->pos.x = data->parser->ppos[1].x + 0.5;
		player->pos.y = data->parser->ppos[1].y + 0.5;
	}
	else if (x == data->parser->ppos[1].x && y == data->parser->ppos[1].y)
	{
		player->pos.x = data->parser->ppos[0].x + 0.5;
		player->pos.y = data->parser->ppos[0].y + 0.5;
	}
}

void	teleport_check(t_cubdata *data, t_player *player, char dir)
{
	if (dir == '0')
		return ;
	if (dir == 'N')
		teleport(data, data->player, player->pos.x, player->pos.y - 1);
	else if (dir == 'S')
		teleport(data, data->player, player->pos.x, player->pos.y + 1);
	else if (dir == 'E')
		teleport(data, data->player, player->pos.x + 1, player->pos.y);
	else if (dir == 'W')
		teleport(data, data->player, player->pos.x - 1, player->pos.y);
}
