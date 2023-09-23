/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:37:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/23 17:39:56 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parse_error(char *error_message)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 2);
	exit(EXIT_FAILURE);
}

void	parse_free(t_parse *data)
{
	int	i;

	i = -1;
	while (data->worldmap && data->worldmap[++i])
		free(data->worldmap[i]);
	free(data->worldmap);
	i = 0;
	while (i < 5)
	{
		if (data->textures[i] != NULL)
			free(data->textures[i]);
		i++;
	}
	if (data->floortex != NULL)
		free(data->floortex);
	if (data->rooftex != NULL)
		free(data->rooftex);
	free(data);
}

uint32_t	rgbtohex(t_parse *data, int rgb[3], char *buff)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (free(buff), parse_free(data), \
		parse_error("Colour value must be 0-255"), 0);
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) \
	+ (255 & 0xff));
}

void	padding_right(t_parse *data, size_t len, char **new_map)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (new_map[i] != NULL)
	{
		temp = ft_strtrim(new_map[i], "\n");
		free(new_map[i]);
		new_map[i] = ft_strdup(temp);
		free(temp);
		while (ft_strlen(new_map[i]) < len + 5) 
			new_map[i] = ft_frstrjoin(new_map[i], " ", 1); //leak (malloc :63)
		printf("%s\n", new_map[i]);
		i++;
	}
	data->mapsizes.x = len + 6;
	i = 0;
	while (data->worldmap[i] != NULL)
		free(data->worldmap[i++]);
	free(data->worldmap);
	data->worldmap = new_map;
}

void	padding(t_parse *data, size_t len, size_t col)
{
	char		**new_map;
	char		*pad_line;
	size_t		i;
	size_t		j;

	new_map = malloc((col + 7) * sizeof(char *)); //leak
	data->mapsizes.y = col + 6;
	pad_line = ft_strdup("");
	while (ft_strlen(pad_line) < len + 5)
		pad_line = ft_frstrjoin(pad_line, " ", 1);
	pad_line = ft_frstrjoin(pad_line, "\n", 1);
	data->worldmap[col - 1] = ft_frstrjoin(data->worldmap[col - 1], "\n", 1);
	i = 0;
	j = 0;
	while (i <= (col + 5))
	{
		if (i < 3 || (i > col + 2 && i != col + 6))
			new_map[i] = ft_strdup(pad_line);
		else
			new_map[i] = ft_strjoin("   ", data->worldmap[j++]);
		i++;
	}
	new_map[col + 6] = NULL;
	free(pad_line);
	padding_right(data, len, new_map);
}
