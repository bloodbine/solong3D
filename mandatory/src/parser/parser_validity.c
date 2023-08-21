/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:54:30 by gpasztor          #+#    #+#             */
/*   Updated: 2023/08/21 16:02:41 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
