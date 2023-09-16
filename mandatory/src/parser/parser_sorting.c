/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:47:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/16 16:13:15 by gpasztor         ###   ########.fr       */
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
	data->worldmap = ft_split(map, '|');
	free(map);
	padding(data, maxline, col);
}

void	filter(t_parse *data, char *buff, int *found, int *limit)
{
	if (ft_strncmp(buff, "NO", 2) == 0 && ++(*found))
		data->textures[0] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "EA", 2) == 0 && ++(*found))
		data->textures[1] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "SO", 2) == 0 && ++(*found))
		data->textures[2] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "WE", 2) == 0 && ++(*found))
		data->textures[3] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "D", 1) == 0 && ++(*found))
	{
		data->textures[4] = ft_strtrim(buff + 2, " \n");
		*limit = 7;
	}
	else if (ft_strncmp(buff, "F", 1) == 0 && ++(*found))
		data->floor = sort_rgba(buff);
	else if (ft_strncmp(buff, "C", 1) == 0 && ++(*found))
		data->roof = sort_rgba(buff);
}

void	sort_data(t_parse *data, int fd, int *found, char *buff)
{
	int	limit;

	limit = 6;
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		filter(data, buff, found, &limit);
		free(buff);
		if (*found == limit)
			break ;
		buff = get_next_line(fd);
	}
	if ((*found != 6 && *found != 7) || buff == NULL)
		parse_error("Incorrect variables");
	sort_map(data, fd);
}
