/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/15 05:07:00 by ffederol         ###   ########.fr       */
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

static mlx_image_t* image;
// -----------------------------------------------------------------------------

void verLine(t_raycaster* rc, int drawStart, int drawEnd, uint32_t color)
{
	int	temp = drawStart;
	double	scale;
	int		y;
	int		x;
	x = round(rc->tilePos * rc->texture->width);
	while (drawStart <= drawEnd)
	{
		scale = (double)(drawStart - temp) / (drawEnd - temp + 1);
		y = (int)round(scale * rc->texture->height);
		//printf("scale: %x \n", *(u_int32_t *)&(rc->texture->pixels[(y * rc->texture ->width + x) * 4]) >> 24);
		// printf("y: %d\n", y);
		// printf("x: %d\n", x);
		mlx_put_pixel(image, rc->x_cam, drawStart, *(u_int32_t *)&(rc->texture->pixels[(y * rc->texture ->width + x) * 4]));
		drawStart++;
	}
}

void	init_raycaster(t_player *player, t_raycaster *rc)
{
	rc->planeScaling = 2 * (double)rc->x_cam / (double)screenWidth - 1; //-1 to 1 (scales the planevector to get the xpos in cam_plane for calculating the ray-directions with 0 scaling the ray-direction = player_direction)
	rc->ray.x = player->dir->x + player->cam_plane->x * rc->planeScaling;
    rc->ray.y = player->dir->y + player->cam_plane->y * rc->planeScaling;
	rc->map.x = (int)player->pos->x;
	rc->map.y = (int)player->pos->y;
	rc->hit = 0;
	rc->side = 0;
	rc->deltaDist.x = fabs(1/rc->ray.x);
	rc->deltaDist.y = fabs(1/rc->ray.y);
}

void	draw_line(t_raycaster *rc)
{
	int lineHeight;
	int drawStart; 
	int drawEnd;
	
	lineHeight = (int)(screenHeight / rc->camPlane2wallDist);
	drawStart = (-lineHeight + screenHeight) / 2;
    if(drawStart < 0)
		drawStart = 0;
    drawEnd = (lineHeight + screenHeight) / 2;
    if(drawEnd >= screenHeight)
		drawEnd = screenHeight - 1;
	
	// uint32_t	color;
    // switch(rc->side)
    // {
    // 	case 0:  color = 0xff0000ff;  	break; //red
    //    	case 1:  color = 0x00ff00ff;  	break; //green
    //    	case 2:  color = 0x0000ffff;   	break; //blue
    //    	case 3:  color = 0x00ffffff;  	break; //
    //    	default: color = 0xffff00ff; 	break; //yellow
	// }
	
	// color = color - (uint32_t)((fabs(rc->tilePos)) * 192);

	verLine(rc, drawStart, drawEnd, color);
}

void ft_raycast(void* param)
{
	t_cupData *data;
	t_raycaster	*rc;
	t_player *player;
	
	data = (t_cupData*)param;
	rc = data->rc;
	player = data->player;
	rc->x_cam = 0;
	ft_memset(image->pixels, 0, image->width * (image->height) * sizeof(int32_t));
	while (rc->x_cam < screenWidth)
	{
		init_raycaster(player, rc);
		calc_dist_next_side(player, rc);
		calc_rayDist_euclidean(rc);
		calc_raydist_perp(rc);
		get_tilePos(player, rc);
		draw_line(rc);
		rc->x_cam++;
	}
}

void ft_hook(void* param)
{
	t_cupData *data;
	float movespeed = 0.1;
	data = (t_cupData *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		if (!worldMap[(int)(data->player->pos->y)][(int)(data->player->pos->x + data->player->dir->x * movespeed)])
			data->player->pos->x += data->player->dir->x * movespeed;
		if (!worldMap[(int)(data->player->pos->y + data->player->dir->y * movespeed)][(int)(data->player->pos->x)])
			data->player->pos->y += data->player->dir->y * movespeed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (!worldMap[(int)(data->player->pos->y)][(int)(data->player->pos->x + data->player->dir->x * movespeed)])
			data->player->pos->x -= data->player->dir->x * movespeed;
		if (!worldMap[(int)(data->player->pos->y + data->player->dir->y * movespeed)][(int)(data->player->pos->x)])
			data->player->pos->y -= data->player->dir->y * movespeed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = data->player->dir->x;
      	data->player->dir->x = data->player->dir->x * cos(-0.05) - data->player->dir->y * sin(-0.05);
      	data->player->dir->y = oldDirX * sin(-0.05) + data->player->dir->y * cos(-0.05);
      	double oldPlaneX = data->player->cam_plane->x;
    	data->player->cam_plane->x = data->player->cam_plane->x * cos(-0.05) - data->player->cam_plane->y * sin(-0.05);
  	    data->player->cam_plane->y = oldPlaneX * sin(-0.05) + data->player->cam_plane->y * cos(-0.05);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = data->player->dir->x;
      	data->player->dir->x = data->player->dir->x * cos(0.05) - data->player->dir->y * sin(0.05);
      	data->player->dir->y = oldDirX * sin(0.05) + data->player->dir->y * cos(0.05);
      	double oldPlaneX = data->player->cam_plane->x;
    	data->player->cam_plane->x = data->player->cam_plane->x * cos(0.05) - data->player->cam_plane->y * sin(0.05);
  	    data->player->cam_plane->y = oldPlaneX * sin(0.05) + data->player->cam_plane->y * cos(0.05);
	}
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;
	mlx_texture_t* texture = mlx_load_png("./3179875.png");
	texture->pixels++;
	// Gotta error check this stuff
	if (!(mlx = mlx_init(screenWidth, screenHeight, "Raycaster", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, screenWidth, screenHeight)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	t_player player;
	t_cupData data;
	t_raycaster rc;
	t_double_vector	pos;
	rc.texture = texture;
	pos.x = 2;
	pos.y = 2;
	t_double_vector	dir;
	dir.x = 1;
	dir.y = 0;
	player.pos = &pos;
	player.dir = &dir;
	t_double_vector	cam;
	cam.x = 0;
	cam.y = 0.66; // FOV function
	player.cam_plane = &cam;
	double time = 0; //time of current frame
  	double oldTime = 0;

	data.mlx = mlx;
	data.player = &player;
	//data.worldMap = worldMap;
	data.rc = &rc;
	
	mlx_loop_hook(mlx, ft_raycast, &data);
	mlx_loop_hook(mlx, ft_hook, &data);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
