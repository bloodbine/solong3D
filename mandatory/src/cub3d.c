/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/25 11:47:30 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_cubdata *data)
{
	data->player->pos.x = data->parser->playerpos.x + 0.5;
	data->player->pos.y = data->parser->playerpos.y + 0.5;
	data->player->dir.x = data->parser->playerdir.x;
	data->player->dir.y = data->parser->playerdir.y;
	data->player->cam_plane.x = 0.66 * (fabs(data->player->dir.x) - 1) \
				* (float)(data->player->dir.y / fabs(data->player->dir.y));
	data->player->cam_plane.y = -0.66 * (fabs(data->player->dir.y) - 1) \
				* (float)(data->player->dir.x / fabs(data->player->dir.x));
}

void	init_textures(t_cubdata *data, int i)
{
	while (++i < 12)
	{
		if (data->parser->textures[i])
			data->tex[i] = mlx_load_png(data->parser->textures[i]);
	}
	i = -1;
	if (data->parser->floortex != NULL)
	{
		data->floor = mlx_load_png(data->parser->floortex);
		if (!data->floor)
			parse_error("failed to load floor image");
	}
	if (data->parser->rooftex != NULL)
	{
		data->roof = mlx_load_png(data->parser->rooftex);
		if (!data->roof)
			parse_error("failed to load roof image");
	}
	while (++i < 12)
	{
		if (i == 4 && data->parser->limit == 6)
			i++;
		if (!data->tex[i])
			parse_error("failed to load image");
	}
}

void	init_cubdata(t_cubdata *data, t_player *player, t_raycaster *rc)
{
	data->player = player;
	data->rc = rc;
	data->worldmap = data->parser->worldmap;
	data->modus = 0;
	data->roof = NULL;
	data->floor = NULL;
	init_player(data);
	init_textures(data, -1);
}

int	main(int argc, char**argv)
{
	t_cubdata	data;
	t_player	player;
	t_raycaster	rc;

	data.parser = parse(argc, argv);
	init_cubdata(&data, &player, &rc);
	if (manage_graphics(&data))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
