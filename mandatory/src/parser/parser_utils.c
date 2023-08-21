/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:37:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/21 15:09:16 by gpasztor         ###   ########.fr       */
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

uint32_t	rgbtohex(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) \
	+ (a & 0xff));
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
			new_map[i] = ft_frstrjoin(new_map[i], " ", 1);
		printf("%s\n", new_map[i]);
		i++;
	}
	i = 0;
	while (data->worldMap[i] != NULL)
		free(data->worldMap[i++]);
	free(data->worldMap);
	data->worldMap = new_map;
}

void	padding(t_parse *data, size_t len, size_t col)
{
	char		**new_map;
	char		*pad_line;
	size_t		i;
	size_t		j;

	new_map = malloc((col + 8) * sizeof(char *));
	pad_line = malloc((len + 7) * sizeof(char *));
	pad_line = ft_strdup("");
	while (ft_strlen(pad_line) < len + 5)
		pad_line = ft_frstrjoin(pad_line, " ", 1);
	pad_line = ft_frstrjoin(pad_line, "\n", 1);
	new_map[col + 6] = NULL;
	data->worldMap[col - 1] = ft_frstrjoin(data->worldMap[col - 1], "\n", 1);
	i = 0;
	j = 0;
	while (new_map[i] != NULL)
	{
		if (i < 3 || i > col + 2)
			new_map[i] = ft_strdup(pad_line);
		else
			new_map[i] = ft_strjoin("   ", data->worldMap[j++]);
		i++;
	}
	padding_right(data, len, new_map);
}
