/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/16 16:12:33 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	sort_pos(t_parse *data, char type, int i, int j)
{
	data->playerpos.x = j;
	data->playerpos.y = i;
	if (type == 'N')
	{
		data->playerdir.y = -1;
		data->playerdir.x = 0;
	}
	else if (type == 'E')
	{
		data->playerdir.y = 0;
		data->playerdir.x = 1;
	}
	else if (type == 'S')
	{
		data->playerdir.y = 1;
		data->playerdir.x = 0;
	}
	else if (type == 'W')
	{
		data->playerdir.y = 0;
		data->playerdir.x = -1;
	}
}

void	find_player(t_parse *data)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	j = -1;
	found = 0;
	while (data->worldmap[++i] != NULL)
	{
		while (data->worldmap[i][++j] != '\0')
		{
			if (data->worldmap[i][j] == 'N' && ++found)
				sort_pos(data, 'N', i, j);
			else if (data->worldmap[i][j] == 'E' && ++found)
				sort_pos(data, 'E', i, j);
			else if (data->worldmap[i][j] == 'W' && ++found)
				sort_pos(data, 'W', i, j);
			else if (data->worldmap[i][j] == 'S' && ++found)
				sort_pos(data, 'S', i, j);
			if (found > 1)
				parse_error("More than one player found in map");
		}
		j = -1;
	}
}

t_parse	*parse(int argc, char **argv)
{
	t_parse	*data;
	int		found;
	int		fd;

	found = 0;
	data = malloc(sizeof(t_parse));
	if (argc == 1)
		parse_error("No map path given");
	if (argc > 2)
		parse_error("Too many arguments given");
	if (ft_strlen(argv[1]) < 5)
		parse_error("Map name is too short");
	if (ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 5) != 0)
		parse_error("File extension is invalid");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		parse_error("Failed to open map file");
	sort_data(data, fd, &found, NULL);
	find_player(data);
	if (character_check(data, data->worldmap, 0, 0) == 1)
		parse_error("Invalid character in map");
	run_dfs(data);
	file_check(data);
	data->worldmap[data->playerpos.y][data->playerpos.x] = '0';
	return (data);
}
