/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:41:52 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/24 11:08:44 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Dir: N = (0|1), E = (1|0), S = (0|-1), W = (-1|0)

char	get_dir(t_player *player)
{
	if (player->dir.y > 0.8)
		return ('S');
	if (player->dir.y < -0.8)
		return ('N');
	if (player->dir.x > 0.8)
		return ('E');
	if (player->dir.x < -0.8)
		return ('W');
	return ('0');
}

void	switch_door_tile(t_cubdata *data, int x, int y)
{
	if (data->worldmap[y][x] == 'O')
		data->worldmap[y][x] = 'D';
	else if (data->worldmap[y][x] == 'D')
		data->worldmap[y][x] = 'O';
}

void	toggle_door(t_cubdata *data, t_player *player, char dir)
{
	int	x;
	int	y;

	if (dir == '0')
		return ;
	x = (int)(player->pos.x);
	y = (int)(player->pos.y);
	if (dir == 'N')
		switch_door_tile(data, x, y - 1);
	else if (dir == 'S')
		switch_door_tile(data, x, y + 1);
	else if (dir == 'E')
		switch_door_tile(data, x + 1, y);
	else if (dir == 'W')
		switch_door_tile(data, x - 1, y);
}

void	interact(mlx_key_data_t keydata, void *param)
{
	t_cubdata	*data;
	t_player	*player;

	data = (t_cubdata *)param;
	player = data->player;
	if (keydata.key == MLX_KEY_TAB && keydata.action == 1)
	{
		mlx_set_mouse_pos(data->mlx, data->x_mouse, data->y_mouse);
		data->modus = abs(data->modus - 1);
		if (data->modus)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
		else
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
	if (keydata.action != MLX_RELEASE || keydata.key != MLX_KEY_E)
		return ;
	toggle_door(data, player, get_dir(player));
	teleport_check(data, player, get_dir(player));
}
