/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/21 22:58:26 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	my_mouse_func(t_cubdata *data)
{
	int	x;
	int	y;

	if (data->modus > 1)
	{
		mlx_set_mouse_pos(data->mlx, data->x_mouse, data->y_mouse);
		data->modus--;
		return ;
	}
	mlx_get_mouse_pos(data->mlx, &x, &y);
	rotate(data->player, -(data->x_mouse - x) / 75.0);
	mlx_set_mouse_pos(data->mlx, data->x_mouse, data->y_mouse);
}

void	ft_hook(void *param)
{
	t_cubdata	*data;

	data = (t_cubdata *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->modus)
	{
		my_mouse_func(data);
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
	printf("FPS: %f \n", 1 / data->mlx->delta_time);
}

int	init_graphics(t_cubdata *data)
{
	mlx_t	*mlx;

	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cup3d", 1);
	if (!mlx)
		return (puts(mlx_strerror(mlx_errno)), 1);
	data->mlx = mlx;
	mlx_get_monitor_size(0, &mlx->width, &mlx->height);
	mlx_set_window_size(mlx, mlx->width * 0.75, \
						mlx->height * 0.75);
	data->x_mouse = mlx->width / 2;
	data->y_mouse = mlx->height / 2;
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_set_window_pos(mlx, mlx->width / 6, mlx->height / 6);
	mlx_set_window_limit(mlx, mlx->width, mlx->height, mlx->width, mlx->height);
	data->image[0] = mlx_new_image(mlx, mlx->width, mlx->height);
	data->image[1] = mlx_new_image(mlx, mlx->width / 8, mlx->height / 4.5);
	data->image[2] = mlx_new_image(mlx, 30, 30);
	if (!data->image[0] || !data->image[1] || !data->image[2])
		return (mlx_close_window(mlx), puts(mlx_strerror(mlx_errno)), 1);
	if (mlx_image_to_window(mlx, data->image[0], 0, 0) == -1 || \
		mlx_image_to_window(mlx, data->image[1], 10, 10) == -1 || \
		mlx_image_to_window(mlx, data->image[2], 115, 115) == -1)
		return (mlx_close_window(mlx), puts(mlx_strerror(mlx_errno)), 1);
	data->modus = 10;
	return (0);
}

void	texture_free(t_cubdata *data)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (data->tex[i])
			mlx_delete_texture(data->tex[i]);
		i++;
	}
	if (data->parser->floortex)
		mlx_delete_texture(data->floor);
	if (data->parser->rooftex)
		mlx_delete_texture(data->roof);
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
	texture_free(data);
	parse_free(data->parser);
	return (EXIT_SUCCESS);
}
