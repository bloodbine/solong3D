/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/20 11:31:45 by gpasztor         ###   ########.fr       */
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
	i = 0;
	while (rgb[i] != NULL)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (rgba);
}

void	sort_map(t_parse *data, int fd)
{
	char	*map;
	char	*buff;

	buff = get_next_line(fd);
	map = ft_strdup("");
	while (buff != NULL)
	{
		map = ft_frstrjoin(map, buff, 1);
		map = ft_frstrjoin(map, "|", 1);
		free(buff);
		buff = get_next_line(fd);
	}
	data->worldMap = ft_split(map, '|');
}

void	sort_data(t_parse *data, int fd, int *found)
{
	char	*buff;

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
	if (*found != 6)
		parse_error("Missing required variables from file");
	sort_map(data, fd);
}

t_parse	*parse(int argc, char **argv)
{
	t_parse	parsed_data;
	int		found;
	int		fd;

	found = 0;
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
	sort_data(&parsed_data, fd, &found);
	return (NULL);
}

	// printf("TEST Found: %d\n", found);
	// printf("TEST NO: %s\n", parsed_data.textures[0]);
	// printf("TEST EA: %s\n", parsed_data.textures[1]);
	// printf("TEST SO: %s\n", parsed_data.textures[2]);
	// printf("TEST WE: %s\n", parsed_data.textures[3]);
	// printf("TEST F: 0x%06X\n", parsed_data.floor);
	// printf("TEST C: 0x%06X\n", parsed_data.roof);