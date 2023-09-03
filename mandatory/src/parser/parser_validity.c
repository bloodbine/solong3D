/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:54:30 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/03 14:04:22 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	file_check(t_parse *data)
{
	int	fd;
	int	i;

	i = -1;
	while (++i < 4)
	{
		fd = open(data->textures[i], O_RDONLY);
		if (fd == -1)
			parse_error("Invalid texture file");
		close(fd);
	}
}

int	character_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		printf("Index: %d\n", i);
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && \
			map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && \
			map[i][j] != 'E' && map[i][j] != 'D')
				return (1);
			j++;
		}
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
	i = -1;
	while (temp_map[++i] != NULL)
		free(temp_map[i]);
	free(temp_map);
	if (data->error == 1)
		parse_error("Map is not closed");
}
