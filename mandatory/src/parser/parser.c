/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/16 17:33:15 by gpasztor         ###   ########.fr       */
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
		ft_fprintf(2, "%s", buff);
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

t_rgb	sort_rgb(char *line)
{
	t_rgb	rgb_val;
	char	**split;

	split = ft_split(line, ",");
	free(line);
	if (!split || !split[0] || !split[1] || !split[2])
		parse_error("Invalid colour value");
	rgb_val.r = ft_atoi(split[0]);
	free(split[0]);
	rgb_val.g = ft_atoi(split[1]);
	free(split[1]);
	rgb_val.b = ft_atoi(split[2]);
	free(split[2]);
}

void	sort_data(t_parse *data, char **file, int *found)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file[i] != NULL)
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0 && ++(*found))
			data->textures[0] = ft_strtrim(file[i] + 2, " ");
		if (ft_strncmp(file[i], "EA ", 3) == 0 && ++(*found))
			data->textures[1] = ft_strtrim(file[i] + 2, " ");
		if (ft_strncmp(file[i], "SO ", 3) == 0 && ++(*found))
			data->textures[2] = ft_strtrim(file[i] + 2, " ");
		if (ft_strncmp(file[i], "WE ", 3) == 0 && ++(*found))
			data->textures[3] = ft_strtrim(file[i] + 2, " ");
		if (ft_strncmp(file[i], "F ", 3) == 0 && ++(*found))
			
		if (ft_strncmp(file[i], "C ", 3) == 0 && ++(*found))
			
		free(file[i]);
	}
}

t_parse	*parse(int argc, char **argv)
{
	t_parse	parsed_data;
	int		found;
	char	**file;
	int		fd;

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
	return (NULL);
}
