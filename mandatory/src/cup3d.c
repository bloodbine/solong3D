/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:25:10 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/13 04:56:46 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cup3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1280
#define screenHeight 960

int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static mlx_image_t* image;

// -----------------------------------------------------------------------------

void verLine(x, drawStart, drawEnd, color)
{
	while (drawStart <= drawEnd)
	{
		mlx_put_pixel(image, x, drawStart, color);
		drawStart++;
	}
}

void ft_raycast(void* param)
{
	t_player *player;

	player = (t_player *)param;
	t_vector	ray;
	t_vector	sideDist;
	t_vector	deltaDist;
	int			hit;
	int 		side;
	int 		stepX;
	int			stepY;
	int			mapX;
	int			mapY;
	double		camplane2wallDist;
	
	ft_memset(image->pixels, 0, image->width * (image->height) * sizeof(int32_t));
	for(int x = 0; x < screenWidth; x++)
    {
    	//calculate ray position and direction
    	double plane_scaling = 2 * (double)x / (double)screenWidth - 1; //-1 to 1 (scales the planevector to get the xpos in cam_plane for calculating the ray-directions with 0 scaling the ray-direction = player_direction)
    	// printf ("scaling %f\n", plane_scaling);
		ray.x = player->dir->x + player->cam_plane->x * plane_scaling;
    	ray.y = player->dir->y + player->cam_plane->y * plane_scaling;
		// printf ("rayx: %f	rayy: %f\n", ray.x, ray.y);
		mapX = (int)player->pos->x;
		mapY = (int)player->pos->y;
		hit = 0;
		side = 0;
		deltaDist.x = fabs(1/ray.x);
		deltaDist.y = fabs(1/ray.y);
		// printf ("ddx: %f	ddy: %f\n", deltaDist.x, deltaDist.y);
		if (ray.x < 0)
		{
			stepX = -1;
			sideDist.x = (player->pos->x - mapX) * deltaDist.x;
		}
		else
		{
			stepX = 1;
			sideDist.x = (mapX - player->pos->x + 1) * deltaDist.x;
		}
		if (ray.y < 0)
		{
			stepY = -1;
			sideDist.y = (player->pos->y - mapY) * deltaDist.y;
		}
		else
		{
			stepY = 1;
			sideDist.y = (mapY - player->pos->y + 1) * deltaDist.y;
		}
		
		// printf ("sdx: %f	sdy: %f\n", sideDist.x, sideDist.y);
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapY][mapX] > 0)
				hit = 1;
		}
		// printf ("1sdx: %f	sdy: %f\n\n", sideDist.x, sideDist.y);

		if(side == 0) 
			camplane2wallDist = (sideDist.x - deltaDist.x);
      	else 
			camplane2wallDist = (sideDist.y - deltaDist.y);

		int lineHeight = (int)(screenHeight / camplane2wallDist);

		int drawStart = (-lineHeight + screenHeight) / 2;
    	if(drawStart < 0)
			drawStart = 0;
    	int drawEnd = (lineHeight + screenHeight) / 2;
    	if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		
		uint32_t	color;
      	switch(worldMap[mapY][mapX])
      	{
       		case 1:  color = 0xff0000ff;  	break; //red
        	case 2:  color = 0x00ff00ff;  	break; //green
        	case 3:  color = 0x0000ffff;   	break; //blue
        	case 4:  color = 0x00ffffff;  	break; //
        	default: color = 0xffff00ff; 	break; //yellow
      	}

      	if (side == 1) {color = color - 128;}

      	//draw the pixels of the stripe as a vertical line
      	verLine(x, drawStart, drawEnd, color);
    }
}

void ft_hook(void* param)
{
	t_player *player;
	float movespeed = 0.1;
	player = (t_player *)param;
	if (mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	if (mlx_is_key_down(player->mlx, MLX_KEY_UP))
	{
		if (!worldMap[(int)(player->pos->y)][(int)(player->pos->x + player->dir->x * movespeed)])
			player->pos->x += player->dir->x * movespeed;
		if (!worldMap[(int)(player->pos->y + player->dir->y * movespeed)][(int)(player->pos->x)])
			player->pos->y += player->dir->y * movespeed;
	}
	if (mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
	{
		if (!worldMap[(int)(player->pos->y)][(int)(player->pos->x + player->dir->x * movespeed)])
			player->pos->x -= player->dir->x * movespeed;
		if (!worldMap[(int)(player->pos->y + player->dir->y * movespeed)][(int)(player->pos->x)])
			player->pos->y -= player->dir->y * movespeed;
	}
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = player->dir->x;
      	player->dir->x = player->dir->x * cos(-0.05) - player->dir->y * sin(-0.05);
      	player->dir->y = oldDirX * sin(-0.05) + player->dir->y * cos(-0.05);
      	double oldPlaneX = player->cam_plane->x;
    	player->cam_plane->x = player->cam_plane->x * cos(-0.05) - player->cam_plane->y * sin(-0.05);
  	    player->cam_plane->y = oldPlaneX * sin(-0.05) + player->cam_plane->y * cos(-0.05);
	}
	if (mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = player->dir->x;
      	player->dir->x = player->dir->x * cos(0.05) - player->dir->y * sin(0.05);
      	player->dir->y = oldDirX * sin(0.05) + player->dir->y * cos(0.05);
      	double oldPlaneX = player->cam_plane->x;
    	player->cam_plane->x = player->cam_plane->x * cos(0.05) - player->cam_plane->y * sin(0.05);
  	    player->cam_plane->y = oldPlaneX * sin(0.05) + player->cam_plane->y * cos(0.05);
	}
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;

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
	t_vector	pos;
	pos.x = 7;
	pos.y = 2;
	t_vector	dir;
	dir.x = 1;
	dir.y = 0;
	player.pos = &pos;
	player.dir = &dir;
	player.mlx = mlx;
	t_vector	cam;
	cam.x = 0;
	cam.y = 0.66; // FOV function
	player.cam_plane = &cam;
	double time = 0; //time of current frame
  	double oldTime = 0;

	mlx_loop_hook(mlx, ft_raycast, &player);
	mlx_loop_hook(mlx, ft_hook, &player);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
