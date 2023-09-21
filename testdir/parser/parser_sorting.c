/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:47:29 by gpasztor          #+#    #+#             */
/*   Updated: 2023/09/21 22:08:48 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	filter(t_parse *data, char *buff, int *found, int *limit)
{
	if (ft_strncmp(buff, "NO", 2) == 0 && ++(*found) && !data->textures[0])
		data->textures[0] = ft_strtrim(buff + 2, " \n"); //leak
	else if (ft_strncmp(buff, "EA", 2) == 0 && ++(*found) && !data->textures[1])
		data->textures[1] = ft_strtrim(buff + 2, " \n"); //leak
	else if (ft_strncmp(buff, "SO", 2) == 0 && ++(*found) && !data->textures[2])
		data->textures[2] = ft_strtrim(buff + 2, " \n"); //leak
	else if (ft_strncmp(buff, "WE", 2) == 0 && ++(*found) && !data->textures[3])
		data->textures[3] = ft_strtrim(buff + 2, " \n"); //leak
	else if (ft_strncmp(buff, "D", 1) == 0 && ++(*found) && !data->textures[4])
	{
		data->textures[4] = ft_strtrim(buff + 2, " \n");
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
	
	ft_memset(data->textures, 0, sizeof(data->textures));
	data->textures[5] = "./textures/player.png";
	data->textures[6] = "./textures/portal/portal1.png";
	data->textures[7] = "./textures/portal/portal2.png";
	data->textures[8] = "./textures/portal/portal3.png";
	data->textures[9] = "./textures/portal/portal4.png";
	data->textures[10] = "./textures/portal/portal5.png";
	data->textures[11] = "./textures/portal/portal6.png";
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
