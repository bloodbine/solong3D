/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:54:30 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/23 17:35:37 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	file_check(t_parse *data)
{
	int	fd;
	int	i;

	i = -1;
	while (++i < 12)
	{
		fd = open(data->textures[i], O_RDONLY);
		if (fd == -1)
			return(parse_free(data), parse_error("Invalid texture file"));
		close(fd);
	}
}

int	character_check(t_parse *data, char **map, int i, int j)
{
	data->pcount = 0;
	while (map[i])
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && \
			map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && \
			map[i][j] != 'E' && map[i][j] != 'D' && map[i][j] != 'P')
				return (1);
			j++;
			if (map[i][j] == 'P')
			{
				data->ppos[data->pcount].y = i;
				data->ppos[data->pcount].x = j;
				data->pcount++;
			}
		}
		if (data->pcount > 2)
			return (1);
		j = 0;
		i++;
	}
	return (0);
}

void	closed_check(t_parse *data, char **map, int y, int x)
{
	if (data->error == 1)
		return ;
	if (map[y][x] == ' ')
	{
		printf("Not closed at: [%d/%d]\n", x - 3, y - 3);
		data->error = 1;
		return ;
	}
	map[y][x] = 'X';
	if (map[y][x + 1] != '1' && map[y][x + 1] != 'X')
		closed_check(data, map, y, x + 1);
	if (map[y][x - 1] != '1' && map[y][x - 1] != 'X')
		closed_check(data, map, y, x - 1);
	if (map[y + 1][x] != '1' && map[y + 1][x] != 'X')
		closed_check(data, map, y + 1, x);
	if (map[y - 1][x] != '1' && map[y - 1][x] != 'X')
		closed_check(data, map, y - 1, x);
	if (map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != 'X')
		closed_check(data, map, y + 1, x + 1);
	if (map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != 'X')
		closed_check(data, map, y + 1, x - 1);
	if (map[y - 1][x - 1] != '1' && map[y - 1][x - 1] != 'X')
		closed_check(data, map, y - 1, x - 1);
	if (map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != 'X')
		closed_check(data, map, y - 1, x + 1);
}

void	run_dfs(t_parse *data)
{
	char	**temp_map;
	int		i;

	i = 0;
	data->error = 0;
	while (data->worldmap[i] != NULL)
		i++;
	temp_map = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (data->worldmap[++i] != NULL)
		temp_map[i] = ft_strdup(data->worldmap[i]);
	temp_map[i] = NULL;
	closed_check(data, temp_map, data->playerpos.y, data->playerpos.x);
	if (data->pcount > 0)
		closed_check(data, temp_map, data->ppos[0].y, data->ppos[0].x);
	if (data->pcount > 1)
		closed_check(data, temp_map, data->ppos[1].y, data->ppos[1].x);
	i = -1;
	while (temp_map[++i] != NULL)
		free(temp_map[i]);
	free(temp_map);
	if (data->error == 1)
		return(parse_free(data), parse_error("Map is not closed"));
}
