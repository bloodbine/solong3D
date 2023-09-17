/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/17 15:41:48 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// -----------------------------------------------------------------------------
void	my_mouse_func(t_cubdata *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (data->x_mouse - x < 0)
		rotate(data->player, 1);
	else if (data->x_mouse - x > 0)
		rotate(data->player, -1);
	data->x_mouse = data->mlx->width / 2;
	data->y_mouse = data->mlx->height / 2;
	mlx_set_mouse_pos(data->mlx, data->mlx->width / 2, data->mlx->height / 2);
}

void	ft_hook(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	my_mouse_func(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_straight(data->player, 1, data->worldmap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_straight(data->player, -1, data->worldmap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_side(data->player, 1, data->worldmap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_side(data->player, -1, data->worldmap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(data->player, -1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data->player, 1);
}

int	init_graphics(t_cubdata *data)
{
	data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cup3d", 1);
	if (!data->mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	mlx_get_mouse_pos(data->mlx, &data->x_mouse, &data->y_mouse);
	mlx_get_monitor_size(0, &data->mlx->width, &data->mlx->height);
	mlx_set_window_size(data->mlx, data->mlx->width * 0.75, \
						data->mlx->height * 0.75);
	printf("width %d	height %d\n", data->mlx->width, data->mlx->height);
	mlx_set_window_pos(data->mlx, data->mlx->width / 6, data->mlx->height / 6);
	//segfault when trying to resize window with mouse
	if (!(data->image[0] = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height)) || \
		!(data->image[1] = mlx_new_image(data->mlx, data->mlx->width / 8, data->mlx->height / 4.5)) || \
		!(data->image[2] = mlx_new_image(data->mlx, 30, 30)))
		return(mlx_close_window(data->mlx), puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	if (mlx_image_to_window(data->mlx, data->image[0], 0, 0) == -1 || \
		mlx_image_to_window(data->mlx, data->image[1], 10, 10) == -1 || \
		mlx_image_to_window(data->mlx, data->image[2], 115, 115) == -1)
		return(mlx_close_window(data->mlx), puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	port_counter(void *param)
{
	t_cubdata	*data;
	static int	i = 0;

	data = (t_cubdata *)(param);
	i++;
	if (i == 7)
	{
		data->prot++;
		i = 0;
	}
	if (data->prot == 6)
		data->prot = 0;
}

int	manage_graphics(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	data->prot = 0;
	if (init_graphics(data))
		return (EXIT_FAILURE);
	mlx_loop_hook(data->mlx, ft_raycast, data);
	mlx_loop_hook(data->mlx, ft_minimap, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop_hook(data->mlx, port_counter, data);
	mlx_key_hook(data->mlx, interact, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	parse_free(data->parser);
	return (EXIT_SUCCESS);
}
