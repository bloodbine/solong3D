/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:47:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/23 04:08:21 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

uint32_t	sort_rgba(char	*line)
{
	char		**rgb;
	uint32_t	rgba;
	int			i;

	rgb = ft_split(line + 1, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		parse_error("Invalid value in RGB values");
	rgba = rgbtohex(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	i = -1;
	while (rgb[++i] != NULL)
		free(rgb[i]);
	free(rgb);
	return (rgba);
}

void	sort_map(t_parse *data, int fd)
{
	char	*map;
	char	*buff;
	int		currline;
	int		maxline;
	int		col;

	buff = get_next_line(fd);
	map = ft_strdup("");
	maxline = 0;
	col = 0;
	while (buff != NULL)
	{
		currline = ft_strlen(buff);
		if (currline > maxline)
			maxline = currline;
		map = ft_frstrjoin(map, buff, 1);
		map = ft_frstrjoin(map, "|", 1);
		free(buff);
		buff = get_next_line(fd);
		col++;
	}
	close(fd);
	// printf("Line Test: %d %d\n", col, maxline);
	data->worldMap = ft_split(map, '|');
	free(map);
	padding(data, maxline, col);
}

void	sort_data(t_parse *data, int fd, int *found, char *buff)
{
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		if (*found == 6)
			break ;
		if (ft_strncmp(buff, "NO", 2) == 0 && ++(*found))
			data->textures[0] = ft_strtrim(buff + 2, " \n");
		else if (ft_strncmp(buff, "EA", 2) == 0 && ++(*found))
			data->textures[1] = ft_strtrim(buff + 2, " \n");
		else if (ft_strncmp(buff, "SO", 2) == 0 && ++(*found))
			data->textures[2] = ft_strtrim(buff + 2, " \n");
		else if (ft_strncmp(buff, "WE", 2) == 0 && ++(*found))
			data->textures[3] = ft_strtrim(buff + 2, " \n");
		else if (ft_strncmp(buff, "F", 1) == 0 && ++(*found))
			data->floor = sort_rgba(buff);
		else if (ft_strncmp(buff, "C", 1) == 0 && ++(*found))
			data->roof = sort_rgba(buff);
		free(buff);
		buff = get_next_line(fd);
	}
	data->textures[4] = NULL;
	if (*found != 6 || buff == NULL)
		parse_error("Incorrect variables");
	sort_map(data, fd);
}

void	sort_pos(t_parse *data, char type, int i, int j)
{
	data->playerPos.x = j;
	data->playerPos.y = i;
	if (type == 'N')
	{
		data->playerDir.y = -1;
		data->playerDir.x = 0;
	}
	else if (type == 'E')
	{
		data->playerDir.y = 0;
		data->playerDir.x = 1;
	}
	else if (type == 'S')
	{
		data->playerDir.y = 1;
		data->playerDir.x = 0;
	}
	else if (type == 'W')
	{
		data->playerDir.y = 0;
		data->playerDir.x = -1;
	}
	printf("DEBUG: Player Pos: [%d/%d]\n", data->playerPos.x, data->playerPos.y);
	printf("DEBUG: Player Dir: %c\n", type);
}

void	find_player(t_parse *data)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	j = -1;
	found = 0;
	while (data->worldMap[++i] != NULL)
	{
		while (data->worldMap[i][++j] != '\0')
		{
			if (data->worldMap[i][j] == 'N' && ++found)
				sort_pos(data, 'N', i, j);
			else if (data->worldMap[i][j] == 'E' && ++found)
				sort_pos(data, 'E', i, j);
			else if (data->worldMap[i][j] == 'W' && ++found)
				sort_pos(data, 'W', i, j);
			else if (data->worldMap[i][j] == 'S' && ++found)
				sort_pos(data, 'S', i, j);
			if (found > 1)
				parse_error("More than one player found in map");
		}
		j = -1;
	}
}