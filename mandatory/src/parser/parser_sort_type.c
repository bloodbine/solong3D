/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sort_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:34:36 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/24 12:02:14 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	sort_rgba(t_parse *data, char *line)
{
	char		**rgbc;
	uint32_t	rgba;
	int			rgb[3];
	int			i;

	rgbc = ft_split(line + 2, ',');
	if (!rgbc || !rgbc[0] || !rgbc[1] || !rgbc[2] || rgbc[3])
	{
		i = -1;
		while (rgbc[++i] != NULL)
			free(rgbc[i]);
		free(rgbc);
		free(line);
		return (parse_free(data), \
		parse_error("Invalid value in RGB values"), 0);
	}
	rgb[0] = ft_atoi(rgbc[0]);
	rgb[1] = ft_atoi(rgbc[1]);
	rgb[2] = ft_atoi(rgbc[2]);
	i = -1;
	while (rgbc[++i] != NULL)
		free(rgbc[i]);
	free(rgbc);
	rgba = rgbtohex(data, rgb, line);
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
	data->worldmap = ft_split(map, '|');
	free(map);
	padding(data, maxline, col);
}

void	sort_floor_roof(t_parse *data, char *buff, char type)
{
	if (type == 'F')
	{
		printf("Floor: %s\n", buff);
		if (ft_isdigit(buff[2]) == 1)
			data->floor = sort_rgba(data, buff);
		else
			data->floortex = ft_strtrim(buff + 2, " \n");
		printf("Floortex: %s\n", data->floortex);
	}
	else
	{
		printf("Roof: %s\n", buff);
		if (ft_isdigit(buff[2]) == 1)
			data->roof = sort_rgba(data, buff);
		else
			data->rooftex = ft_strtrim(buff + 2, " \n");
		printf("Rooftex: %s\n", data->rooftex);
	}
}
