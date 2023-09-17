/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/17 18:49:12 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// -----------------------------------------------------------------------------
void	my_mouse_func(t_cupData *data)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (data->x_mouse - x < 0)
		rotate(data->player, 1);
	else if (data->x_mouse - x > 0)
		rotate(data->player, -1);
	data->x_mouse = x;
	data->y_mouse = y;
}

void ft_hook(void* param)
{
	t_cupData *data;

	data = (t_cupData *)param;
	//my_mouse_func(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_straight(data->player, 1, data->worldMap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_straight(data->player, -1, data->worldMap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_side(data->player, 1, data->worldMap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_side(data->player, -1, data->worldMap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(data->player, -1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data->player, 1);
	//printf("FPS: %f\n", 1/data->mlx->delta_time);
}

int	init_graphics(t_cupData *data)
{
	data->mlx = mlx_init(screenWidth, screenHeight, "cup3d", 1);
	if (!data->mlx)
		return(puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
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

int	manage_graphics(void *param)
{
	t_cupData *data;

	data = (t_cupData *)param;
	if (init_graphics(data))
		return (EXIT_FAILURE);
	mlx_loop_hook(data->mlx, ft_raycast, data);
	mlx_loop_hook(data->mlx, ft_minimap, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return(EXIT_SUCCESS);
}