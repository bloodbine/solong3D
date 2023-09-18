/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:47:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/18 18:24:42 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	filter(t_parse *data, char *buff, int *found, int *limit)
{
	if (ft_strncmp(buff, "NO", 2) == 0 && ++(*found) && !data->textures[0])
		data->textures[0] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "EA", 2) == 0 && ++(*found) && !data->textures[1])
		data->textures[1] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "SO", 2) == 0 && ++(*found) && !data->textures[2])
		data->textures[2] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "WE", 2) == 0 && ++(*found) && !data->textures[3])
		data->textures[3] = ft_strtrim(buff + 2, " \n");
	else if (ft_strncmp(buff, "D", 1) == 0 && ++(*found) && !data->doortex)
	{
		data->doortex = ft_strtrim(buff + 2, " \n");
		*limit = 7;
	}
	else if (ft_strncmp(buff, "F", 1) == 0 && ++(*found))
		sort_floor_roof(data, buff + 2, 'F');
	else if (ft_strncmp(buff, "C", 1) == 0 && ++(*found))
		sort_floor_roof(data, buff + 2, 'C');
}

void	sort_data(t_parse *data, int fd, int *found, char *buff)
{
	data->limit = 6;
	data->textures[0] = NULL;
	data->textures[1] = NULL;
	data->textures[2] = NULL;
	data->textures[3] = NULL;
	data->textures[4] = NULL;
	data->doortex = NULL;
	data->floortex = NULL;
	data->rooftex = NULL;
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		filter(data, buff, found, &data->limit);
		free(buff);
		if (*found == data->limit)
			break ;
		buff = get_next_line(fd);
	}
	if ((*found != 6 && *found != 7) || buff == NULL)
		parse_error("Incorrect variables");
	sort_map(data, fd);
}
