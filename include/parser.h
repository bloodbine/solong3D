/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:40 by ffederol          #+#    #+#             */
/*   Updated: 2023/08/23 03:22:47 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector.h"

typedef struct	s_parse
{
	char			*textures[5]; //{./path_to_the_north_texture,./path_to_the_east_texture,./path_to_the_s_texture,./path_to_the_w_texture,./path_to_the_door_texture, NULL}
	char			**worldMap;
	int				map_cols;
	int				map_lines;
	int				error;
	uint32_t		floor;
	uint32_t		roof;
	t_int_vector	playerPos;
	t_int_vector	playerDir; // (x|y)  N = (0|-1), E = (1|0), S = (0|1), W = (-1|0)
}				t_parse;

void		parse_free(t_parse *data);
void		run_dfs(t_parse *data);
uint32_t	sort_rgba(char	*line);
void		sort_map(t_parse *data, int fd);
void		sort_data(t_parse *data, int fd, int *found, char *buff);
void		find_player(t_parse *data);
void		file_check(t_parse *data);
int			character_check(char **map);
void		padding(t_parse *data, size_t len, size_t col);
t_parse		*parse(int argc, char **argv);
void		parse_error(char *error_message);
uint32_t	rgbtohex(int r, int g, int b, int a);

#endif