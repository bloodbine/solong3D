/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/17 22:02:22 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_cupData *data)
{
	data->player->pos.x = data->parser->playerPos.x;
	data->player->pos.y = data->parser->playerPos.y;
	data->player->dir.x = data->parser->playerDir.x;
	data->player->dir.y = data->parser->playerDir.y;

	printf("test %f\n", data->player->dir.x/(float)fabs(data->player->dir.x));
	data->player->cam_plane.x = 0.66 * ((float)fabs(data->player->dir.x) - 1) * (float)(data->player->dir.y/fabs(data->player->dir.y));
	data->player->cam_plane.y = -0.66 * ((float)fabs(data->player->dir.y) - 1) * (float)(data->player->dir.x/fabs(data->player->dir.x));
}

void	init_textures(t_cupData *data)
{
	int	i;
	
	i = 0;
	while (data->parser->textures[i])
	{
		data->tex[i] = mlx_load_png(data->parser->textures[i]);
		i++;
	}
	data->tex[i] = mlx_load_png("./textures/player.png");
}

void	init_cupData(t_cupData *data, t_player *player, t_raycaster *rc)
{
	data->player = player;
	data->rc = rc;
	data->worldMap = data->parser->worldMap;
	init_player(data);
	init_textures(data);
}

int main(int argc, char**argv)
{
	t_cupData	data;
	t_player	player;
	t_raycaster rc;
	
	data.parser = parse(argc, argv);
	printf("test\n");
	init_cupData(&data, &player, &rc);
	printf("dir.x %f\n", data.player->dir.x);
	printf("dir.y %f\n", data.player->dir.y);
	if (manage_graphics(&data))
	{
		//free stuff
		return (EXIT_FAILURE);
	}
	else //free stuff
		return (EXIT_SUCCESS);
}
