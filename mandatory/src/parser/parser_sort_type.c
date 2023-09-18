/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sort_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:34:36 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 14:33:31 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

uint32_t	sort_rgba(char	*line)
{
	char		**rgb;
	uint32_t	rgba;
	int			i;

	rgb = ft_split(line, ',');
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
	data->worldmap = ft_split(map, '|');
	free(map);
	padding(data, maxline, col);
}

void	sort_floor_roof(t_parse *data, char *buff, char type)
{
	if (type == 'F')
	{
		printf("Floor: %s\n", buff);
		if (ft_isdigit(buff[0]) == 1)
			data->floor = sort_rgba(buff);
		else
			data->floortex = ft_strtrim(buff, " \n");
	}
	else
	{
		printf("Roof: %s\n", buff);
		if (ft_isdigit(buff[0]) == 1)
			data->roof = sort_rgba(buff);
		else
			data->rooftex = ft_strtrim(buff, " \n");
	}
}
