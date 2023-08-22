/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:54:30 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/22 13:53:36 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	file_check(t_parse *data)
{
	int	fd;
	int	i;

	i = -1;
	while (++i < 4)
	{
		fd = open(data->textures[i], O_RDONLY);
		if (fd == -1)
			parse_error("Invalid texture file");
		close(fd);
	}
}

int	character_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && \
			map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && \
			map[i][j] != 'E')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
