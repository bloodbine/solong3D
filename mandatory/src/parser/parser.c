/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/18 15:57:55 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parse_error(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 2);
	exit(EXIT_FAILURE);
}

char	**read_file(int fd)
{
	char	**file;
	char	*buff;
	char	*line;

	buff = ft_strdup("");
	line = ft_strdup("");
	while (1)
	{
		buff = get_next_line(fd);
		if (buff != NULL)
			line = ft_frstrjoin(line, buff, 1);
		else
			break ;
		free(buff);
	}
	file = ft_split(line, '\n');
	close(fd);
	return (free(line), file);
}

uint32_t	rgbtohex(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) \
	+ (a & 0xff));
}

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

void	sort_data(t_parse *data, char **file, int *found)
{
	int	i;

	i = 0;
	while (file[i] != NULL)
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0 && ++(*found))
			data->textures[0] = ft_strtrim(file[i] + 2, " ");
		else if (ft_strncmp(file[i], "EA ", 3) == 0 && ++(*found))
			data->textures[1] = ft_strtrim(file[i] + 2, " ");
		else if (ft_strncmp(file[i], "SO ", 3) == 0 && ++(*found))
			data->textures[2] = ft_strtrim(file[i] + 2, " ");
		else if (ft_strncmp(file[i], "WE ", 3) == 0 && ++(*found))
			data->textures[3] = ft_strtrim(file[i] + 2, " ");
		else if (ft_strncmp(file[i], "F ", 2) == 0 && ++(*found))
			data->floor = sort_rgba(file[i]);
		else if (ft_strncmp(file[i], "C ", 2) == 0 && ++(*found))
			data->roof = sort_rgba(file[i]);
		else if ((ft_strchr(file[i], '1') || ft_strchr(file[i], '0')) && *found == 6)
			printf("Line: %d\n", i);
		free(file[i]);
		i++;
	}
}

t_parse	*parse(int argc, char **argv)
{
	t_parse	parsed_data;
	int		found;
	char	**file;
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
	file = read_file(fd);
	sort_data(&parsed_data, file, &found);
	printf("TEST Found: %d\n", found);
	printf("TEST NO: %s\n", parsed_data.textures[0]);
	printf("TEST EA: %s\n", parsed_data.textures[1]);
	printf("TEST SO: %s\n", parsed_data.textures[2]);
	printf("TEST WE: %s\n", parsed_data.textures[3]);
	printf("TEST F: 0x%06X\n", parsed_data.floor);
	printf("TEST C: 0x%06X\n", parsed_data.roof);
	return (NULL);
}
