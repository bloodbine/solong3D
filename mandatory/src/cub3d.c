/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/16 16:45:44 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


int worldMap[mapHeight][mapWidth] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// -----------------------------------------------------------------------------

void	init_player(t_cupData *data)
{
	//data->player->pos.x = data->parser->playerPos.x;
	data->player->pos.x = 2;
	//data->player->pos.y = data->parser->playerPos.y;
	data->player->pos.y = 2;
	//data->player->dir.x = data->parser->playerDir.x;
	data->player->dir.x = 1;
	//data->player->dir.y = data->parser->playerDir.y;
	data->player->dir.y = 0;

	// data->player->cam_plane.x = 0.66 * fabs(fabs(data->player->dir.x) - 1);
	// data->player->cam_plane.y = 0.66 * fabs(fabs(data->player->dir.y) - 1);
	data->player->cam_plane.x = 0;
	data->player->cam_plane.y = 0.66;
	data->player->hp = 100;
}

void	init_textures(t_cupData *data)
{
	int	i;
	
	i = 0;
	// while (data->parser->textures[i])
	// {
	// 	data->tex[i] = mlx_load_png(data->parser->textures[i]);
	// 	i++;
	// }

	//char *texture[] = {"./2ln_crnw_ne_g.png", "./2ln_crnw_ne_g.png", "./2ln_crnw_ne_g.png", "./2ln_crnw_ne_g.png"};
	char *texture[] = {"./textures/stonewall_grayscale.png", "./textures/stonewall_normal.png", "./textures/stonewall000.png", "./textures/stonewall001.png"};
	while (i < 4)
	{
		data->tex[i] = mlx_load_png(texture[i]);
		i++;
	}
}

void	init_cupData(t_cupData *data, t_player *player, t_raycaster *rc)
{
	data->player = player;
	data->rc = rc;
	init_player(data);
	init_textures(data);
}

int main(int argc, char **argv)
{
	t_cupData	data;
	t_player	player;
	t_raycaster rc;

	argv = NULL;
	argc = 0;
	// data.parser = parse(argc, argv);
	init_cupData(&data, &player, &rc);
	
	if (manage_graphics(&data))
	{
		//free stuff
		return (EXIT_FAILURE);
	}
	else //free stuff
		return (EXIT_SUCCESS);
}
