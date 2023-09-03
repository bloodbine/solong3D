/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/03 13:30:25 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_cubdata *data)
{
	data->player->pos.x = data->parser->playerpos.x + 0.5;
	data->player->pos.y = data->parser->playerpos.y + 0.5;
	data->player->dir.x = data->parser->playerdir.x;
	data->player->dir.y = data->parser->playerdir.y;
	data->player->cam_plane.x = -0.66 * (fabs(data->player->dir.x) - 1);
	data->player->cam_plane.y = -0.66 * (fabs(data->player->dir.y) - 1);
}

void	init_textures(t_cubdata *data)
{
	int	i;

	i = 0;
	while (data->parser->textures[i])
	{
		data->tex[i] = mlx_load_png(data->parser->textures[i]);
		printf("Tex : %s\n", data->parser->textures[i]);
		i++;
	}
	printf("Tex : %s\n", data->parser->textures[i]);
	data->tex[i] = mlx_load_png("./textures/unnamed-1.png");
}

void	init_cubdata(t_cubdata *data, t_player *player, t_raycaster *rc)
{
	data->player = player;
	data->rc = rc;
	data->worldmap = data->parser->worldmap;
	init_player(data);
	init_textures(data);
}

int	main(int argc, char**argv)
{
	t_cubdata	data;
	t_player	player;
	t_raycaster	rc;

	data.parser = parse(argc, argv);
	init_cubdata(&data, &player, &rc);
	if (manage_graphics(&data))
	{
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
