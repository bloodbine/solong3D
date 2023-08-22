/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:26:50 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/22 18:58:07 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	sort_data(data, fd, &found);
	find_player(data);
	if (character_check(data->worldMap) == 1)
		parse_error("Invalid character in map");
	// file_check(data);
	return (data);
}

	// printf("TEST Found: %d\n", found);
	// printf("TEST NO: %s\n", parsed_data.textures[0]);
	// printf("TEST EA: %s\n", parsed_data.textures[1]);
	// printf("TEST SO: %s\n", parsed_data.textures[2]);
	// printf("TEST WE: %s\n", parsed_data.textures[3]);
	// printf("TEST F: 0x%06X\n", parsed_data.floor);
	// printf("TEST C: 0x%06X\n", parsed_data.roof);