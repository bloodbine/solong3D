/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 15:38:49 by gpasztor         ###   ########.fr       */
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

void	init_textures(t_cubdata *data)
{
	int	i;

	i = 0;
	data->tex[0] = mlx_load_png(data->parser->textures[0]);
	data->tex[1] = mlx_load_png(data->parser->textures[1]);
	data->tex[2] = mlx_load_png(data->parser->textures[2]);
	data->tex[3] = mlx_load_png(data->parser->textures[3]);
	if (data->parser->textures[4] != NULL)
		data->tex[4] = mlx_load_png(data->parser->textures[4]);
	data->tex[5] = mlx_load_png("./textures/player.png");
	data->ptex[0] = mlx_load_png("./textures/portal/portal1.png");
	data->ptex[1] = mlx_load_png("./textures/portal/portal2.png");
	data->ptex[2] = mlx_load_png("./textures/portal/portal3.png");
	data->ptex[3] = mlx_load_png("./textures/portal/portal4.png");
	data->ptex[4] = mlx_load_png("./textures/portal/portal5.png");
	data->ptex[5] = mlx_load_png("./textures/portal/portal6.png");
	if (data->parser->floortex != NULL)
		data->floor = mlx_load_png(data->parser->floortex);
	if (data->parser->rooftex != NULL)
		data->roof = mlx_load_png(data->parser->rooftex);
	while (i < 6)
	{
		if (i == 4 && data->parser->limit == 6)
			i++;
		if (!data->tex[i] || !data->ptex[i])
			parse_error("failed to load image");
		i++;
	}
}

void	init_cubdata(t_cubdata *data, t_player *player, t_raycaster *rc)
{
	data->player = player;
	data->rc = rc;
	data->worldmap = data->parser->worldmap;
	data->modus = 0;
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
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
